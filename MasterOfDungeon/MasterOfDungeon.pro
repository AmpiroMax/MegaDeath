QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(release, debug|release): LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release):   LIBS += -L$$PWD/SFML/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD/SFML/include/
DEPENDPATH +=  $$PWD/SFML/include/

SOURCES += \
    Game/game.cpp \
    Game/gamewidget.cpp \
    Interfaces/IUnit.cpp \
    MathLib/math_lib.cpp \
    Player/player.cpp \
    UnitMap/unit_map.cpp \
    WorldMap/tile/tile.cpp \
    WorldMap/tilemap.cpp \
    main.cpp


HEADERS += \
    Constants/constants.h \
    Game/game.h \
    Game/gamewidget.h \
    Interfaces/IUnit.h \
    MathLib/math_lib.h \
    Player/player.h \
    Structures/structs.h \
    UnitMap/unit_map.h \
    UnitMap/unit_map_constants.h \
    WorldMap/tile/tile.h \
    WorldMap/tile/tile_constants.h \
    WorldMap/tilemap.h \
    WorldMap/tilemap_constants.h

FORMS +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    media.qrc

