#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
    UI::UI()
    {
        sx = sy = 0;
    }
    void UI::LoadBitmap()
    {
        dice[0].SetXY(576, 415);                                  // �]�w��l1��m
        dice[1].SetXY(676, 415);                                  // �]�w��l2��m
        number[0].SetXY(400, 400);                                // �]�w�Ʀr��l��m
        number[1].SetXY(450, 400);
        yesButton.SetXY(480, 480);
        noButton.SetXY(680, 480);
        dice[0].LoadBitmap();
        dice[1].LoadBitmap();
        number[0].LoadBitmap();
        number[1].LoadBitmap();
        yesButton.LoadBitmap("res/YES.bmp", "res/YES_1.bmp", RGB(0, 0, 0));       // �ƹL�e�Ϥ� �ƹL�Ϥ�
        noButton.LoadBitmap("res/NO.bmp", "res/NO_1.bmp", RGB(0, 0, 0));          // �ƹL�e�Ϥ� �ƹL�Ϥ�
        miniMap.LoadBitmap("res/mini_map_1.bmp", RGB(255, 255, 255)); //Ū���p�a��
        status_background.LoadBitmap("res/STATUS_BACKGROUND.bmp");  //Ū���A��I��
    }
    void UI::OnShow()
    {
        
        if (state != 3)     //�D�Y������
        {
            dice[0].OnShow();
            dice[1].OnShow();
        }
            //
            if ((amount / 10) == 0 && !dice[0].GetState()) //��l�`�M���Ӧ�� �K�Ӧ�ƥX��
            {
                number[1].OnShow((amount % 10)); //�Ӧ��
            }
            else if (amount > 0 && amount <= 12 && !dice[0].GetState()) //��l�`�X���Q��ƫh�K�X����
            {
                number[0].OnShow((amount / 10)); //�Q���
                number[1].OnShow((amount % 10)); //�Ӧ��
            }
        //
        status_background.SetTopLeft(890, 0); //���A��I����m
        status_background.ShowBitmap();       //��ܹϤ�
        miniMap.SetTopLeft(890, 568);
        miniMap.ShowBitmap();
        yesButton.OnShow();
        noButton.OnShow();
        myGame->GetPlayer()[myGame->GetNowPlayer()]->OnShowState();
    }
    void UI::OnMove()
    {  
        dice[0].OnMove();   
        dice[1].OnMove();
        TRACE("ui state = %d\n", state);
        TRACE("playerrun=%d\n", dice[0].GetPlayerRun());

        amount = dice[0].GetValue() + dice[1].GetValue();
        if (dice[0].GetPlayerRun())
        {
            state = 2;
        }
        dice[0].SetPlayerRun(0);
        yesButton.SetSignal(0);
        noButton.SetSignal(0);
    }
    void UI::SetXY(int playerX, int playerY, int speed)
    {
        if (playerX - sx > 445 && sx < 1030) sx += speed;
        if (playerX - sx < 445 && sx > 0) sx -= speed;
        if (playerY - sy > 480 && sy < 960) sy += speed;
        if (playerY - sy < 480 && sy > 0) sy -= speed;
    }
    int UI::GetSx()
    {
        return sx;
    }
    int UI::GetSy()
    {
        return sy;
    }
    int UI::GetPlayerRun()
    {
        return dice[0].GetPlayerRun();
    }
    int UI::GetAmount()
    {
        return amount;
    }
    void UI::RollDice()
    {
        state = 1;
        dice[0].OnLButtonDown();
        dice[1].OnLButtonDown();
    }
    int UI::GetState()
    {
        return state;
    }

    void UI::SetState(int n)
    {
        state = n;
    }
    void UI::SetButton(int s)
    {
        if (s == 1)
        {
            yesButton.SetEnable(true);
            noButton.SetEnable(true);
        }
        else if(s == 0)
        {
            yesButton.SetEnable(false);
            noButton.SetEnable(false);
        }
    }
    void UI::OnMouseMove(UINT nFlags, CPoint point)
    {
        yesButton.OnMove(point);
        noButton.OnMove(point);
    }
    void UI::OnClick(CPoint point)
    {
        yesButton.OnClick(point);
        noButton.OnClick(point);
    }
    int UI::GetYesOrNoBuy()
    {
        if (yesButton.GetSignal())
        {
            return 1;
        }
        else if (noButton.GetSignal())
        {
            return 0;
        }
        else return 99;
    }
    void UI::SetMyGame(CGameStateRun *mygame)
    {
        myGame = mygame;
    }
}
