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
        CMovingBitmap status_background;    // ���A��
        CMovingBitmap miniMap;              // �p�a��
        int sx, sy;                         // �ù��y��
        Dice dice[2];
        Number number[2];
        Button yesButton, noButton;
        int amount;
        int state=0;//0�L��  1��l��� 2��l��ʵ����ǭ� 3�H�����ʤ� 4�H����F 
        
    };
}