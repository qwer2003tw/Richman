#pragma once
#include "Map.h"
namespace game_framework {
    class Player {
    public:
        Player();
        void LoadBitmap();							// 載入圖形
       // void OnMove();			            // 移動
        void OnShow(int sx, int sy);				// 將圖形貼到畫面 
        int GetMapX();                              // 取得人物地圖座標 X
        int GetMapY();                              // 取得人物地圖座標 Y
        void SetPositionNum(int amount);            // 設定該次累加點數
        void SetState(int ns);                      // 設定狀態
        int GetState();
        void SetMap(Map* m);
        void Move(int n);
    protected:
        Map* map;
        CMovingBitmap bmp;			                // 人物圖片
        int dx, dy;					                // 人物地圖座標
    private:
        int prePositionNum;                         // 前一次位置點數
        int positionNum;                            // 位置點數
        int state;                                  // 0人物不動狀態 1人物移動狀態
    };
}
