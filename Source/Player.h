#pragma once
namespace game_framework {
    class Player {
    public:
        Player();
        void LoadBitmap();										// 載入圖形
        void OnMove(int x, int y);								// 移動
        void OnShow();											// 將圖形貼到畫面 
    protected:
        CMovingBitmap bmp;			// 球的圖
        int x, y;					// 圓心的座標
        int dx, dy;					// 地圖的座標
        int index;					// 球的「角度」，0-17表示0-360度
    private:
        void SetXY();               // 設定人物中心的座標
    };
}
