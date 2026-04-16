#include "depositwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>

DepositTableWidget::DepositTableWidget(QWidget *parent) : BaseWidget(parent) {
    auto* main = new QHBoxLayout(this);

    table = new QTableWidget;
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels({
        "ID", "ФИО", "Телефон", "Дата начала",
        "Срок (дн.)", "Тип ставки", "Ставка (%)",
        "Нач. сумма", "Кон. сумма"
    });
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // РАЗРЕШАЕМ РЕДАКТИРОВАНИЕ
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    table->setSortingEnabled(true);
    main->addWidget(table, 3);

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

    ctrl->addWidget(new QLabel("Дата начала от:"));
    dateFrom = new QDateEdit(QDate(2000,1,1)); dateFrom->setCalendarPopup(true);
    dateFrom->setDisplayFormat("dd.MM.yyyy");
    ctrl->addWidget(dateFrom);
    ctrl->addWidget(new QLabel("Дата начала до:"));
    dateTo = new QDateEdit(QDate::currentDate().addYears(10)); dateTo->setCalendarPopup(true);
    dateTo->setDisplayFormat("dd.MM.yyyy");
    ctrl->addWidget(dateTo);

    searchBtn = new QPushButton("🔍 ПОИСК");
    searchBtn->setStyleSheet("font-size:14px;padding:8px;background:#1976D2;color:white;border-radius:5px;");
    connect(searchBtn, &QPushButton::clicked, this, &DepositTableWidget::onSearchClicked);
    ctrl->addWidget(searchBtn);

    resetBtn = new QPushButton("СБРОСИТЬ");
    resetBtn->setStyleSheet("font-size:14px;padding:6px;background:#78909C;color:white;border-radius:5px;");
    connect(resetBtn, &QPushButton::clicked, this, &DepositTableWidget::onResetClicked);
    ctrl->addWidget(resetBtn);

    ctrl->addStretch();

    delBtn = new QPushButton("🗑 УДАЛИТЬ");
    delBtn->setStyleSheet("font-size:14px;padding:8px;background:#f44336;color:white;border-radius:5px;");
    connect(delBtn, &QPushButton::clicked, this, &DepositTableWidget::onDeleteClicked);
    ctrl->addWidget(delBtn);

    backBtn = new QPushButton("← НАЗАД");
    backBtn->setStyleSheet("font-size:14px;padding:8px;background:#555;color:white;border-radius:5px;");
    connect(backBtn, &QPushButton::clicked, this, &DepositTableWidget::navigateToAdmin);
    ctrl->addWidget(backBtn);

    // Подключаем сигнал изменения ячейки
    connect(table, &QTableWidget::itemChanged, this, &DepositTableWidget::onItemChanged);

    setLayout(main);
}

void DepositTableWidget::setRecords(const QList<DepositRecord>& data) {
    records = data;
    refreshTable(records);
}

QList<DepositRecord> DepositTableWidget::getRecords() const {
    return records;
}

void DepositTableWidget::refreshTable(const QList<DepositRecord>& data) {
    m_isRefreshing = true;
    table->setSortingEnabled(false);
    table->setRowCount(0);

    for (const auto& r : data) {
        int row = table->rowCount();
        table->insertRow(row);

        // ID - не редактируемый
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(r.id));
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 0, idItem);

        table->setItem(row, 1, new QTableWidgetItem(r.fullName));
        table->setItem(row, 2, new QTableWidgetItem(r.phone));
        table->setItem(row, 3, new QTableWidgetItem(r.issueDate));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(r.termDays)));

        // Тип ставки - не редактируемый
        QTableWidgetItem* rateTypeItem = new QTableWidgetItem(rateTypeName(r.rateType));
        rateTypeItem->setFlags(rateTypeItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 5, rateTypeItem);

        table->setItem(row, 6, new QTableWidgetItem(QString::number(r.ratePercent,'f',2)+"%"));
        table->setItem(row, 7, new QTableWidgetItem(QString::number(r.startSum,'f',2)));
        table->setItem(row, 8, new QTableWidgetItem(QString::number(r.endSum,'f',2)));
    }

    table->setSortingEnabled(true);
    m_isRefreshing = false;
}

void DepositTableWidget::onSearchClicked() {
    QString f = searchInput->text().trimmed().toLower();
    double  minS = sumMin->value(), maxS = sumMax->value();
    QDate   df = dateFrom->date(), dt = dateTo->date();

    QList<DepositRecord> out;
    for (const auto& r : records) {
        QDate d = QDate::fromString(r.issueDate, "dd.MM.yyyy");
        bool nameOk = f.isEmpty() || r.fullName.toLower().contains(f)
                      || r.phone.contains(f)
                      || QString::number(r.id).contains(f);
        bool sumOk  = r.startSum >= minS && r.startSum <= maxS;
        bool dateOk = (!d.isValid()) || (d >= df && d <= dt);
        if (nameOk && sumOk && dateOk) out.append(r);
    }
    refreshTable(out);
}

void DepositTableWidget::onResetClicked() {
    searchInput->clear();
    sumMin->setValue(0); sumMax->setValue(999999999);
    dateFrom->setDate(QDate(2000,1,1)); dateTo->setDate(QDate::currentDate().addYears(10));
    refreshTable(records);
}
#include <algorithm>
void DepositTableWidget::onDeleteClicked() {
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this,"Внимание","Выберите строку."); return; }
    int id = table->item(row, 0)->text().toInt();

    if (QMessageBox::Yes == QMessageBox::question(this,"Удаление","Удалить выбранную запись?",
                                                  QMessageBox::Yes|QMessageBox::No)) {

        // FIX: Replace removeIf with std::remove_if + erase (compatible with older Qt)
        records.erase(std::remove_if(records.begin(), records.end(), [id](const DepositRecord& r){
            return r.id == id;
        }), records.end());

        refreshTable(records);
        emit recordDeleted(id);
    }
}

void DepositTableWidget::onItemChanged(QTableWidgetItem* item) {
    if (m_isRefreshing) return;

    int row = item->row();
    int col = item->column();

    if (row < 0 || row >= table->rowCount()) return;

    int id = table->item(row, 0)->text().toInt();

    auto it = std::find_if(records.begin(), records.end(),
                           [id](const DepositRecord& r) { return r.id == id; });
    if (it == records.end()) return;

    QString newVal = item->text();

    switch(col) {
    case 1: it->fullName = newVal; break;
    case 2: it->phone = newVal; break;
    case 3: it->issueDate = newVal; break;
    case 4: it->termDays = newVal.toInt(); break;
    case 6:
        it->ratePercent = newVal.remove("%").trimmed().toDouble();
        break;
    case 7: it->startSum = newVal.toDouble(); break;
    case 8: it->endSum = newVal.toDouble(); break;
    default: return;
    }

    emit recordUpdated(*it);
}

QString DepositTableWidget::rateTypeName(int t) {
    switch(t){ case 1: return "От суммы"; case 2: return "От срока"; default: return "Фиксированная"; }
}

QString DepositTableWidget::periodName(int p) {
    switch(p){ case 1: return "Ежеквартально"; case 2: return "Ежегодно"; default: return "Ежемесячно"; }
}
