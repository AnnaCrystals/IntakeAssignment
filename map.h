#pragma once
#include "template.h"
#include "surface.h"
#include "bottle.h"
#include <string>
#include <vector>

namespace Tmpl8 {
    class Surface;
    class Bottle;

    class Map
    {
    public:
        Map();
        void LoadMap(const char* nameFile, const int layer);

        int map[1][16][25] = {};
        int loadedLayers = 0;

        struct MapLayer {
            vec2 map[16][25];
        };

        struct MapData {
            std::vector<MapLayer> layers;
            MapLayer collisionLayer;
        };

        static void FolderRead();

    private:
        std::string TextFileRead(const char* nameFile);
    };
}
