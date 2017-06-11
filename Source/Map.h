#pragma once
#include "MapData.h"
namespace game_framework {
    class Map {
    public:
        Map();
        ~Map();
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
        int mapcount = 36;//地圖格數
        CMovingBitmap map;
        CMovingBitmap house[5][4];      // 5 users 4 levels
        CMovingBitmap props[15];            // 道具貼圖
        MapData *mapData[40];
    };
}
