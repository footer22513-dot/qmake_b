#include "adminwidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

AdminWidget::AdminWidget(QWidget *parent) : BaseWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 30, 40, 30);
    layout->setSpacing(14);

    titleLabel = new QLabel("ПАНЕЛЬ АДМИНИСТРАТОРА");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size:44px; font-weight:bold;");
    layout->addWidget(titleLabel);
    layout->addStretch();

    auto btn = [&](const QString& text, const QString& color) {
        auto* b = new QPushButton(text);
        b->setMinimumHeight(54);
        b->setStyleSheet(QString("font-size:26px; background:%1; color:white; border-radius:8px;").arg(color));
        return b;
    };

    analytics = btn("АНАЛИТИКА", "#6A1B9A");
    creditTableBtn  = btn("📋  ТАБЛИЦА ЗАЙМОВ",   "#388E3C");
    depositTableBtn = btn("💰  ТАБЛИЦА ВКЛАДОВ",  "#1976D2");
    loadDbBtn       = btn("📂  ЗАГРУЗИТЬ БАЗУ",   "#F57C00");
    saveDbBtn       = btn("💾  ВЫГРУЗИТЬ БАЗУ",   "#6A1B9A");
    backBtn         = btn("← НАЗАД",              "#555555");

    connect(analytics, &QPushButton::clicked, this, &AdminWidget::navigateToAnalytics);
    connect(creditTableBtn,  &QPushButton::clicked, this, &AdminWidget::navigateToCreditTable);
    connect(depositTableBtn, &QPushButton::clicked, this, &AdminWidget::navigateToDepositTable);
    connect(loadDbBtn,       &QPushButton::clicked, this, &AdminWidget::loadDatabaseRequested);
    connect(saveDbBtn,       &QPushButton::clicked, this, &AdminWidget::saveDatabaseRequested);
    connect(backBtn,         &QPushButton::clicked, this, &AdminWidget::navigateToLogin);

    layout->addWidget(analytics);
    layout->addWidget(creditTableBtn);
    layout->addWidget(depositTableBtn);
    layout->addSpacing(8);
    layout->addWidget(loadDbBtn);
    layout->addWidget(saveDbBtn);
    layout->addStretch();
    layout->addWidget(backBtn);
    setLayout(layout);
}
