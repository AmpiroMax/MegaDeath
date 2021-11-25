#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(400, 400);

    menuWidget = new MenuWidget(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-image: url(:/media/menuTextures/menu_background_image.jpg)");
    setCentralWidget(menuWidget);

    connect(menuWidget, &MenuWidget::startGame, this, &MainWindow::startGame);
}

void MainWindow::initGameWidget(const TileMap *tileMap, Player *player)
{
    centralWidget = new MainWidget(tileMap, player, this);
    centralWidget->hide();
}

void MainWindow::showMenu()
{
    centralWidget->hide();
    toolbar->hide();
    resize(400, 400);
    // setCentralWidget(menuWidget);
    // menuWidget->show();
}

void MainWindow::startGame()
{
    QRect rec = QApplication::desktop()->screenGeometry();

    menuWidget->hide();

    // Задаю размеры глобального виджета, как 1/2 и 1/2
    // от размеров всего экрана
    int height = rec.height();
    int width = rec.width();
    resize(width, height);
    move(QPoint(0, 0));

    setCentralWidget(centralWidget);
    centralWidget->show();

    QPixmap menupix(":/media/menuTextures/menu.png");
    QPixmap quitpix(":/media/menuTextures/exit.png");

    toolbar = addToolBar("main toolbar");
    QAction *menuOpen = toolbar->addAction(QIcon(menupix), "menu");
    QAction *quit = toolbar->addAction(QIcon(quitpix), "quit");

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(menuOpen, &QAction::triggered, this, &MainWindow::showMenu);

    toolbar->setIconSize(QSize(40, 40));
    toolbar->setStyleSheet("background: black");
    toolbar->setMovable(false);

    disconnect(menuWidget, &MenuWidget::startGame, this, &MainWindow::startGame);
    connect(menuWidget, &MenuWidget::continueGame, this, &MainWindow::continueGame);
}

void MainWindow::continueGame()
{
    menuWidget->show();
    setCentralWidget(centralWidget);
    centralWidget->hide();
}
