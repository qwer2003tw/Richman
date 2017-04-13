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
        CGameStateRun *myGame;              // Ūmygme��T
        CMovingBitmap status_background;    // ���A��
        CMovingBitmap miniMap;              // �p�a��
        CMovingBitmap messageFrame;         // �T���ج[
        CMovingBitmap cardFrame;            // �D����
        int sx, sy;                         // �ù��y��
        Dice dice[2];
        Number number[2];
        Button *yesButton = new Button(), *noButton = new Button();
		Button *cardButton = new Button(1);
        int amount;
        int state = 0;                      // 0 �}�l > 1�Y�� > 2�백�ǭ� > 3�H�����ʤ� > �i�H�R�a��4�� �i�H�ɯŸ�5 ����6
        int messageType;                    // �T������ 1 �R�a 2 �ɯ�
        int money;                          // ���B�T��
        bool displayMessage;
        bool displayCardFrame;
        char *propName[15];
    };
}