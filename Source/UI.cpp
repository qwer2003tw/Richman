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
        displayMessage = false;
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
        yesButton.LoadBitmap("res/YES.bmp", "res/YES_1.bmp", RGB(0, 0, 0));       // 滑過前圖片 滑過圖片
        noButton.LoadBitmap("res/NO.bmp", "res/NO_1.bmp", RGB(0, 0, 0));          // 滑過前圖片 滑過圖片
        miniMap.LoadBitmap("res/mini_map_1.bmp", RGB(255, 255, 255)); //讀取小地圖
        status_background.LoadBitmap("res/STATUS_BACKGROUND.bmp");  //讀狀態欄背景
        messageFrame.LoadBitmap("res/MESSAGE_FRAME.bmp", RGB(0, 0, 0));
    }
    void UI::OnShow()
    {
        
        if (state != 3)     //非擲骰隱藏
        {
            dice[0].OnShow();
            dice[1].OnShow();
        }
            //
        if (state == 0) amount = 0;
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
        status_background.SetTopLeft(SIZE_X - 390, 0); //狀態欄背景位置
        status_background.ShowBitmap();       //顯示圖片
        miniMap.SetTopLeft(SIZE_X - 390, SIZE_Y - 390);
        miniMap.ShowBitmap();
        myGame->GetPlayer()[myGame->GetNowPlayer()]->OnShowState();
        if (displayMessage)
        {
            messageFrame.ShowBitmap();
            messageFrame.SetTopLeft(440, 230);
        }
        yesButton.OnShow();
        noButton.OnShow();
        OnShowMessage();
    }
    void UI::OnMove()
    {  
        dice[0].OnMove();   
        dice[1].OnMove();
        TRACE("ui state = %d\n", state);

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
        if (playerX - sx > (SIZE_X - 390) / 2 && sx < 390) sx += speed;
        if (playerX - sx < (SIZE_X - 390) / 2 && sx > 0) sx -= speed;
        if (playerY - sy > SIZE_Y / 2 && sy < 890) sy += speed;
        if (playerY - sy < SIZE_Y / 2 && sy > 0) sy -= speed;
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
    void UI::OnShowMessage()
    {
        CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
        CFont f, *fp;
        f.CreatePointFont(240, "Times New Roman");	// 產生 font f; 160表示16 point的字
        fp = pDC->SelectObject(&f);					// 選用 font f
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255, 255, 255));
        char str[80], moneyStr[50];								// Demo 數字對字串的轉換
        
        if (messageType == 1)
        {
            sprintf(str, "是否要購買土地");
            sprintf(moneyStr, "$ %d", money);
        }
        if (displayMessage)
        {
            pDC->TextOut(490, 325, str);
            pDC->TextOut(490, 400, moneyStr);
        }
        pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
        CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
    }
    void UI::SetMessage(int type, int Money)
    {
        money = Money;
        messageType = type;
    }
    void UI::SetDisplay(bool displayMessage)
    {
        this->displayMessage = displayMessage;
    }
}
