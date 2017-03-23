#pragma once
namespace game_framework {
    class Map {
    public:
        Map();
        void LoadBitmap();
        void OnShow(int sx, int sy);
    private:
        CMovingBitmap map;
    };
}
