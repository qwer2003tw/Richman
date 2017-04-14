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
        sx = 0;
        sy = -60;     //道具欄位下修
        displayMessage = false;
        displayCardFrame = false;
        propName[0] = "地雷";
        propName[1] = "路障";
        propName[2] = "定時炸彈";
        propName[3] = "遙控骰子";
    }
    void UI::LoadBitmap()
    {
        dice[0].SetXY(576, 475);                                  // 設定骰子1位置
        dice[1].SetXY(676, 475);                                  // 設定骰子2位置
        number[0].SetXY(400, 460);                                // 設定數字初始位置
        number[1].SetXY(450, 460);
        yesButton->SetXY(480, 540);
        noButton->SetXY(680, 540);
		cardButton->SetXY(0, 0);
        dice[0].LoadBitmap();
        dice[1].LoadBitmap();
        number[0].LoadBitmap();
        number[1].LoadBitmap();
        yesButton->LoadBitmap("res/YES.bmp", "res/YES_1.bmp", RGB(0, 0, 0));       // 滑過前圖片 滑過圖片
        noButton->LoadBitmap("res/NO.bmp", "res/NO_1.bmp", RGB(0, 0, 0));          // 滑過前圖片 滑過圖片
		cardButton->LoadBitmap("res/props.bmp", "res/props1.bmp", RGB(0, 0, 0));
		cardButton->SetEnable(true);
        miniMap.LoadBitmap("res/mini_map_1.bmp", RGB(255, 255, 255)); //讀取小地圖
        status_background.LoadBitmap("res/STATUS_BACKGROUND.bmp");  //讀狀態欄背景
        messageFrame.LoadBitmap("res/MESSAGE_FRAME.bmp", RGB(0, 0, 0));
        cardFrame.LoadBitmap("res/CARD_FRAME.bmp");
        props[0].LoadBitmap("res/Landmine.bmp", RGB(255, 255, 255));
        props[1].LoadBitmap("res/Roadblocks.bmp", RGB(255, 255, 255));
        props[2].LoadBitmap("res/Timebombs.bmp", RGB(255, 255, 255));
        props[3].LoadBitmap("res/Remotedice.bmp", RGB(255, 255, 255));
        
    }
    void UI::OnShow()
    {
        

        if (state != 5)     //非擲骰隱藏
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
            messageFrame.SetTopLeft(440, 260);
        }
        if (displayCardFrame)
        {
            showPropFields();
        }

        yesButton->OnShow();
        noButton->OnShow();        
		cardButton->OnShow();
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
        yesButton->SetSignal(0);
        noButton->SetSignal(0);
		cardButton->SetSignal(0);
    }
    void UI::SetXY(int playerX, int playerY, int speed)
    {
        if (playerX - sx > (SIZE_X - 390) / 2 && sx < 370) sx += speed;
        if (playerX - sx < (SIZE_X - 390) / 2 && sx > 0) sx -= speed;
        if (playerY - sy > SIZE_Y / 2 && sy < 800) sy += speed;
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
            yesButton->SetEnable(true);
            noButton->SetEnable(true);
        }
        else if(s == 0)
        {
            yesButton->SetEnable(false);
            noButton->SetEnable(false);
        }
    }
    void UI::OnMouseMove(UINT nFlags, CPoint point)
    {
        yesButton->OnMove(point);
        noButton->OnMove(point);
        cardButton->OnMove(point);
    }
    void UI::OnLClick(CPoint point)
    {
        yesButton->OnClick(point);
        noButton->OnClick(point);
        cardButton->OnClick(point);
        if (state == 0 && cardButton->GetSignal())
        {
            displayCardFrame = true;
        }
        if (displayCardFrame) // 判斷點擊位置 620/5=124 270/3=90
        {
            //if (point.x > 510 && point.x < 634 && point.y > 380 && point.y < 470)
                //testsingal = 1;
        }


    }
    void UI::OnRClick(CPoint point)
    {
        if (state == 0 && displayCardFrame)
        {
            displayCardFrame = false;
        }
    }
    int UI::GetYesOrNoBuy()
    {
        if (yesButton->GetSignal())
        {
            return 1;
        }
        else if (noButton->GetSignal())
        {
            return 0;
        }
        else return 99;
    }
   bool UI::GetCardDisplay()
    {
        return displayCardFrame;
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
        else if (messageType == 2)
        {
            sprintf(str, "是否要升級");
            sprintf(moneyStr, "$ %d", money);

        }
        if (displayMessage)
        {
            pDC->TextOut(490, 335, str);
            pDC->TextOut(490, 410, moneyStr);
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
	void UI::SetDiceValue(int d1, int d2)
	{
		dice[0].SetValue(d1);
		dice[1].SetValue(d2);
	}
    void UI::GetEvent()
    {
        int eventType = rand() % enevtIndex;
        switch (eventType)
        {
        case 0:

            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        default:
            break;
        }
    }
    void UI::showPropFields()
    {
        char amountStr[50] = "";
        cardFrame.SetTopLeft(440, 360);
        cardFrame.ShowBitmap(1.5);
        for (int i = 0; myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index != -1; i++)
        {
            if (i >= 0 && i < 5)
            {
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(510 + i * 180, 380);
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
                //sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                //pDC->TextOutA(520 + i * 170, 450, amountStr);
            }
            else if (i >= 5 && i < 10)
            {
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(510 + (i % 5) * 180, 470);
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
                //sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                //pDC->TextOutA(520 + (i % 5) * 170, 540, amountStr);
            }
            else if (i >= 10 && i < 15)
            {
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(510 + (i % 5) * 180, 560);
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
                //sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                //pDC->TextOutA(520 + (i % 5) * 170, 630, amountStr);

            }
        }

        CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
        CFont f, *fp;
        f.CreatePointFont(200, "Times New Roman");
        fp = pDC->SelectObject(&f);					// 選用 font f
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255, 255, 255));


        for (int i = 0; myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index != -1; i++)
        {
            if (i >= 0 && i < 5)
            {
                //props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(490 + i * 190, 380);
                //props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
                sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                pDC->TextOutA(520 + i * 180, 450, amountStr);
            }
            else if (i >= 5 && i < 10)
            {
                //props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(490 + (i % 5) * 190, 470);
                //props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
                sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                pDC->TextOutA(520 + (i % 5) * 180, 540, amountStr);
            }
            else if (i >= 10 && i < 15)
            {
                //props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(490 + (i % 5) * 190, 560);
                //props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
                sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                pDC->TextOutA(520 + (i % 5) * 180, 630, amountStr);

            }
        }

        pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
        CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
    }
}
