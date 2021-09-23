#ifndef IDRAWOBJ_H
#define IDRAWOBJ_H
#include "IObj.h"

class IDrawObj : public IObj
{
  public:
    // Метод отрисовки объекта на экран
    virtual void draw() = 0;

    // Отрисовка доп. информации об объекте
    // при наведении на объект мышкой или ином действии
    virtual void drawInfo() = 0;
};

#endif // IDRAWOBJ_H
