#pragma once
#include "MapData.h"
namespace game_framework {
    class Map {
    public:
        Map();
        void LoadBitmap();
        void OnShow(int sx, int sy);
        void Build(int nowPlayer, int nowPosition);
        void Upgrade(int nowPosition);
        void SetPropIndex(int index, int position);
        int GetPropIndex(int position);
        CMovingBitmap* GetHouse();
        MapData** GetMapData();
        int GetMapCount();  
    private:
        int mapcount = 36;//�a�Ϯ��
        CMovingBitmap map;
        CMovingBitmap house[4][4][40];      // 4 users 4 levels 40 houses
        CMovingBitmap props[15];            // �D��K��
        MapData *mapData[40];
    };
}
