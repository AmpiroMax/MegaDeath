#ifndef CANVAS_H
#define CANVAS_H

#include <QMouseEvent>
#include <QTimer>
#include <QWidget>
#include <SFML/Graphics.hpp>

#include "Handlers/keyboardhandler.h"
#include "Handlers/mousehandler.h"
#include "worldmap.h"

class Canvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

  private:
    QTimer timer;

    sf::Texture canvasTexture;
    sf::Sprite canvasSprite;
    sf::Color clearColor;
    sf::View view;

    WorldMap gameMap;
    KeyBoardHandler keyHandler;
    MouseHandler mouseHandler;
    bool isInited;

    std::pair<int, int> targetPos;
    std::pair<int, int> targetVelocity;

  private:
    void onInit();
    void onUpdate();
    void drawMap();

    virtual QPaintEngine *paintEngine() const override;

    virtual void showEvent(QShowEvent *) override;
    virtual void paintEvent(QPaintEvent *) override;

  private slots:
    void onTimeout();
    void onCloseKey();
    void onMoveKey(int);
    void onZoomKey(int);

    void onMouseClicked(int, int);

  signals:
    void closeWindow();

  public:
    explicit Canvas(QWidget *parent = nullptr, uint frameTime = 1);
};

#endif // CANVAS_H
