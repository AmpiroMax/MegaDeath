#include "worldmap.h"

#include <QFile>
#include <QString>

#include <iostream>
#include <string>

void WorldMap::initLand()
{
    QFile file(":/media/map_1.txt");

    if (!file.exists())
    {
        std::cout << "FIle does not exist" << std::endl;
        return;
    }

    file.open(QIODevice::ReadOnly);
    while (!file.atEnd())
    {
        QString strReader;
        strReader = file.readLine();

        std::string str = strReader.toStdString();

        landScape.resize(landScape.size() + 1);
        size_t ind = landScape.size() - 1;
        for (size_t i = 0; i < str.size(); ++i)
        {
            landScape[ind].push_back(str[i]);
        }
    }

    file.close();
}

WorldMap::WorldMap()
{
    initLand();
}
