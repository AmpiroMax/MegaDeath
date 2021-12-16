#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include "menuwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QToolBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
  private:
    MainWidget *centralWidget;
    QToolBar *toolbar;

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initGameWidget(const TileMap *, Player *);

  private slots:
    void startGame();
    void continueGame();
};

#endif // MAINWINDOW_H
