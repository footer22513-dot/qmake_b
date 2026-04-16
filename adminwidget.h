#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include "basewidget.h"

class QPushButton;
class QLabel;

class AdminWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = nullptr);

signals:
    void loadDatabaseRequested();
    void saveDatabaseRequested();

private:
    QPushButton* creditTableBtn;
    QPushButton* depositTableBtn;
    QPushButton* loadDbBtn;
    QPushButton* saveDbBtn;
    QPushButton* backBtn;
    QLabel*      titleLabel;
};

#endif // ADMINWIDGET_H
