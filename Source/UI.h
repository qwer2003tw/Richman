#pragma once
#include"Player.h"
#include "Button.h"

namespace game_framework {
    class UI {
    public:
        UI();
        void LoadBitmap();
        void OnShow();
        void OnMove();
        void SetXY(int playerX, int playerY, int speed);
        int GetSx();
        int GetSy();
        int GetPlayerRun();
        int GetAmount();
        void RollDice();
        int GetState();
        void SetState(int n);
        
    protected:
        CMovingBitmap status_background;    // 狀態欄
        CMovingBitmap miniMap;              // 小地圖
        int sx, sy;                         // 螢幕座標
        Dice dice[2];
        Number number[2];
        Button yesButton, noButton;
        int amount;
        int state=0;//0無事  1骰子轉動 2骰子轉動結束傳值 3人物移動中 4人物到達 
        
    };
}