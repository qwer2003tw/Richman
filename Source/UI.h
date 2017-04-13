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
        void OnLClick(CPoint point);
        void OnRClick(CPoint point);
        int GetYesOrNoBuy();
        bool GetCardDisplay();
        void SetMyGame(CGameStateRun *mygame);
        void OnShowMessage();
        void SetMessage(int type, int Money);
        void SetDisplay(bool displayMessage);
		void SetDiceValue(int d1, int d2);
    protected:
        CGameStateRun *myGame;              // 讀mygme資訊
        CMovingBitmap status_background;    // 狀態欄
        CMovingBitmap miniMap;              // 小地圖
        CMovingBitmap messageFrame;         // 訊息框架
        CMovingBitmap cardFrame;            // 道具欄
        int sx, sy;                         // 螢幕座標
        Dice dice[2];
        Number number[2];
        Button *yesButton = new Button(), *noButton = new Button();
		Button *cardButton = new Button(1);
        int amount;
        int state = 0;                      // 0 開始 > 1擲骰 > 2骰停傳值 > 3人物移動中 > 可以買地跳4做 可以升級跳5 延遲6
        int messageType;                    // 訊息類型 1 買地 2 升級
        int money;                          // 金額訊息
        bool displayMessage;
        bool displayCardFrame;
        char *propName[15];
    };
}