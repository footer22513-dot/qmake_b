#ifndef CREDITTABLEWIDGET_H
#define CREDITTABLEWIDGET_H

#include "basewidget.h"
#include <QList>
#include <QDate>

// Структура точно по ТЗ п.3.2.1
struct CreditRecord {
    int     id;
    QString fullName;
    QString phone;
    QString issueDate;
    int     termDays;
    int     rateType;
    double  ratePercent;
    int     paymentPeriod;
    double  startSum;
    double  endSum;
    bool    earlyRepay;
};

class QTableWidget;
class QLineEdit;
class QSpinBox;
class QDateEdit;
class QPushButton;
class QLabel;
class QTableWidgetItem;

class CreditTableWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit CreditTableWidget(QWidget *parent = nullptr);

    void setRecords(const QList<CreditRecord>& records);
    QList<CreditRecord> getRecords() const;

signals:
    void recordDeleted(int id);
    void recordUpdated(const CreditRecord& record);  // Для сохранения изменений

private slots:
    void onSearchClicked();
    void onResetClicked();
    void onDeleteClicked();
    void onItemChanged(QTableWidgetItem* item);      // Обработчик редактирования

private:
    QTableWidget* table;
    QLineEdit*    searchInput;
    QSpinBox*     sumMin;
    QSpinBox*     sumMax;
    QDateEdit*    dateFrom;
    QDateEdit*    dateTo;
    QPushButton*  searchBtn;
    QPushButton*  resetBtn;
    QPushButton*  delBtn;
    QPushButton*  backBtn;

    QList<CreditRecord> records;
    bool m_isRefreshing = false;                      // Флаг блокировки сигналов

    void refreshTable(const QList<CreditRecord>& data);
    static QString rateTypeName(int t);
    static QString periodName(int p);
};

#endif // CREDITTABLEWIDGET_H
