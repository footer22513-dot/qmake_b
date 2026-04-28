#include "creditformwidget.h"
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
    double rate  = selectedRate();
    int    days  = selectedDays();
    if (ok && start > 0 && days > 0) {
        double end = start * (1.0 + rate * days / 36500.0);
        endSumLabel->setText(QString::number(end, 'f', 2) + " руб.");
    } else {
        endSumLabel->setText("0.00 руб.");
    }
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
    double endSum = start * (1.0 + rate * days / 36500.0);

    emit creditDataReady(
        fioInput->text().trimmed(), phoneInput->text().trimmed(),
        issueDateEdit->date(), days,
        rateTypeCombo->currentIndex(), rate,
        periodCombo->currentIndex(),
        start, endSum,
        earlyRepayCheck->isChecked()
        );
    emit navigateToSuccess();
}
