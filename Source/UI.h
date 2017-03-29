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
        CMovingBitmap status_background;    // ���A��
        CMovingBitmap miniMap;              // �p�a��
        int sx, sy;                         // �ù��y��
        Dice dice[2];
        Number number[2];
        Button yesButton, noButton;
        int amount;
        int state = 0;                      // 0 �}�l > 1�Y�� > 2�백�ǭ� > 3�H�����ʤ� > �i�H�R�a��4�� �i�H�ɯŸ�5 ����R�^0
        
    };
}