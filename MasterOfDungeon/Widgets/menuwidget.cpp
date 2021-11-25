#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);

    startButton = new QPushButton("START", this);
    exitButton = new QPushButton("EXIT", this);
    settingButton = new QPushButton("SETTINGS", this);

    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

    grid->addItem(spacer, 0, 0, 1, 5);
    grid->addWidget(startButton);
    grid->addWidget(settingButton);
    grid->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(startButton, &QPushButton::clicked, this, &MenuWidget::startButtonClicked);
}

void MenuWidget::startButtonClicked()
{
    emit startGame();

    startButton->setText("CONTINUE");
    startButton->disconnect();
    connect(startButton, &QPushButton::clicked, this, &MenuWidget::hide);
}

void MenuWidget::continueButtonClicked()
{
    emit continueGame();
}
