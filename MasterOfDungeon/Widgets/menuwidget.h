#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>

class MenuWidget : public QWidget
{
  private:
    Q_OBJECT

    QPushButton *startButton;
    QPushButton *exitButton;
    QPushButton *settingButton;

    QGridLayout *grid;

  public:
    explicit MenuWidget(QWidget *parent = nullptr);

  private slots:
    void startButtonClicked();
    void continueButtonClicked();

  signals:
    void startGame();
    void continueGame();
};

#endif // MENUWIDGET_H
