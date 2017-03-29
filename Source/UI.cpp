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
        dice[0].SetXY(576, 415);                                  // 設定骰子1位置
        dice[1].SetXY(676, 415);                                  // 設定骰子2位置
        number[0].SetXY(400, 400);                                // 設定數字初始位置
        number[1].SetXY(450, 400);
        yesButton.SetXY(480, 480);
        noButton.SetXY(680, 480);
        dice[0].LoadBitmap();
        dice[1].LoadBitmap();
        number[0].LoadBitmap();
        number[1].LoadBitmap();
        yesButton.LoadBitmap("res/YES.bmp", "res/YES.bmp", RGB(0, 0, 0));       // 滑過前圖片 滑過圖片
        noButton.LoadBitmap("res/NO.bmp", "res/NO.bmp", RGB(0, 0, 0));          // 滑過前圖片 滑過圖片
        miniMap.LoadBitmap("res/mini_map_1.bmp", RGB(255, 255, 255)); //讀取小地圖
        status_background.LoadBitmap("res/STATUS_BACKGROUND.bmp");  //讀狀態欄背景
    }
    void UI::OnShow()
    {
        dice[0].OnShow();
        dice[1].OnShow();
        //
        if ((amount / 10) == 0 && !dice[0].GetState()) //骰子總和為個位數 貼個位數出來
        {
            number[1].OnShow((amount % 10)); //個位數
        }
        else if (amount > 0 && amount <= 12 && !dice[0].GetState()) //骰子總合為十位數則貼出兩位數
        {
            number[0].OnShow((amount / 10)); //十位數
            number[1].OnShow((amount % 10)); //個位數
        }
        //
        status_background.SetTopLeft(890, 0); //狀態欄背景位置
        status_background.ShowBitmap();       //顯示圖片
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
