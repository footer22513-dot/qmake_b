#include "piechartwidget.h"
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

PieChartWidget::PieChartWidget(QWidget *parent) : QWidget(parent) {
    // Layout
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(32, 32, 32, 24);
    layout->setSpacing(16);
    setLayout(layout);

    QLabel *chartTitle = new QLabel("АНАЛИТИКА");
    chartTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(chartTitle);

    QFrame *divider = new QFrame;
    divider->setFrameShape(QFrame::HLine);
    layout->addWidget(divider);

    // Series
    series = new QPieSeries();
    series->append("КРЕДИТЫ", 1);
    series->append("ВКЛАДЫ", 1);
    series->setHoleSize(0.4);

    QPieSlice *slice1 = series->slices().at(0);
    slice1->setLabelVisible(true);
    QPieSlice *slice2 = series->slices().at(1);
    slice2->setLabelVisible(true);

    // Chart
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setBackgroundPen(Qt::NoPen);
    chart->legend()->hide();
    chart->setMargins(QMargins(0,0,0,0));
    chart->layout()->setContentsMargins(0,0,0,0);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(420);
    layout->addWidget(chartView, 1);

    // Legend placeholder
    QHBoxLayout *legend = new QHBoxLayout;
    legend->setSpacing(24);
    legend->setContentsMargins(0,8,0,8);
    legend->addStretch();
    legend->addStretch();
    layout->addLayout(legend);
}

void PieChartWidget::updateData(int credits, int deposits) {
    QPieSlice *s1 = series->slices().at(0);
    QPieSlice *s2 = series->slices().at(1);
    if (credits == 0 && deposits == 0) {
        s1->setValue(1);
        s2->setValue(1);
        s1->setLabel("КРЕДИТЫ: 0");
        s2->setLabel("ВКЛАДЫ: 0");
        s1->setBrush(QColor("#444466"));
        s2->setBrush(QColor("#444466"));
    } else {
        s1->setValue(credits);
        s2->setValue(deposits);
        s1->setLabel(QString("КРЕДИТЫ: %1").arg(credits));
        s2->setLabel(QString("ВКЛАДЫ: %1").arg(deposits));
        s1->setBrush(QColor("#ffd166"));
        s2->setBrush(QColor("#06d6a0"));
    }
    s1->setLabelVisible(credits > 0);
    s2->setLabelVisible(deposits > 0);
}
