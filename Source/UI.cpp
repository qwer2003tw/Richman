#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Dice.h"
#include "Number.h" 
#include "UI.h"

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
        yesButton.LoadBitmap("res/YES.bmp", "res/YES.bmp", RGB(0, 0, 0));       // �ƹL�e�Ϥ� �ƹL�Ϥ�
        noButton.LoadBitmap("res/NO.bmp", "res/NO.bmp", RGB(0, 0, 0));          // �ƹL�e�Ϥ� �ƹL�Ϥ�
        miniMap.LoadBitmap("res/mini_map_1.bmp", RGB(255, 255, 255)); //Ū���p�a��
        status_background.LoadBitmap("res/STATUS_BACKGROUND.bmp");  //Ū���A��I��
    }
    void UI::OnShow()
    {
        dice[0].OnShow();
        dice[1].OnShow();
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
        if (state == 4)
        {
            yesButton.SetEnable(1);
            noButton.SetEnable(1);
        }
        else
        {
            yesButton.SetEnable(0);
            noButton.SetEnable(0);
        }
    }
    void UI::OnMove()
    {  
        dice[0].OnMove();
        dice[1].OnMove();

        TRACE("ui=%d\n", state);
        TRACE("playerrun=%d\n", dice[0].GetPlayerRun());

        amount = dice[0].GetValue() + dice[1].GetValue();
        if (dice[0].GetPlayerRun())
            state = 2;
        dice[0].SetPlayerRun(0);


        if (state == 4)
        {
           
        }
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
}
