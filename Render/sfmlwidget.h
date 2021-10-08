#ifndef SFMLWIDGET_H
#define SFMLWIDGET_H

#include "canvas.h"
#include <QGridLayout>
#include <QWidget>

class SFMLWidget : public QWidget
{
    Q_OBJECT
  private:
    Canvas *sfmlCanvasWidget;
    QGridLayout *gridLayout;

  private slots:
    void onClose();

  public:
    explicit SFMLWidget(QWidget *parent = nullptr);
    ~SFMLWidget();
};

#endif // SFMLWIDGET_H
