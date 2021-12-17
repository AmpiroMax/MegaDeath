#include "graphiccontroller.h"

GraphicController::GraphicController()
{
}

void GraphicController::initParametrs(GameWidget *_gameWidget, const TileMap *_WM, const UnitMap *_UM,
                                      const Player *_player, PlayerController *_PLC)
{
    // Назначаю свои указатели на объекты карты юнитов, игровой карты, самого игрока
    // также на gameWidget, за который данный контроллер ответственный
    // и дополнительно передаётся контроллер игрока, для передачи ему сигналов от ввода пользователя
    gameWidget = _gameWidget;
    WM = _WM;
    UM = _UM;
    player = _player;
    PLC = _PLC;

    // Подсоединение сигналов gameWidgeta с соответствующими им слотами контроллера
    connect(gameWidget, &GameWidget::paintEventSignal, this, &GraphicController::onPaintEvent);
    connect(gameWidget, &GameWidget::mouseEventSignal, this, &GraphicController::onMouseClickEvent);
    connect(gameWidget, &GameWidget::keyPressEventSignal, this, &GraphicController::onKeyPressEvent);
    connect(gameWidget, &GameWidget::showEventSignal, this, &GraphicController::onShowEvent);
    connect(gameWidget, &GameWidget::resizeEventSignal, this, &GraphicController::onResizeEvent);
}

void GraphicController::onTimeOutEvent()
{
    // При каждом такте игры вызываем процесс отрисовки
    paint();
}

void GraphicController::processMouseEvents(Cell mouseCell)
{
    // Данная функция расчитана на определение того, куд нажал пользователь
    // Если было нажатие на одного из противников мы будем открывать меню, но
    // это у нас в планах на следующих этапах.
    // На данный момент, игрок может нажать мышкой тольько на пустое поле,
    // что соответствует указанию игроку куда переместиться. Собственно
    // здесь вызываем у контроллера игрока метод пересчета траектории движения
    // и передаём тот Cell на который было совершено нажатие
    PLC->recalculatePath(mouseCell);
}

void GraphicController::processKeyboardEvents(int code)
{
    // Есть возможность обработки нажатий клавиатуры

    switch (code)
    {
        case Qt::Key_Z:
        {
            // Метод исключительно для демонстрации возможности легкой обработки надатий клавиатуры
            // и некоторая вспомогательная функция при дебаге
            gameWidget->setViewZoom(1.1);
            break;
        }
        case Qt::Key_X:
        {
            // Метод исключительно для демонстрации возможности легкой обработки надатий клавиатуры
            // и некоторая вспомогательная функция при дебаге
            gameWidget->setViewZoom(0.9);
            break;
        }
    }
}

Cell GraphicController::calculateMarginForMap(const TileMatrix &localMap, int marginSize)
{
    // Функция считает координаты точки, откуда должна быть нарисована локальная игровая карта

    // Получение координат игрока в тайлах
    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerPosition = {tmp.x, tmp.y};

    // Опрределение размеров локальной карты, которую хотим отрисовать
    GYM::Point2D<int> shape(WM->shape().x, WM->shape().y);
    int horMapSize = localMap.size();
    int verMapSize = localMap[0].size();

    // Смещение точки отрисовки относительно положения игрока
    int deltaX = 0;
    int deltaY = 0;

    // Определение смещения для координаты Х
    if (shape.x - playerPosition.first > marginSize)
        deltaX = std::min(horMapSize / 2, playerPosition.first);
    else
        deltaX = horMapSize - shape.x + playerPosition.first;

    // Определение смещения для координаты У
    if (shape.y - playerPosition.second > marginSize)
        deltaY = std::min(verMapSize / 2, playerPosition.second);
    else
        deltaY = verMapSize - shape.y + playerPosition.second;

    // Возвращаем координату того тайла, откуда необходимо рисовать рисовать локальную карту
    return Cell(playerPosition.first - deltaX, playerPosition.second - deltaY);
}

void GraphicController::paint()
{
    // Функция отрисовки содержимого игрового мира

    // Получаем координаты игрока в тайлах и чанках, так как разные функции
    // требуют координаты в различных системах координаты
    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerPosition = {tmp.x, tmp.y};
    GYM::Point2D<int> playerChunk = getUnitChunkPos(player);

    // Получаем по координатам в тайлах локальную карту мира
    TileMatrix localWM = WM->getCentredLocalMap(playerPosition, 100, 100);
    // Получаем по координатам в чанках локальную карту юнитов
    UnitChunk localUM = UM->getLocalUnitMap(playerChunk);

    // Определяем координату тайла, с которого необходимо рисовать
    // локальную карту мира
    Cell X0Y0 = calculateMarginForMap(localWM, 100);

    // gameWidget - sfml renderWIndow, поэтому использую функционал sfml

    // зачищаем экран перед новой отрисовкой
    gameWidget->clear();
    // обновлчем положение камеры мира на позицию игрока, тем самым
    // поддерживаем нахождение игрока в центре экрана
    gameWidget->setViewPosition(player->getPosition());
    // рисуем игровые объекты
    gameWidget->drawMap(localWM, X0Y0);
    gameWidget->drawUnits(localUM);
    gameWidget->drawPlayer(player);
    // отображаем на экран результат отрисовки
    gameWidget->display();
}

void GraphicController::onPaintEvent()
{
    // У виджета есть событие отрисовки, его по-хорошему
    // нельзя было оставлять просто так, поэтому было решено,
    // что логично при этом событии вызывать отрисовку
    paint();
}

void GraphicController::onMouseClickEvent(GYM::Point2D<int> pos)
{
    // Функция получает от виджета координаты курсора мыши в момент нажатия
    // относительно верхнего левого угла виджета
    // Поэтому тут мы пересчитываем эти координаты в координаты TileMap
    int width = gameWidget->size().width();
    int height = gameWidget->size().height();

    GYM::Point2D<int> tmp = getUnitTilePos(player);
    Cell playerCell = {tmp.x, tmp.y};

    int xm = (pos.x - width / 2) / GYM::tileSize + playerCell.first;
    int ym = (pos.y - height / 2) / GYM::tileSize + playerCell.second;

    // После пересчета коориднат вызываем обработку события
    processMouseEvents(Cell(xm, ym));
}

void GraphicController::onKeyPressEvent(int code)
{
    // При вызове этой функции обрабатывает событие нажатие клавиши
    // номер которой ледит в переменной code
    processKeyboardEvents(code);
}

void GraphicController::onShowEvent()
{
    // На данном этапе это событие не требует особой обработки, однако оно будет крайне важно
    // кода будет добавляться вомзможность открывать меню и в целом взаимодействовать с виджетом
}

void GraphicController::onResizeEvent()
{
    // В случае изменения размера виджета, необходимо поменять
    // размер и SFML RenderWindow окну, для правильного отображения

    int width = gameWidget->size().width();
    int height = gameWidget->size().height();

    // обновляю размер sfml window
    gameWidget->setSize(sf::Vector2u(width, height));
    // обновляю размеры камеры, для корректного отображения масштаба
    gameWidget->setViewSize(width, height);
}
