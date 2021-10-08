#include "Render/sfmlwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SFMLWidget w;
    w.show();
    return a.exec();
}
