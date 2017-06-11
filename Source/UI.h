#pragma once
#include"Player.h"
#include "Button.h"
#include "Map.h"

namespace game_framework {
    class UI {
    public:
        UI();
        ~UI();
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
        void SetAmount(int a);
        void SetState(int n);
        void SetButton(int s);
        void OnMouseMove(UINT nFlags, CPoint point);
        void OnLClick(CPoint point);
        void OnRClick(CPoint point);
        int GetPickedProp();
        int GetYesOrNoBuy();
        bool GetCardDisplay();
        bool GetIsEnd();
        void SetMyGame(CGameStateRun *mygame);
        void OnShowMessage();
        void SetMessage(int type, int Money);
        void SetDisplay(bool displayMessage);
		void SetDiceValue(int d1, int d2);
        void SetIsEnd(bool isEnd);
        void initFollowMouse();
        void RandomEvent();
        int GetEvent();
        int GetNowUseProp();
        int GetFollowMouse();
        Button** GetyesButton();
        void InitEvent();
        void UseProp(int prop);
        void UseRemoteDice(CPoint point);
        void ComputeOrder();
        
    protected:
        CGameStateRun *myGame;              // 讀mygme資訊
        CMovingBitmap status_background;    // 狀態欄
        CMovingBitmap miniMap;              // 小地圖
        CMovingBitmap messageFrame;         // 訊息框架
        CMovingBitmap cardFrame;            // 道具欄
        CMovingBitmap props[15];            // 道具
        CMovingBitmap event[10];            // 事件
        CMovingBitmap house[5][4];          // 4 users 4 levels
        CMovingBitmap playerHead[5];
        CMovingBitmap btnbackground;        // 上方背景
        CMovingBitmap rdbg;                 // 遙控骰子背景
        CMovingBitmap endbackground;        // 結束結算背景
        int sx, sy;                         // 螢幕座標
        Dice dice[2];
        Dice remoteDice[6];
        Number number[2];
        Button *yesButton = new Button(), *noButton = new Button();
		Button *cardButton = new Button(1);
        int amount;
        int state = 0;                      // 0 開始 > 1擲骰 > 2骰停傳值 > 3人物移動中 > 可以買地跳4做 
                                            // 5可以升級跳 6延遲 7事件 8使用道具 9暫停延遲 10結算
        int messageType;                    // 訊息類型 1 買地 2 升級
        int money;                          // 金額訊息
        bool displayMessage;
        bool displayCardFrame;
        bool displayRemoteDice;
        bool isEnd;
        int followMouse;
        int followX, followY;
        char *propName[15];
        void ShowPropFields();
        void ShowPropText();
        void ShowProp();
        void ShowMiniMap();
        void ShowEnd();
        int enevtIndex = 4;
        int showEvent = 99;
        int tempX = 0, tempY = 0;           // 抓道具座標
        int prop;                           // 所選取的座標
        int order[4];
    };
}