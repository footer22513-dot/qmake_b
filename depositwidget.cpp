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
#include <QInputDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QDir>
#include <QTextCodec>
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
    // Кнопка "Пополнить" рядом с "Удалить"
    topUpBtn = new QPushButton("💰 Пополнить");
    topUpBtn->setStyleSheet("font-size:14px;padding:8px;background:#388E3C;color:white;border-radius:5px;");
    connect(topUpBtn, &QPushButton::clicked, this, &DepositTableWidget::onTopUpClicked);
    ctrl->addWidget(topUpBtn);

    // Withdraw button for partial withdrawal
    withdrawBtn = new QPushButton("💸 Снять");
    withdrawBtn->setStyleSheet("font-size:14px;padding:8px;background:#D32F2F;color:white;border-radius:5px;");
    connect(withdrawBtn, &QPushButton::clicked, this, &DepositTableWidget::onWithdrawClicked);
    ctrl->addWidget(withdrawBtn);

    backBtn = new QPushButton("← НАЗАД");
    backBtn->setStyleSheet("font-size:14px;padding:8px;background:#555;color:white;border-radius:5px;");
    connect(backBtn, &QPushButton::clicked, this, &DepositTableWidget::navigateToAdmin);
    ctrl->addWidget(backBtn);
    // Export report button
    exportBtn = new QPushButton("📄 Экспорт отчёта");
    exportBtn->setStyleSheet("font-size:14px;padding:8px;background:#1976D2;color:white;border-radius:5px;");
    connect(exportBtn, &QPushButton::clicked, this, &DepositTableWidget::onExportReport);
    ctrl->addWidget(exportBtn);

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
void DepositTableWidget::onTopUpClicked() {
    // existing top‑up logic (unchanged)
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this, tr("\u0412\u043d\u0438\u043c\u0430\u043d\u0438\u0435"), tr("\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u0437\u0430\u043f\u0438\u0441\u044c.")); return; }
    int id = table->item(row, 0)->text().toInt();
    bool ok = false;
    double amount = QInputDialog::getDouble(this, tr("\u041f\u043e\u043f\u043e\u043b\u043d\u0435\u043d\u0438\u0435 \u0432\u043a\u043b\u0430\u0434\u0430"), tr("\u0421\u0443\u043c\u043c\u0430:"), 0.0, 0.0, 1e9, 2, &ok);
    if (!ok) return;
    auto it = std::find_if(records.begin(), records.end(), [id](const DepositRecord& r){ return r.id == id; });
    if (it == records.end()) return;
    // Добавляем сумму к начальной и пересчитываем конечную
    it->startSum = qMax(0.0, it->startSum + amount);
    double rate = it->ratePercent;
    int days = it->termDays;
    it->endSum = qMax(0.0, it->startSum * (1.0 + rate * days / 36500.0));
    refreshTable(records);
    emit recordUpdated(*it);
}

// Partial withdrawal handling
void DepositTableWidget::onWithdrawClicked() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, tr("Внимание"), tr("Выберите запись."));
        return;
    }
    int id = table->item(row, 0)->text().toInt();
    auto it = std::find_if(records.begin(), records.end(), [id](const DepositRecord& r){ return r.id == id; });
    if (it == records.end()) return;
    bool ok = false;
    double amount = QInputDialog::getDouble(this, tr("Снятие части вклада"), tr("Сумма:"), 0.0, 0.0, it->startSum, 2, &ok);
    if (!ok) return;
    // Ensure withdrawal does not exceed current balance
    if (amount > it->startSum) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Сумма снятия превышает текущую сумму вклада."));
        return;
    }
    it->startSum = qMax(0.0, it->startSum - amount);
    double rate = it->ratePercent;
    int days = it->termDays;
    it->endSum = qMax(0.0, it->startSum * (1.0 + rate * days / 36500.0));
    refreshTable(records);
    emit recordUpdated(*it);
}

void DepositTableWidget::onExportReport() {
    int row = table->currentRow();
    QString clientName = (row >= 0) ? table->item(row, 1)->text() : "все_клиенты";
    clientName.replace(" ", "_");

    QString defaultName = QDir::homePath() + QString("/отчёт_вклады_%1_%2.txt")
                                                 .arg(clientName)
                                                 .arg(QDate::currentDate().toString("dd-MM-yyyy"));

    QString path = QFileDialog::getSaveFileName(
        this, "Сохранить отчёт", defaultName, "Текстовые файлы (*.txt)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);

    out.setCodec(QTextCodec::codecForName("UTF-8"));

    out << "=== ОТЧЁТ ПО ВКЛАДАМ ===\n";
    out << QString("Дата формирования: %1\n").arg(QDate::currentDate().toString("dd.MM.yyyy"));
    out << QString("Всего записей: %1\n\n").arg(records.size());

    QDate today = QDate::currentDate();
    int overdue = 0;

    for (const auto& r : records) {
        QDate d = QDate::fromString(r.issueDate, "dd.MM.yyyy");
        QDate due = d.isValid() ? d.addDays(r.termDays) : QDate();
        bool isOverdue = d.isValid() && (due < today) && (r.endSum > 0);
        if (isOverdue) ++overdue;

        out << QString("ID: %1\n").arg(r.id);
        out << QString("  ФИО:        %1\n").arg(r.fullName);
        out << QString("  Телефон:    %1\n").arg(r.phone);
        out << QString("  Открыт:     %1\n").arg(r.issueDate);
        out << QString("  Срок:       %1 дн.\n").arg(r.termDays);
        out << QString("  Дата конца: %1\n").arg(due.isValid() ? due.toString("dd.MM.yyyy") : "—");
        out << QString("  Ставка:     %1%\n").arg(r.ratePercent, 0, 'f', 2);
        out << QString("  Нач. сумма: %1 руб.\n").arg(r.startSum, 0, 'f', 2);
        out << QString("  Кон. сумма: %1 руб.\n").arg(r.endSum, 0, 'f', 2);
        out << QString("  Статус:     %1\n").arg(isOverdue ? "ПРОСРОЧЕН" : "активен");
        out << "\n";
    }

    out << "========================\n";
    out << QString("Просроченных: %1 из %2\n").arg(overdue).arg(records.size());

    file.close();
    QMessageBox::information(this, "Готово",
                             QString("Отчёт сохранён:\n%1").arg(path));
}
