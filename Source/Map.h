#pragma once
#include "MapData.h"
namespace game_framework {
    class Map {
    public:
        Map();
        void LoadBitmap();
        void OnShow(int sx, int sy);
        MapData** GetMapData();
        int GetMapCount();  
    private:
        int mapcount = 36;//�a�Ϯ��
        CMovingBitmap map;
        MapData *mapData[40];//??
    };
}
