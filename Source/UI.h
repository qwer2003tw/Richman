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
        CGameStateRun *myGame;              // Ūmygme��T
        CMovingBitmap status_background;    // ���A��
        CMovingBitmap miniMap;              // �p�a��
        CMovingBitmap messageFrame;         // �T���ج[
        CMovingBitmap cardFrame;            // �D����
        CMovingBitmap props[15];            // �D��
        CMovingBitmap event[10];            // �ƥ�
        CMovingBitmap house[5][4];          // 4 users 4 levels
        CMovingBitmap playerHead[5];
        CMovingBitmap btnbackground;        // �W��I��
        CMovingBitmap rdbg;                 // ������l�I��
        CMovingBitmap endbackground;        // ��������I��
        int sx, sy;                         // �ù��y��
        Dice dice[2];
        Dice remoteDice[6];
        Number number[2];
        Button *yesButton = new Button(), *noButton = new Button();
		Button *cardButton = new Button(1);
        int amount;
        int state = 0;                      // 0 �}�l > 1�Y�� > 2�백�ǭ� > 3�H�����ʤ� > �i�H�R�a��4�� 
                                            // 5�i�H�ɯŸ� 6���� 7�ƥ� 8�ϥιD�� 9�Ȱ����� 10����
        int messageType;                    // �T������ 1 �R�a 2 �ɯ�
        int money;                          // ���B�T��
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
        int tempX = 0, tempY = 0;           // ��D��y��
        int prop;                           // �ҿ�����y��
        int order[4];
    };
}