#include "credittablewidget.h"
#include "creditcalc.h"
#include <QtWidgets>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QFileDialog>
#include <QDir>

CreditTableWidget::CreditTableWidget(QWidget *parent) : BaseWidget(parent) {
    auto* main = new QHBoxLayout(this);

    // Таблица
    table = new QTableWidget;
    table->setColumnCount(12);
    table->setHorizontalHeaderLabels({
        "ID", "ФИО", "Телефон", "Дата выдачи",
        "Срок (дн.)", "Тип ставки", "Ставка (%)",
        "Периодичность", "Нач. сумма", "Кон. сумма", "Штраф (руб.)", "Штраф (%)"
    });
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    table->setSortingEnabled(true);
    main->addWidget(table, 3);

    // Панель управления
    auto* ctrl = new QVBoxLayout;
    main->addLayout(ctrl, 1);

    ctrl->addWidget(new QLabel("Поиск (ФИО / тел. / ID):"));
    searchInput = new QLineEdit;
    searchInput->setPlaceholderText("Введите...");
    ctrl->addWidget(searchInput);

    ctrl->addWidget(new QLabel("Сумма от:"));
    sumMin = new QSpinBox; sumMin->setRange(0, 999999999);
    ctrl->addWidget(sumMin);
    ctrl->addWidget(new QLabel("Сумма до:"));
    sumMax = new QSpinBox; sumMax->setRange(0, 999999999); sumMax->setValue(999999999);
    ctrl->addWidget(sumMax);

    ctrl->addWidget(new QLabel("Дата выдачи от:"));
    dateFrom = new QDateEdit(QDate(2000,1,1)); dateFrom->setCalendarPopup(true);
    dateFrom->setDisplayFormat("dd.MM.yyyy");
    ctrl->addWidget(dateFrom);
    ctrl->addWidget(new QLabel("Дата выдачи до:"));
    dateTo = new QDateEdit(QDate::currentDate().addYears(10)); dateTo->setCalendarPopup(true);
    dateTo->setDisplayFormat("dd.MM.yyyy");
    ctrl->addWidget(dateTo);

    // Фильтр просроченных
    ctrl->addWidget(new QLabel("Фильтр:"));
    overdueOnly = new QCheckBox("Только просроченные");
    overdueOnly->setStyleSheet("font-size:13px; padding:4px;");
    connect(overdueOnly, &QCheckBox::toggled, this, &CreditTableWidget::onSearchClicked);
    ctrl->addWidget(overdueOnly);

    searchBtn = new QPushButton("🔍 ПОИСК");
    searchBtn->setStyleSheet("font-size:14px;padding:8px;background:#388E3C;color:white;border-radius:5px;");
    connect(searchBtn, &QPushButton::clicked, this, &CreditTableWidget::onSearchClicked);
    ctrl->addWidget(searchBtn);

    resetBtn = new QPushButton("СБРОСИТЬ");
    resetBtn->setStyleSheet("font-size:14px;padding:6px;background:#78909C;color:white;border-radius:5px;");
    connect(resetBtn, &QPushButton::clicked, this, &CreditTableWidget::onResetClicked);
    ctrl->addWidget(resetBtn);

    ctrl->addStretch();

    delBtn = new QPushButton("🗑 УДАЛИТЬ");
    delBtn->setStyleSheet("font-size:14px;padding:8px;background:#f44336;color:white;border-radius:5px;");
    connect(delBtn, &QPushButton::clicked, this, &CreditTableWidget::onDeleteClicked);
    ctrl->addWidget(delBtn);


    exportBtn = new QPushButton("📄 Отчёт");
    exportBtn->setStyleSheet("font-size:14px;padding:8px;background:#1565C0;color:white;border-radius:5px;");
    connect(exportBtn, &QPushButton::clicked, this, &CreditTableWidget::onExportReport);
    ctrl->addWidget(exportBtn);

    repayBtn = new QPushButton("💰 Погасить");
    repayBtn->setStyleSheet("font-size:14px;padding:8px;background:#388E3C;color:white;border-radius:5px;");
    connect(repayBtn, &QPushButton::clicked, this, &CreditTableWidget::onEarlyRepayClicked);
    ctrl->addWidget(repayBtn);



    backBtn = new QPushButton("← НАЗАД");
    backBtn->setStyleSheet("font-size:14px;padding:8px;background:#555;color:white;border-radius:5px;");
    connect(backBtn, &QPushButton::clicked, this, &CreditTableWidget::navigateToAdmin);
    ctrl->addWidget(backBtn);

    connect(table, &QTableWidget::itemChanged, this, &CreditTableWidget::onItemChanged);

    setLayout(main);
}

void CreditTableWidget::setRecords(const QList<CreditRecord>& data) {
    records = data;
    refreshTable(records);
}

QList<CreditRecord> CreditTableWidget::getRecords() const {
    return records;
}

void CreditTableWidget::refreshTable(const QList<CreditRecord>& data) {
    m_isRefreshing = true;
    table->setSortingEnabled(false);
    table->setRowCount(0);

    QDate today = QDate::currentDate();

    for (const auto& r : data) {
        int row = table->rowCount();
        table->insertRow(row);

        // Определяем просроченность для подсветки строки
        QDate issueDate = QDate::fromString(r.issueDate, "dd.MM.yyyy");
        bool overdue = false;
        if (issueDate.isValid()) {
            QDate dueDate = issueDate.addDays(r.termDays);
            overdue = (dueDate < today) && (r.endSum > 0);
        }

        auto makeItem = [&](const QString& text) -> QTableWidgetItem* {
            QTableWidgetItem* item = new QTableWidgetItem(text);
            if (overdue) {
                item->setBackground(QColor(255, 220, 220)); // светло-красный
            }
            return item;
        };

        // ID — не редактируемый
        QTableWidgetItem* idItem = makeItem(QString::number(r.id));
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 0, idItem);

        table->setItem(row, 1, makeItem(r.fullName));
        table->setItem(row, 2, makeItem(r.phone));
        table->setItem(row, 3, makeItem(r.issueDate));
        table->setItem(row, 4, makeItem(QString::number(r.termDays)));

        // Тип ставки — не редактируемый
        QTableWidgetItem* rateTypeItem = makeItem(rateTypeName(r.rateType));
        rateTypeItem->setFlags(rateTypeItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 5, rateTypeItem);

        table->setItem(row, 6, makeItem(QString::number(r.ratePercent, 'f', 2) + "%"));

        // Периодичность — не редактируемая
        QTableWidgetItem* periodItem = makeItem(periodName(r.paymentPeriod));
        periodItem->setFlags(periodItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 7, periodItem);

        table->setItem(row, 8, makeItem(QString::number(r.startSum, 'f', 2)));
        table->setItem(row, 9, makeItem(QString::number(r.endSum, 'f', 2)));
                // Calculate penalty if overdue
        double penaltyAmt = 0.0;
        if (overdue) {
            int daysLate = issueDate.addDays(r.termDays).daysTo(today);
            if (daysLate > 0) {
                penaltyAmt = CreditCalculator::calculatePenalty(r.endSum, r.penaltyPercent, daysLate);
            }
        }
        table->setItem(row, 10, makeItem(QString::number(penaltyAmt, 'f', 2)));
        table->setItem(row, 11, makeItem(QString::number(r.penaltyPercent, 'f', 2)));
    }

    table->setSortingEnabled(true);
    m_isRefreshing = false;
}

void CreditTableWidget::onSearchClicked() {
    QString f = searchInput->text().trimmed().toLower();
    double  minS = sumMin->value(), maxS = sumMax->value();
    QDate   df = dateFrom->date(), dt = dateTo->date();
    bool    onlyOverdue = overdueOnly->isChecked();
    QDate   today = QDate::currentDate();

    QList<CreditRecord> out;
    for (const auto& r : records) {
        QDate d = QDate::fromString(r.issueDate, "dd.MM.yyyy");

        bool nameOk = f.isEmpty() || r.fullName.toLower().contains(f)
                      || r.phone.contains(f)
                      || QString::number(r.id).contains(f);
        bool sumOk  = r.startSum >= minS && r.startSum <= maxS;
        bool dateOk = (!d.isValid()) || (d >= df && d <= dt);

        bool overdue = false;
        if (d.isValid()) {
            QDate dueDate = d.addDays(r.termDays);
            overdue = (dueDate < today) && (r.endSum > 0);
        }
        bool overdueOk = !onlyOverdue || overdue;

        if (nameOk && sumOk && dateOk && overdueOk) out.append(r);
    }
    refreshTable(out);
}

void CreditTableWidget::onResetClicked() {
    searchInput->clear();
    sumMin->setValue(0); sumMax->setValue(999999999);
    dateFrom->setDate(QDate(2000,1,1)); dateTo->setDate(QDate::currentDate().addYears(10));
    overdueOnly->setChecked(false);
    refreshTable(records);
}

void CreditTableWidget::onDeleteClicked() {
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this, "Внимание", "Выберите строку."); return; }
    int id = table->item(row, 0)->text().toInt();

    if (QMessageBox::Yes == QMessageBox::question(this, "Удаление", "Удалить выбранную запись?",
                                                  QMessageBox::Yes | QMessageBox::No)) {
        for (auto it = records.begin(); it != records.end(); ) {
            if (it->id == id) it = records.erase(it);
            else ++it;
        }
        refreshTable(records);
        emit recordDeleted(id);
    }
}

void CreditTableWidget::onItemChanged(QTableWidgetItem* item) {
    if (m_isRefreshing) return;

    int row = item->row();
    int col = item->column();
    if (row < 0 || row >= table->rowCount()) return;

    int id = table->item(row, 0)->text().toInt();
    auto it = std::find_if(records.begin(), records.end(),
                           [id](const CreditRecord& r) { return r.id == id; });
    if (it == records.end()) return;

    QString newVal = item->text();
    switch(col) {
    case 1:  it->fullName   = newVal; break;
    case 2:  it->phone      = newVal; break;
    case 3:  it->issueDate  = newVal; break;
    case 4:  it->termDays   = newVal.toInt(); break;
    case 6:  it->ratePercent = newVal.remove("%").trimmed().toDouble(); break;
    case 8:  it->startSum   = newVal.toDouble(); break;
    case 9:  it->endSum     = newVal.toDouble(); break;
    case 10: it->penaltyAmount  = newVal.toDouble(); break;
    case 11: it->penaltyPercent = newVal.toDouble(); break;
    default: return;
    }
    emit recordUpdated(*it);
}

void CreditTableWidget::onEarlyRepayClicked() {
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this, tr("Внимание"), tr("Выберите запись.")); return; }
    int id = table->item(row, 0)->text().toInt();

    bool ok = false;
    double amount = QInputDialog::getDouble(this, tr("Досрочное погашение"), tr("Сумма:"),
                                            0.0, 0.0, 1e9, 2, &ok);
    if (!ok) return;

    auto it = std::find_if(records.begin(), records.end(),
                           [id](const CreditRecord& r){ return r.id == id; });
    if (it == records.end()) return;

    it->endSum = qMax(0.0, it->endSum - amount);
    it->earlyRepay = true;
    refreshTable(records);
    emit recordUpdated(*it);
}

QString CreditTableWidget::rateTypeName(int t) {
    switch(t) { case 1: return "От суммы"; case 2: return "От срока"; default: return "Фиксированная"; }
}

QString CreditTableWidget::periodName(int p) {
    switch(p) { case 1: return "Ежеквартально"; case 2: return "Ежегодно"; default: return "Ежемесячно"; }
}


void CreditTableWidget::onExportReport() {
    QString path = QFileDialog::getSaveFileName(
        this, "Сохранить отчёт",

        QDir::homePath() + "/credit_report.txt" ,

        "Текстовые файлы (*.txt)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "=== ОТЧЁТ ПО ЗАЙМАМ ===\n";
    out << QString("Дата формирования: %1\n").arg(QDate::currentDate().toString("dd.MM.yyyy"));
    out << QString("Всего записей: %1\n\n").arg(records.size());

    int overdue = 0;
    QDate today = QDate::currentDate();
    for (const auto& r : records) {
        QDate d = QDate::fromString(r.issueDate, "dd.MM.yyyy");
        bool isOverdue = d.isValid() && (d.addDays(r.termDays) < today) && (r.endSum > 0);
        if (isOverdue) ++overdue;

        out << QString("ID: %1\n").arg(r.id);
        out << QString("  ФИО:        %1\n").arg(r.fullName);
        out << QString("  Телефон:    %1\n").arg(r.phone);
        out << QString("  Выдан:      %1\n").arg(r.issueDate);
        out << QString("  Срок:       %1 дн.\n").arg(r.termDays);
        out << QString("  Ставка:     %1%\n").arg(r.ratePercent, 0, 'f', 2);
        out << QString("  Нач. сумма: %1 руб.\n").arg(r.startSum, 0, 'f', 2);
        out << QString("  Кон. сумма: %1 руб.\n").arg(r.endSum, 0, 'f', 2);
        if (isOverdue) {
            int daysLate = QDate::fromString(r.issueDate, "dd.MM.yyyy").addDays(r.termDays).daysTo(today);
            double penaltyAmt = (daysLate > 0) ? CreditCalculator::calculatePenalty(r.endSum, r.penaltyPercent, daysLate) : 0.0;
            out << QString("  Штраф: %1 руб. ( %2% )\n").arg(penaltyAmt, 0, 'f', 2).arg(r.penaltyPercent, 0, 'f', 2);
        }
        out << QString("  Статус:     %1\n").arg(isOverdue ? "ПРОСРОЧЕН" : "активен");
        out << "\n";
    }

    out << "========================\n";
    out << QString("Просроченных: %1 из %2\n").arg(overdue).arg(records.size());

    file.close();
    QMessageBox::information(this, "Готово",
                             QString("Отчёт сохранён:\n%1").arg(path));
}
