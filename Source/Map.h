#pragma once
#include "MapData.h"
namespace game_framework {
    class Map {
    public:
        Map();
        void LoadBitmap();
        void OnShow(int sx, int sy);
        MapData** GetMapData();
    
    private:
        CMovingBitmap map;
        MapData* mapData[40];//??
    };
}
