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
        void SetButton(int s);
        void OnMouseMove(UINT nFlags, CPoint point);
        void OnClick(CPoint point);
        int GetYesOrNoBuy();
    protected:
        CMovingBitmap status_background;    // 狀態欄
        CMovingBitmap miniMap;              // 小地圖
        int sx, sy;                         // 螢幕座標
        Dice dice[2];
        Number number[2];
        Button yesButton, noButton;
        int amount;
        int state = 0;                      // 0 開始 > 1擲骰 > 2骰停傳值 > 3人物移動中 > 可以買地跳4做 可以升級跳5 不能買回0
        
    };
}