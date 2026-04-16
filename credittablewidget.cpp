#include "credittablewidget.h"
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

CreditTableWidget::CreditTableWidget(QWidget *parent) : BaseWidget(parent) {
    auto* main = new QHBoxLayout(this);

    // Таблица — колонки строго по ТЗ п.3.2.1
    table = new QTableWidget;
    table->setColumnCount(10);
    table->setHorizontalHeaderLabels({
        "ID", "ФИО", "Телефон", "Дата выдачи",
        "Срок (дн.)", "Тип ставки", "Ставка (%)",
        "Периодичность", "Нач. сумма", "Кон. сумма"
    });
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // РАЗРЕШАЕМ РЕДАКТИРОВАНИЕ
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    table->setSortingEnabled(true);
    main->addWidget(table, 3);

    // Панель фильтрации — по ТЗ п.3.1.5
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

    backBtn = new QPushButton("← НАЗАД");
    backBtn->setStyleSheet("font-size:14px;padding:8px;background:#555;color:white;border-radius:5px;");
    connect(backBtn, &QPushButton::clicked, this, &CreditTableWidget::navigateToAdmin);
    ctrl->addWidget(backBtn);

    // Подключаем сигнал изменения ячейки
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
    m_isRefreshing = true;  // Блокируем сигналы на время обновления
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

        // Тип ставки - не редактируемый текстом (только для отображения)
        QTableWidgetItem* rateTypeItem = new QTableWidgetItem(rateTypeName(r.rateType));
        rateTypeItem->setFlags(rateTypeItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 5, rateTypeItem);

        table->setItem(row, 6, new QTableWidgetItem(QString::number(r.ratePercent,'f',2)+"%"));

        // Периодичность - не редактируемая текстом
        QTableWidgetItem* periodItem = new QTableWidgetItem(periodName(r.paymentPeriod));
        periodItem->setFlags(periodItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 7, periodItem);

        table->setItem(row, 8, new QTableWidgetItem(QString::number(r.startSum,'f',2)));
        table->setItem(row, 9, new QTableWidgetItem(QString::number(r.endSum,'f',2)));
    }

    table->setSortingEnabled(true);
    m_isRefreshing = false;  // Разблокируем сигналы
}

void CreditTableWidget::onSearchClicked() {
    QString f = searchInput->text().trimmed().toLower();
    double  minS = sumMin->value(), maxS = sumMax->value();
    QDate   df = dateFrom->date(), dt = dateTo->date();

    QList<CreditRecord> out;
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

void CreditTableWidget::onResetClicked() {
    searchInput->clear();
    sumMin->setValue(0); sumMax->setValue(999999999);
    dateFrom->setDate(QDate(2000,1,1)); dateTo->setDate(QDate::currentDate().addYears(10));
    refreshTable(records);
}

void CreditTableWidget::onDeleteClicked() {
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this,"Внимание","Выберите строку."); return; }
    int id = table->item(row, 0)->text().toInt();

    if (QMessageBox::Yes == QMessageBox::question(this,"Удаление","Удалить выбранную запись?", QMessageBox::Yes|QMessageBox::No)) {

        // FIX: Changed 'allRecords' to 'records'
        for (auto it = records.begin(); it != records.end(); ) {
            if (it->id == id) {
                it = records.erase(it);
            } else {
                ++it;
            }
        }

        refreshTable(records);
        emit recordDeleted(id);
    }
}

void CreditTableWidget::onItemChanged(QTableWidgetItem* item) {
    if (m_isRefreshing) return;  // Игнорируем программные изменения

    int row = item->row();
    int col = item->column();

    if (row < 0 || row >= table->rowCount()) return;

    // Получаем ID из первой колонки (он не меняется)
    int id = table->item(row, 0)->text().toInt();

    // Ищем запись в списке
    auto it = std::find_if(records.begin(), records.end(),
                           [id](const CreditRecord& r) { return r.id == id; });
    if (it == records.end()) return;

    QString newVal = item->text();

    // Обновляем поле в зависимости от колонки
    switch(col) {
    case 1: it->fullName = newVal; break;
    case 2: it->phone = newVal; break;
    case 3: it->issueDate = newVal; break;  // Формат dd.MM.yyyy
    case 4: it->termDays = newVal.toInt(); break;
    case 6: // Ставка — убираем символ % если есть
        it->ratePercent = newVal.remove("%").trimmed().toDouble();
        break;
    case 8: it->startSum = newVal.toDouble(); break;
    case 9: it->endSum = newVal.toDouble(); break;
    default: return; // Для остальных колонок ничего не делаем
    }

    emit recordUpdated(*it);  // Уведомляем MainWindow о изменении
}

QString CreditTableWidget::rateTypeName(int t) {
    switch(t){ case 1: return "От суммы"; case 2: return "От срока"; default: return "Фиксированная"; }
}

QString CreditTableWidget::periodName(int p) {
    switch(p){ case 1: return "Ежеквартально"; case 2: return "Ежегодно"; default: return "Ежемесячно"; }
}
