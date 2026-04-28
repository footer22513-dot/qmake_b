#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "loginwidget.h"
#include "adminwidget.h"
#include "userwidget.h"
#include "credittablewidget.h"
#include "depositwidget.h"
#include "creditformwidget.h"
#include "depositformwidget.h"
#include "successwidget.h"
#include "datahandler.h"

#include <initializer_list>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QLayout>
#include "piechartwidget.h"
#include <QtCharts/QtCharts>
#include <QPen>

static const QString DEFAULT_FILE = "bank_records.txt";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    currentFile(DEFAULT_FILE)
{
    ui->setupUi(this);
    resize(1280, 800);
    setMinimumSize(1024, 768);
    setWindowTitle("АРМ «Займы и Вклады»");

    loginWgt       = new LoginWidget(this);
    adminWgt       = new AdminWidget(this);
    userWgt        = new UserWidget(this);
    creditTableWgt = new CreditTableWidget(this);
    depositTableWgt= new DepositTableWidget(this);
    creditFormWgt  = new CreditFormWidget(this);
    depositFormWgt = new DepositFormWidget(this);
    successWgt     = new SuccessWidget(this);
    pieChartWgt = new PieChartWidget();

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // ДОБАВЛЯЕМ ВИДЖЕТЫ В СТЕК (это было пропущено!)
    stack->addWidget(loginWgt);
    stack->addWidget(adminWgt);
    stack->addWidget(userWgt);
    stack->addWidget(creditTableWgt);
    stack->addWidget(depositTableWgt);
    stack->addWidget(creditFormWgt);
    stack->addWidget(depositFormWgt);
    stack->addWidget(successWgt);
    stack->addWidget(pieChartWgt);

    // ── Навигация ──────────────────────────────────────────
    connect(loginWgt, &LoginWidget::navigateToAdmin, this, &MainWindow::goAdmin);
    connect(loginWgt, &LoginWidget::navigateToUser,  this, &MainWindow::goUser);

    connect(adminWgt, &AdminWidget::navigateToCreditTable,  this, &MainWindow::goCreditTable);
    connect(adminWgt, &AdminWidget::navigateToDepositTable, this, &MainWindow::goDepositTable);
    connect(adminWgt, &AdminWidget::navigateToLogin,        this, &MainWindow::goLogin);
    connect(adminWgt, &AdminWidget::loadDatabaseRequested,  this, &MainWindow::onLoadDb);
    connect(adminWgt, &AdminWidget::saveDatabaseRequested,  this, &MainWindow::onSaveDb);
    connect(adminWgt, &AdminWidget::navigateToAnalytics, this, &MainWindow::goPieChart);

    connect(userWgt, &UserWidget::navigateToCreditForm,  this, &MainWindow::goCreditForm);
    connect(userWgt, &UserWidget::navigateToDepositForm, this, &MainWindow::goDepositForm);
    connect(userWgt, &UserWidget::navigateToLogin,       this, &MainWindow::goLogin);

    connect(creditTableWgt,  &CreditTableWidget::navigateToAdmin,  this, &MainWindow::goAdmin);
    connect(depositTableWgt, &DepositTableWidget::navigateToAdmin, this, &MainWindow::goAdmin);
    connect(creditTableWgt,  &CreditTableWidget::recordDeleted,    this, &MainWindow::onCreditDeleted);
    connect(depositTableWgt, &DepositTableWidget::recordDeleted,   this, &MainWindow::onDepositDeleted);

    // Подключаем сигналы обновления
    connect(creditTableWgt,  &CreditTableWidget::recordUpdated,    this, &MainWindow::onCreditUpdated);
    connect(depositTableWgt, &DepositTableWidget::recordUpdated,   this, &MainWindow::onDepositUpdated);

    connect(creditFormWgt, &CreditFormWidget::navigateToUser,    this, &MainWindow::goUser);
    connect(creditFormWgt, &CreditFormWidget::navigateToSuccess, this, &MainWindow::goSuccess);
    connect(creditFormWgt, &CreditFormWidget::creditDataReady,   this, &MainWindow::onCreditReady);

    connect(depositFormWgt, &DepositFormWidget::navigateToUser,    this, &MainWindow::goUser);
    connect(depositFormWgt, &DepositFormWidget::navigateToSuccess, this, &MainWindow::goSuccess);
    connect(depositFormWgt, &DepositFormWidget::depositDataReady,  this, &MainWindow::onDepositReady);

    connect(successWgt, &SuccessWidget::navigateToUser, this, &MainWindow::goUser);



    //-----ПРОПИСЫВАЮ НОВЫЙ ВИДЖЕТ ЗДЕСЬ, ПОТОМ НАДО В ОТДЕЛЬНЫЙ ФАЙЛ-----
    //-----АНАЛИТИКА-----
    QVBoxLayout* pie_chart_layout = new QVBoxLayout;
    pie_chart_layout->setContentsMargins(32, 32, 32, 24);
    pie_chart_layout->setSpacing(16);
    pieChartWgt->setLayout(pie_chart_layout);


    QLabel* chartTitle = new QLabel("АНАЛИТИКА");
    chartTitle->setAlignment(Qt::AlignCenter);

    pie_chart_layout->addWidget(chartTitle);

    QFrame* divider = new QFrame;
    divider->setFrameShape(QFrame::HLine);

    pie_chart_layout->addWidget(divider);



    QHBoxLayout* legend = new QHBoxLayout;
    legend->setSpacing(24);
    legend->setContentsMargins(0, 8, 0, 8);

    auto makeLegendItem = [](const QString& color, const QString& label) -> QWidget* {
        auto* w = new QWidget;
        auto* h = new QHBoxLayout(w);
        h->setContentsMargins(16, 10, 24, 10);
        h->setSpacing(10);


        auto* dot = new QLabel;
        dot->setFixedSize(14, 14);
        dot->setStyleSheet(QString(
                               "background: %1; border-radius: 7px;"
                               ).arg(color));
        h->addWidget(dot);

        auto* lbl = new QLabel(label);
        lbl->setStyleSheet(QString(
                               "font-size: 15px; font-weight: bold; color: %1; letter-spacing: 1px;"
                               ).arg(color));
        h->addWidget(lbl);
        return w;
    };

    legend->addStretch();

    legend->addStretch();
    pie_chart_layout->addLayout(legend);

    QPushButton* Btn = new QPushButton("← НАЗАД");
    Btn->setMinimumHeight(50);

    connect(Btn, &QPushButton::clicked, this, &MainWindow::goAdmin);
    pie_chart_layout->addWidget(Btn);
    //--------------------
    //--------------------------------------------------------------------

    loadFile(currentFile);
    stack->setCurrentWidget(loginWgt);
}

MainWindow::~MainWindow() { delete ui; }

// ── Файлы ──────────────────────────────────────────────────
void MainWindow::loadFile(const QString& path) {
    allRecords = DataHandler::loadRecords(path);
}
void MainWindow::saveFile(const QString& path) {
    DataHandler::saveRecords(allRecords, path);
}

void MainWindow::onLoadDb() {
    QString path = QFileDialog::getOpenFileName(this, "Загрузить базу",
                                                QDir::homePath(), "Текстовые файлы (*.txt);;Все файлы (*)");
    if (path.isEmpty()) return;
    loadFile(path);
    currentFile = path;
    QMessageBox::information(this, "Загрузка",
                             QString("Загружено записей: %1").arg(allRecords.size()));
}

void MainWindow::onSaveDb() {
    QString path = QFileDialog::getSaveFileName(this, "Выгрузить базу",
                                                QDir::homePath() + "/" + QFileInfo(currentFile).fileName(),
                                                "Текстовые файлы (*.txt);;Все файлы (*)");
    if (path.isEmpty()) return;
    saveFile(path);
    currentFile = path;
    QMessageBox::information(this, "Выгрузка",
                             QString("База сохранена:\n%1").arg(path));
}

// ── Конвертеры ─────────────────────────────────────────────
QList<CreditRecord> MainWindow::toCreditList() const {
    QList<CreditRecord> out;
    for (const auto& r : allRecords) {
        if (r.type != OperationType::Credit) continue;
        CreditRecord cr;
        cr.id            = r.id;
        cr.fullName      = r.fullName;
        cr.phone         = r.phone;
        cr.issueDate     = r.issueDate.toString("dd.MM.yyyy");
        cr.termDays      = r.termDays;
        cr.rateType      = static_cast<int>(r.rateType);
        cr.ratePercent   = r.ratePercent;
        cr.paymentPeriod = static_cast<int>(r.paymentPeriod);
        cr.startSum      = r.startSum;
        cr.endSum        = r.endSum;
        cr.earlyRepay    = r.isEarlyRepaymentAllowed;
        out.append(cr);
    }
    return out;
}

QList<DepositRecord> MainWindow::toDepositList() const {
    QList<DepositRecord> out;
    for (const auto& r : allRecords) {
        if (r.type != OperationType::Deposit) continue;
        DepositRecord dr;
        dr.id            = r.id;
        dr.fullName      = r.fullName;
        dr.phone         = r.phone;
        dr.issueDate     = r.issueDate.toString("dd.MM.yyyy");
        dr.termDays      = r.termDays;
        dr.rateType      = static_cast<int>(r.rateType);
        dr.ratePercent   = r.ratePercent;
        dr.paymentPeriod = static_cast<int>(r.paymentPeriod);
        dr.startSum      = r.startSum;
        dr.endSum        = r.endSum;
        out.append(dr);
    }
    return out;
}

// ── Навигация ──────────────────────────────────────────────
void MainWindow::goLogin()   { stack->setCurrentWidget(loginWgt); }
void MainWindow::goAdmin()   { stack->setCurrentWidget(adminWgt); }
void MainWindow::goUser()    { stack->setCurrentWidget(userWgt); }
void MainWindow::goSuccess() { stack->setCurrentWidget(successWgt); }
void MainWindow::goCreditForm()  { stack->setCurrentWidget(creditFormWgt); }
void MainWindow::goDepositForm() { stack->setCurrentWidget(depositFormWgt); }
void MainWindow::goPieChart() {
    int credits = 0, deposits = 0;
    for (const auto& r : allRecords) {
        if (r.type == OperationType::Credit) credits++;
        else deposits++;
    }
    // Update chart
    static_cast<PieChartWidget*>(pieChartWgt)->updateData(credits, deposits);
    stack->setCurrentWidget(pieChartWgt);
}


void MainWindow::goCreditTable() {
    creditTableWgt->setRecords(toCreditList());
    stack->setCurrentWidget(creditTableWgt);
}
void MainWindow::goDepositTable() {
    depositTableWgt->setRecords(toDepositList());
    stack->setCurrentWidget(depositTableWgt);
}

// ── Приём данных ───────────────────────────────────────────
void MainWindow::onCreditReady(const QString& fio, const QString& phone,
                               QDate issueDate, int days,
                               int rateType, double rate, int period,
                               double startSum, double endSum, bool earlyRepay)
{
    BankRecord r;
    r.id          = DataHandler::generateNextId(allRecords);
    r.type        = OperationType::Credit;
    r.fullName    = fio;
    r.phone       = phone;
    r.issueDate   = issueDate;
    r.termDays    = days;
    r.rateType    = static_cast<RateType>(rateType);
    r.ratePercent = rate;
    r.paymentPeriod = static_cast<PaymentPeriod>(period);
    r.startSum    = startSum;
    r.endSum      = endSum;
    r.isEarlyRepaymentAllowed = earlyRepay;
    allRecords.append(r);
    saveFile(currentFile);
}

void MainWindow::onDepositReady(const QString& fio, const QString& phone,
                                QDate issueDate, int days,
                                int rateType, double rate, int period,
                                double startSum, double endSum)
{
    BankRecord r;
    r.id          = DataHandler::generateNextId(allRecords);
    r.type        = OperationType::Deposit;
    r.fullName    = fio;
    r.phone       = phone;
    r.issueDate   = issueDate;
    r.termDays    = days;
    r.rateType    = static_cast<RateType>(rateType);
    r.ratePercent = rate;
    r.paymentPeriod = static_cast<PaymentPeriod>(period);
    r.startSum    = startSum;
    r.endSum      = endSum;
    allRecords.append(r);
    saveFile(currentFile);
}

void MainWindow::onCreditDeleted(int id) {
    for (auto it = allRecords.begin(); it != allRecords.end(); ) {
        if (it->id == id && it->type == OperationType::Credit) {
            it = allRecords.erase(it);
        } else {
            ++it;
        }
    }
    saveFile(currentFile);
}

void MainWindow::onDepositDeleted(int id) {
    for (auto it = allRecords.begin(); it != allRecords.end(); ) {
        if (it->id == id && it->type == OperationType::Deposit) {
            it = allRecords.erase(it);
        } else {
            ++it;
        }
    }
    saveFile(currentFile);
}

// ── Обновление записей (редактирование в таблице) ──────────
void MainWindow::onCreditUpdated(const CreditRecord& rec) {
    for (auto& r : allRecords) {
        if (r.id == rec.id && r.type == OperationType::Credit) {
            r.fullName    = rec.fullName;
            r.phone       = rec.phone;
            r.issueDate   = QDate::fromString(rec.issueDate, "dd.MM.yyyy");
            r.termDays    = rec.termDays;
            r.ratePercent = rec.ratePercent;
            r.startSum    = rec.startSum;
            r.endSum      = rec.endSum;
            // rateType и paymentPeriod не меняем здесь (требуют спец. контролов)
            break;
        }
    }
    saveFile(currentFile);
}

void MainWindow::onDepositUpdated(const DepositRecord& rec) {
    for (auto& r : allRecords) {
        if (r.id == rec.id && r.type == OperationType::Deposit) {
            r.fullName    = rec.fullName;
            r.phone       = rec.phone;
            r.issueDate   = QDate::fromString(rec.issueDate, "dd.MM.yyyy");
            r.termDays    = rec.termDays;
            r.ratePercent = rec.ratePercent;
            r.startSum    = rec.startSum;
            r.endSum      = rec.endSum;
            break;
        }
    }
    saveFile(currentFile);
}


