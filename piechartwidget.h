#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

class PieChartWidget : public QWidget {
public:
    explicit PieChartWidget(QWidget *parent = nullptr);
    void updateData(int credits, int deposits);
private:
    QPieSeries *series;
    QChart *chart;
    QChartView *chartView;
    QVBoxLayout *layout;
};