#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(400, 400);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("MainWindow{border-image: url(:/media/menuTextures/menu_background_image.jpg)}");
}

void MainWindow::initGameWidget(const TileMap *tileMap, Player *player)
{
    centralWidget = new MainWidget(tileMap, player, this);
    centralWidget->hide();
}

#include <signal.h>
#include <windows.h>

void handler_sigsegv(int signum)
{
    MessageBoxA(NULL, "SIGSEGV Error!", "POSIX Signal", MB_ICONSTOP);
    // открепить обработчик и явно завершить приложение
    signal(signum, SIG_DFL);
    exit(3);
}

void MainWindow::startGame()
{
    QRect rec = QApplication::desktop()->screenGeometry();

    // Задаю размеры глобального виджета, как 1/2 и 1/2
    // от размеров всего экрана
    int height = rec.height() / 2;
    int width = rec.width() / 2;
    resize(width, height);
    move(QPoint(300, 300));

    setCentralWidget(centralWidget);
    centralWidget->show();

    QPixmap menupix(":/media/menuTextures/menu.png");
    QPixmap quitpix(":/media/menuTextures/exit.png");

    toolbar = addToolBar("main toolbar");
    QAction *quit = toolbar->addAction(QIcon(quitpix), "quit");

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    toolbar->setIconSize(QSize(40, 40));
    toolbar->setStyleSheet("background: black");
    toolbar->setMovable(false);
}

void MainWindow::continueGame()
{
    setCentralWidget(centralWidget);
    centralWidget->hide();
}
