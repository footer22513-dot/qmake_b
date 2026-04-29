#include "creditformwidget.h"
#include "creditcalc.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QDate>
#include <cmath>

// Предустановленные ставки для кредитов (ТЗ: фиксированные варианты)
static const QStringList CREDIT_RATES = {"8.00%", "12.00%", "18.00%"};
static const double      CREDIT_RATE_VALUES[] = {8.0, 12.0, 18.0};

CreditFormWidget::CreditFormWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void CreditFormWidget::setupUI() {
    auto* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    auto* inner  = new QWidget;
    auto* layout = new QVBoxLayout(inner);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(8);

    QFont lf("Segoe UI", 13, QFont::Bold);
    QFont wf("Segoe UI", 13);

    auto addRow = [&](const QString& label, QWidget* w) {
        auto* lbl = new QLabel(label); lbl->setFont(lf);
        layout->addWidget(lbl);
        w->setFont(wf);
        layout->addWidget(w);
    };

    fioInput      = new QLineEdit;
    phoneInput    = new QLineEdit;
    issueDateEdit = new QDateEdit(QDate::currentDate());
    issueDateEdit->setCalendarPopup(true);
    issueDateEdit->setDisplayFormat("dd.MM.yyyy");

    // Срок — по ТЗ п.3.1.3
    termCombo = new QComboBox;
    termCombo->addItems({"30 дней (1 мес.)", "90 дней (3 мес.)", "180 дней (6 мес.)",
                         "365 дней (1 год)", "730 дней (2 года)", "Произвольный"});
    daysInput = new QLineEdit;
    daysInput->setPlaceholderText("Введите количество дней");
    daysInput->setVisible(false);
    daysInput->setFont(wf);

    rateTypeCombo = new QComboBox;
    rateTypeCombo->addItems({"ФИКСИРОВАННАЯ", "ЗАВИСИТ ОТ СУММЫ", "ЗАВИСИТ ОТ СРОКА"});

    // Фиксированные варианты ставок — пользователь выбирает из списка
    rateCombo = new QComboBox;
    rateCombo->addItems(CREDIT_RATES);

    periodCombo = new QComboBox;
    periodCombo->addItems({"ЕЖЕМЕСЯЧНО", "ЕЖЕКВАРТАЛЬНО", "ЕЖЕГОДНО"});

    startSumInput = new QLineEdit;

    // ТЗ п.3.1.2: досрочная выплата
    earlyRepayCheck = new QCheckBox("Разрешить досрочное погашение");
    earlyRepayCheck->setFont(wf);
    earlyRepayCheck->setChecked(true);

    addRow("ФИО:", fioInput);
    addRow("НОМЕР ТЕЛЕФОНА:", phoneInput);
    addRow("ДАТА ВЫДАЧИ:", issueDateEdit);
    addRow("СРОК ЗАЙМА:", termCombo);
    layout->addWidget(daysInput);
    addRow("ТИП СТАВКИ:", rateTypeCombo);
    addRow("ПРОЦЕНТНАЯ СТАВКА:", rateCombo);
    addRow("ПЕРИОДИЧНОСТЬ ВЫПЛАТ:", periodCombo);
    addRow("СУММА ЗАЙМА (руб.):", startSumInput);
    layout->addWidget(earlyRepayCheck);

    // Штрафы
    penaltyAmountInput = new QLineEdit;
    penaltyAmountInput->setPlaceholderText("Сумма штрафа (руб.)");
    addRow("ШТРАФ (руб.)", penaltyAmountInput);

    penaltyPercentInput = new QLineEdit;
    penaltyPercentInput->setPlaceholderText("Штраф в % от остатка");
    addRow("ШТРАФ (% )", penaltyPercentInput);

    // Тип кредита
    creditTypeCombo = new QComboBox;
    creditTypeCombo->addItems({"Простой", "Аннуитет", "Дифференцированный"});
    addRow("Тип кредита:", creditTypeCombo);

    auto* endTitle = new QLabel("СУММА К ВОЗВРАТУ:");
    endTitle->setFont(QFont("Segoe UI", 15, QFont::Bold));
    layout->addWidget(endTitle);

    endSumLabel = new QLabel("0.00 руб.");
    endSumLabel->setStyleSheet("font-size:22px; color:#2e7d32; font-weight:bold;"
                               "background:#f0f0f0; padding:8px; border-radius:4px;");
    endSumLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(endSumLabel);
    layout->addStretch();

    createBtn = new QPushButton("ОФОРМИТЬ ЗАЙМ");
    createBtn->setFont(QFont("Segoe UI", 18, QFont::Bold));
    createBtn->setMinimumHeight(52);
    createBtn->setStyleSheet("background:#4CAF50; color:white; border-radius:6px;");
    layout->addWidget(createBtn);

    backBtn = new QPushButton("НАЗАД");
    backBtn->setFont(QFont("Segoe UI", 16));
    backBtn->setMinimumHeight(48);
    backBtn->setStyleSheet("background:#f44336; color:white; border-radius:6px;");
    layout->addWidget(backBtn);

    scroll->setWidget(inner);
    auto* outer = new QVBoxLayout(this);
    outer->setContentsMargins(0,0,0,0);
    outer->addWidget(scroll);
    setLayout(outer);
}

void CreditFormWidget::setupConnections() {
    // FIX: Cast for termCombo (Lambda)
    connect(termCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this](int idx){
        daysInput->setVisible(idx == termCombo->count()-1);
        calculateEndSum();
    });

    connect(daysInput,    &QLineEdit::textChanged, this, &CreditFormWidget::calculateEndSum);

    // FIX: Cast for rateCombo (Member function)
    connect(rateCombo,    static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CreditFormWidget::calculateEndSum);

    connect(startSumInput,&QLineEdit::textChanged, this, &CreditFormWidget::calculateEndSum);
    connect(createBtn, &QPushButton::clicked, this, &CreditFormWidget::onCreateCreditClicked);
    connect(backBtn,   &QPushButton::clicked, this, &CreditFormWidget::navigateToUser);
    // Recalculate when credit type changes
    connect(creditTypeCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CreditFormWidget::calculateEndSum);
}

int CreditFormWidget::selectedDays() const {
    static const int p[] = {30, 90, 180, 365, 730};
    int i = termCombo->currentIndex();
    return (i < 5) ? p[i] : daysInput->text().toInt();
}

double CreditFormWidget::selectedRate() const {
    int i = rateCombo->currentIndex();
    return (i >= 0 && i < 3) ? CREDIT_RATE_VALUES[i] : 0.0;
}

void CreditFormWidget::calculateEndSum() {
    bool ok;
    double start = startSumInput->text().toDouble(&ok);
    int    days  = selectedDays();
    if (!(ok && start > 0 && days > 0)) {
        endSumLabel->setText("0.00 руб.");
        return;
    }
    // Base annual rate
    double baseRate = selectedRate();
    // Adjust based on rate type
    int rateType = rateTypeCombo->currentIndex(); // 0: fixed, 1: depends on sum, 2: depends on term
    if (rateType == 1) { // depends on sum
        if (start > 50000) {
            baseRate += 0.5;
        }
    } else if (rateType == 2) { // depends on term
        if (days > 180) {
            baseRate += 0.3;
        }
    }
    // Apply payment frequency factor
    int periodIdx = periodCombo->currentIndex(); // 0 monthly, 1 quarterly, 2 yearly
    int periodsPerYear = (periodIdx == 0) ? 12 : (periodIdx == 1) ? 4 : 1;
    double frequencyFactor = 12.0 / periodsPerYear; // monthly=1, quarterly=3, yearly=12
    double effectiveRate = baseRate * frequencyFactor;
    double end = 0.0;
    int type = creditTypeCombo->currentIndex(); // 0‑Simple, 1‑Annuity, 2‑Diff
    if (type == 0) {
        // Simple interest using effective annual rate
        end = CreditCalculator::calculateSimple(start, effectiveRate, days);
    } else if (type == 1) {
        // Annuity: approximate months = days/30 (rounded up)
        int months = (days + 29) / 30;
        double monthlyRate = effectiveRate / 12.0 / 100.0;
        double payment = CreditCalculator::calculateAnnuityPayment(start, monthlyRate, months);
        end = payment * months;
    } else if (type == 2) {
        // Differentiated payments
        int months = (days + 29) / 30;
        double monthlyRate = effectiveRate / 12.0 / 100.0;
        double total = 0.0;
        for (int m = 1; m <= months; ++m) {
            total += CreditCalculator::calculateDiffPayment(start, monthlyRate, m, months);
        }
        end = total;
    }
    endSumLabel->setText(QString::number(end, 'f', 2) + " руб.");
}

void CreditFormWidget::onCreateCreditClicked() {
    if (fioInput->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите ФИО клиента."); return;
    }
    if (phoneInput->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите номер телефона."); return;
    }
    bool ok;
    double start = startSumInput->text().toDouble(&ok);
    if (!ok || start <= 0) {
        QMessageBox::warning(this, "Ошибка", "Сумма займа должна быть больше нуля."); return;
    }
    int days = selectedDays();
    if (days <= 0) {
        QMessageBox::warning(this, "Ошибка", "Укажите срок займа."); return;
    }
    double rate   = selectedRate();
    double endSum = 0.0;
    int loanType = creditTypeCombo->currentIndex();
    if (loanType == 0) {
        endSum = CreditCalculator::calculateSimple(start, rate, days);
    } else if (loanType == 1) {
        int months = (days + 29) / 30;
        double monthlyRate = rate / 12.0 / 100.0;
        double payment = CreditCalculator::calculateAnnuityPayment(start, monthlyRate, months);
        endSum = payment * months;
    } else if (loanType == 2) {
        int months = (days + 29) / 30;
        double monthlyRate = rate / 12.0 / 100.0;
        double total = 0.0;
        for (int m = 1; m <= months; ++m) {
            total += CreditCalculator::calculateDiffPayment(start, monthlyRate, m, months);
        }
        endSum = total;
    }
    emit creditDataReady(
        fioInput->text().trimmed(), phoneInput->text().trimmed(),
        issueDateEdit->date(), days,
        rateTypeCombo->currentIndex(), rate,
        periodCombo->currentIndex(),
        start, endSum,
        earlyRepayCheck->isChecked(),
        penaltyAmountInput->text().toDouble(),
        penaltyPercentInput->text().toDouble(),
        creditTypeCombo->currentIndex()
        );
    emit navigateToSuccess();
    // Reset form fields
    fioInput->clear();
    phoneInput->clear();
    issueDateEdit->setDate(QDate::currentDate());
    termCombo->setCurrentIndex(0);
    daysInput->clear();
    daysInput->setVisible(false);
    rateTypeCombo->setCurrentIndex(0);
    rateCombo->setCurrentIndex(0);
    periodCombo->setCurrentIndex(0);
    startSumInput->clear();
    endSumLabel->setText("0.00 руб.");
    earlyRepayCheck->setChecked(true);
    penaltyAmountInput->clear();
    penaltyPercentInput->clear();
}

