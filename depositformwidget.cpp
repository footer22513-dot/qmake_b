#include "depositformwidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>

// Предустановленные ставки для вкладов
static const QStringList DEPOSIT_RATES = {"5.00%", "7.50%", "10.00%"};
static const double      DEPOSIT_RATE_VALUES[] = {5.0, 7.5, 10.0};

DepositFormWidget::DepositFormWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void DepositFormWidget::setupUI() {
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

    // Срок — по ТЗ п.3.1.3: 1м, 3м, 6м, 1г, 3г, произвольный
    termCombo = new QComboBox;
    termCombo->addItems({"1 месяц (30 дней)", "3 месяца (90 дней)", "6 месяцев (180 дней)",
                         "1 год (365 дней)", "3 года (1095 дней)", "Произвольный"});
    daysInput = new QLineEdit;
    daysInput->setPlaceholderText("Введите количество дней");
    daysInput->setVisible(false);
    daysInput->setFont(wf);

    rateTypeCombo = new QComboBox;
    rateTypeCombo->addItems({"ФИКСИРОВАННАЯ", "ЗАВИСИТ ОТ СУММЫ", "ЗАВИСИТ ОТ СРОКА"});

    rateCombo = new QComboBox;
    rateCombo->addItems(DEPOSIT_RATES);

    periodCombo = new QComboBox;
    periodCombo->addItems({"ЕЖЕМЕСЯЧНО", "ЕЖЕКВАРТАЛЬНО", "ЕЖЕГОДНО"});

    startSumInput = new QLineEdit;

    addRow("ФИО:", fioInput);
    addRow("НОМЕР ТЕЛЕФОНА:", phoneInput);
    addRow("ДАТА НАЧАЛА:", issueDateEdit);
    addRow("СРОК РАЗМЕЩЕНИЯ:", termCombo);
    layout->addWidget(daysInput);
    addRow("ТИП СТАВКИ:", rateTypeCombo);
    addRow("ПРОЦЕНТНАЯ СТАВКА:", rateCombo);
    addRow("ПЕРИОДИЧНОСТЬ ВЫПЛАТ:", periodCombo);
    addRow("СУММА ВКЛАДА (руб.):", startSumInput);

    auto* endTitle = new QLabel("СУММА К ПОЛУЧЕНИЮ:");
    endTitle->setFont(QFont("Segoe UI", 15, QFont::Bold));
    layout->addWidget(endTitle);

    endSumLabel = new QLabel("0.00 руб.");
    endSumLabel->setStyleSheet("font-size:22px; color:#1976D2; font-weight:bold;"
                               "background:#f0f0f0; padding:8px; border-radius:4px;");
    endSumLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(endSumLabel);
    layout->addStretch();

    createBtn = new QPushButton("ОТКРЫТЬ ВКЛАД");
    createBtn->setFont(QFont("Segoe UI", 18, QFont::Bold));
    createBtn->setMinimumHeight(52);
    createBtn->setStyleSheet("background:#2196F3; color:white; border-radius:6px;");
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

void DepositFormWidget::setupConnections() {
    // FIX: Cast to void(QComboBox::*)(int) to specify the 'int' version
    connect(termCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [this](int idx){
        daysInput->setVisible(idx == termCombo->count()-1);
        calculateEndSum();
    });

    connect(daysInput,     &QLineEdit::textChanged, this, &DepositFormWidget::calculateEndSum);

    // FIX APPLIED HERE: Added the cast for rateCombo as well
    connect(rateCombo,     static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DepositFormWidget::calculateEndSum);

    connect(startSumInput, &QLineEdit::textChanged, this, &DepositFormWidget::calculateEndSum);
    connect(createBtn, &QPushButton::clicked, this, &DepositFormWidget::onCreateDepositClicked);
    connect(backBtn,   &QPushButton::clicked, this, &DepositFormWidget::navigateToUser);
}

int DepositFormWidget::selectedDays() const {
    static const int p[] = {30, 90, 180, 365, 1095};
    int i = termCombo->currentIndex();
    return (i < 5) ? p[i] : daysInput->text().toInt();
}

double DepositFormWidget::selectedRate() const {
    int i = rateCombo->currentIndex();
    return (i >= 0 && i < 3) ? DEPOSIT_RATE_VALUES[i] : 0.0;
}

void DepositFormWidget::calculateEndSum() {
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

void DepositFormWidget::resetForm() {
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
}

void DepositFormWidget::onCreateDepositClicked() {
    if (fioInput->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите ФИО клиента."); return;
    }
    if (phoneInput->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите номер телефона."); return;
    }
    bool ok;
    double start = startSumInput->text().toDouble(&ok);
    if (!ok || start <= 0) {
        QMessageBox::warning(this, "Ошибка", "Сумма вклада должна быть больше нуля."); return;
    }
    int days = selectedDays();
    if (days <= 0) {
        QMessageBox::warning(this, "Ошибка", "Укажите срок размещения."); return;
    }
    double rate   = selectedRate();
    double endSum = start * (1.0 + rate * days / 36500.0);

    emit depositDataReady(
        fioInput->text().trimmed(), phoneInput->text().trimmed(),
        issueDateEdit->date(), days,
        rateTypeCombo->currentIndex(), rate,
        periodCombo->currentIndex(),
        start, endSum
        );
    emit navigateToSuccess();
}
