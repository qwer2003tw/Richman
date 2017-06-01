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
        displayRemoteDice = false;
        followMouse = 99;   // 沒有圖片跟隨滑鼠
        propName[0] = "地雷";
        propName[1] = "路障";
        propName[2] = "定時炸彈";
        propName[3] = "遙控骰子";
        for (int i = 0; i < 6; i++) remoteDice[i].SetValue(i);
    }
    void UI::LoadBitmap()
    {
        dice[0].SetXY(576, 475);                                  // 設定骰子1位置
        dice[1].SetXY(676, 475);                                  // 設定骰子2位置
        for (int i = 0; i < 3; i++) remoteDice[i].SetXY(588+180*i, 485);
        for (int i = 3; i < 6; i++) remoteDice[i].SetXY(588 + 180 * (i % 3), 665);
        number[0].SetXY(400, 460);                                // 設定數字初始位置
        number[1].SetXY(450, 460);
        yesButton->SetXY(480, 540);
        noButton->SetXY(680, 540);
		cardButton->SetXY(0, 0);
        rdbg.LoadBitmap("res/rdbg.bmp");
        dice[0].LoadBitmap();
        dice[1].LoadBitmap();
        for (int i = 0; i < 6; i++) remoteDice[i].LoadBitmap();
        btnbackground.LoadBitmap("res/btnbg.bmp");
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
        event[0].LoadBitmap("res/Nude1.bmp");
        event[1].LoadBitmap("res/Getmoney1.bmp");
        event[2].LoadBitmap("res/Zero1.bmp");
        event[3].LoadBitmap("res/Ufo1.bmp");
        playerHead[0].LoadBitmap("res/player/doreamon_Head.bmp", RGB(1, 0, 0));
        playerHead[1].LoadBitmap("res/player/Goda_Takeshi_Head.bmp", RGB(1, 0, 0));
        playerHead[2].LoadBitmap("res/player/Minamoto_Shizuka_Head.bmp", RGB(1, 0, 0));
        playerHead[3].LoadBitmap("res/player/Nobi_Nobita_Head.bmp", RGB(1, 0, 0));
        playerHead[4].LoadBitmap("res/player/Suneo_Head.bmp", RGB(1, 0, 0));
        rdbg.SetTopLeft(550, 450);


        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 36; j++)
            {
                if (i == 0) house[i][0][j].LoadBitmap("res/House_level0_0.bmp", RGB(0, 0, 0));
                else if (i == 1) house[i][0][j].LoadBitmap("res/House_level0_1.bmp", RGB(0, 0, 0));
                else if (i == 2) house[i][0][j].LoadBitmap("res/House_level0_2.bmp", RGB(0, 0, 0));
                else if (i == 3) house[i][0][j].LoadBitmap("res/House_level0_3.bmp", RGB(255, 255, 255)); //眼鏡白底的
                if (i == 0) house[i][1][j].LoadBitmap("res/House_level1_0.bmp", RGB(0, 0, 0));
                else if (i == 1) house[i][1][j].LoadBitmap("res/House_level1_1.bmp", RGB(0, 0, 0));
                else if (i == 2) house[i][1][j].LoadBitmap("res/House_level1_2.bmp", RGB(0, 0, 0));
                else if (i == 3) house[i][1][j].LoadBitmap("res/House_level1_3.bmp", RGB(0, 0, 0));
                if (i == 0) house[i][2][j].LoadBitmap("res/House_level2_0.bmp", RGB(0, 0, 0));
                else if (i == 1) house[i][2][j].LoadBitmap("res/House_level2_1.bmp", RGB(0, 0, 0));
                else if (i == 2) house[i][2][j].LoadBitmap("res/House_level2_2.bmp", RGB(0, 0, 0));
                else if (i == 3) house[i][2][j].LoadBitmap("res/House_level2_3.bmp", RGB(0, 0, 0));
                if (i == 0) house[i][3][j].LoadBitmap("res/House_level3_0.bmp", RGB(0, 0, 0));
                else if (i == 1) house[i][3][j].LoadBitmap("res/House_level3_1.bmp", RGB(0, 0, 0));
                else if (i == 2) house[i][3][j].LoadBitmap("res/House_level3_2.bmp", RGB(0, 0, 0));
                else if (i == 3) house[i][3][j].LoadBitmap("res/House_level3_3.bmp", RGB(0, 0, 0));
            }
        }
    }
    void UI::OnShow()
    {
        

        if (state != 5 && state != 8)     //非擲骰隱藏
        {
            dice[0].OnShow();
            dice[1].OnShow();
        }
            //
        if (state == 0) amount = 0;
        if ((amount / 10) == 0 && !dice[0].GetState() && state != 8) //骰子總和為個位數 貼個位數出來
        {
            number[1].OnShow((amount % 10)); //個位數
        }
        else if (amount > 0 && amount <= 12 && !dice[0].GetState() && state != 8) //骰子總合為十位數則貼出兩位數
        {
            number[0].OnShow((amount / 10)); //十位數
            number[1].OnShow((amount % 10)); //個位數
        }
            
        //
        btnbackground.SetTopLeft(0, 0);
        btnbackground.ShowBitmap();
        status_background.SetTopLeft(SIZE_X - 390, 0); //狀態欄背景位置
        status_background.ShowBitmap();       //顯示圖片
        ShowMiniMap();
        
        myGame->GetPlayer()[myGame->GetNowPlayer()]->OnShowState();
        if (displayMessage)
        {
            messageFrame.ShowBitmap();
            messageFrame.SetTopLeft(440, 260);
        }

        ShowPropFields();

        if (displayRemoteDice)
        {
            rdbg.ShowBitmap(1.8);
            for (int i = 0; i < 6; i++) remoteDice[i].OnShow(1.5);
        }
        yesButton->OnShow();
        noButton->OnShow();        
		cardButton->OnShow();
        OnShowMessage();
        if (showEvent != 99)
        {
            event[showEvent].SetTopLeft(400, 300);
            event[showEvent].ShowBitmap();
        }
        if (followMouse != 99)
        {
            props[followMouse].SetTopLeft(followX - props[followMouse].Width() / 2, followY - props[followMouse].Height() / 2);
            props[followMouse].ShowBitmap();
        }
    }
    void UI::OnMove()
    {  
        dice[0].OnMove();   
        dice[1].OnMove();
        TRACE("ui state = %d\n", state);
        //TRACE("amount=%d", amount);
        if (state == 1) amount = dice[0].GetValue() + dice[1].GetValue();
        if (dice[0].GetPlayerRun())
        {  
            state = 2;
        }
        dice[0].SetPlayerRun(0);
        yesButton->SetSignal(0);
        noButton->SetSignal(0);
		cardButton->SetSignal(0);
        TRACE("Picked Prop: %d", prop);
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

    void UI::SetAmount(int a)
    {
        amount = a;
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
        followX = point.x;
        followY = point.y;
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
        if (displayCardFrame) // 判斷點擊位置 (620-20)*1.5/5= (270-20)*1.5/3=    (440,360) 邊框10*1.5 = 15
        {
            if (point.x > 455 && point.x <  1355 && point.y > 375 && point.y < 750) // 440+(620-10)*1.5=1355  360+(270-10)*1.5=750
            {
                tempX = (point.x - 455) / 180; tempY = (point.y - 375) / 125;
                prop = tempX + tempY * 5;
                //->GetPlayer()[myGame->GetNowPlayer()]->GiveProp(myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(prop)->index, -1);
                UseProp(prop);
                //state = 8;
            }
        }
        if (state == 8 && GetNowUseProp() == 3)
        {
            followMouse = 99;
            UseRemoteDice(point);
        }
    }
    void UI::OnRClick(CPoint point)
    {
        if (state == 0 && displayCardFrame)
        {
            displayCardFrame = false;
        }
        if (state == 8)
        {
            displayRemoteDice = false;
            followMouse = 99;
            displayCardFrame = true;
            state = 0;
        }

    }
    int UI::GetPickedProp()
    {
        return prop;
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
        f.CreatePointFont(240, "Microsoft JhengHei");	// 產生 font f; 160表示16 point的字
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
        else if (messageType == 3)
        {
            sprintf(str, "請付過路費");
            sprintf(moneyStr, "$ %d", money);
        }
        else if (messageType == 4)
        {
            sprintf(str, "被地雷炸傷 ");
            sprintf(moneyStr, "無法行動 %d回合", money);
        }
        else if (messageType == 5)
        {
            sprintf(str, "原地療傷中 ");
            sprintf(moneyStr, "剩餘 %d回合", money);
        }
        else if (messageType == 6)
        {
            sprintf(str, "碰到路障");
        }
        if (displayMessage)
        {
            pDC->TextOut(490, 335, str);
            if(messageType != 6) pDC->TextOut(490, 410, moneyStr);
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
    void UI::initFollowMouse()
    {
        followMouse = 99;
    }
    void UI::RandomEvent()
    {
        showEvent = rand() % enevtIndex;
    }
    int UI::GetEvent()
    {
        return showEvent;
    }
    int UI::GetNowUseProp()
    {
        return myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(prop)->index;
    }
    int UI::GetFollowMouse()
    {
        return followMouse;
    }
    void UI::InitEvent()
    {
        showEvent = 99;
    }
    void UI::UseProp(int prop)
    {
        int propIndex = myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(prop)->index;
        if (propIndex == 3)         // 遙控骰子
        {
            state = 8;
            displayCardFrame = false;
            displayRemoteDice = true;
        }
        else if (propIndex == 0 || propIndex == 1 || propIndex == 2) 
        {
            state = 8;
            followMouse = propIndex;
        }
    }
    void UI::UseRemoteDice(CPoint point)
    {
        for (int i = 0; i < 3; i++)
        {
            if (point.x >(586 + 192 * i) && point.x < (586 + 110 * (i + 1) + 192 * i) && point.y > 483 && point.y < 595)
            {
                amount = i + 1;
                state = 2;
                displayRemoteDice = false;
                myGame->GetPlayer()[myGame->GetNowPlayer()]->GiveProp(GetNowUseProp(), -1);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (point.x >(586 + 192 * i) && point.x < (586 + 110 * (i + 1) + 192 * i) && point.y > 663 && point.y < 775)
            {

                amount = i + 4;
                state = 2;
                displayRemoteDice = false;
                myGame->GetPlayer()[myGame->GetNowPlayer()]->GiveProp(GetNowUseProp(), -1);
            }
        }
    }
    void UI::ShowPropFields()
    {
        if (displayCardFrame)
        {
            cardFrame.SetTopLeft(440, 360);
            cardFrame.ShowBitmap(1.5);
            ShowProp();
            ShowPropText();
        }
        
    }

    void UI::ShowPropText()
    {
        char amountStr[50] = "";
        CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
        CFont f, *fp;
        f.CreatePointFont(200, "Microsoft JhengHei");
        fp = pDC->SelectObject(&f);					// 選用 font f
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255, 255, 255));


        for (int i = 0; myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index != -1; i++)
        {
            if (i >= 0 && i < 5)
            {
                sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                pDC->TextOutA(520 + i * 180, 450, amountStr);
            }
            else if (i >= 5 && i < 10)
            {
                sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                pDC->TextOutA(520 + (i % 5) * 180, 540, amountStr);
            }
            else if (i >= 10 && i < 15)
            {
                sprintf(amountStr, "X %d", myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->amount);
                pDC->TextOutA(520 + (i % 5) * 180, 630, amountStr);

            }
        }

        pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
        CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
    }

    void UI::ShowProp()
    {
        for (int i = 0; myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index != -1; i++)
        {
            if (i >= 0 && i < 5)
            {
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(510 + i * 180, 380);
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
            }
            else if (i >= 5 && i < 10)
            {
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(510 + (i % 5) * 180, 470);
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
            }
            else if (i >= 10 && i < 15)
            {
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].SetTopLeft(510 + (i % 5) * 180, 560);
                props[myGame->GetPlayer()[myGame->GetNowPlayer()]->prop.at(i)->index].ShowBitmap();
            }
        }
    }

    void UI::ShowMiniMap()
    {
        
        const int left = SIZE_X - 390, top = SIZE_Y - 390, fix = 5, headFix = 13;
        const float headScale = 0.17f;
        const float scale = 0.2f;
    
        miniMap.SetTopLeft(left, top);
        miniMap.ShowBitmap();
        
        for (int i = 0; i < myGame->GetPlayerCount(); i++)
        {
            int nowPosition = myGame->GetPlayer()[i]->GetNow();
            int x = (myGame->GetBitMap().GetMapData()[nowPosition])->GetPositionX();
            int y = myGame->GetBitMap().GetMapData()[nowPosition]->GetPositionY();
            playerHead[myGame->GetPlayer()[i]->GetType()].SetTopLeft(left + x / 5 - headFix, top + y / 5- headFix);
            playerHead[myGame->GetPlayer()[i]->GetType()].ShowBitmap(headScale);
        }
        for (int i = 0; i < 36; i++)
        {
            if (myGame->GetBitMap().GetMapData()[i]->GetOwner() != 99 && myGame->GetBitMap().GetMapData()[i]->GetType() == 1)
            {
                TRACE("position=%d", myGame->GetBitMap().GetMapData()[i]->GetBuildingPositionX()/5);
                house[myGame->GetBitMap().GetMapData()[i]->GetOwner()][myGame->GetBitMap().GetMapData()[i]->GetHomeLevel()][i].SetTopLeft(fix + left + myGame->GetBitMap().GetMapData()[i]->GetBuildingPositionX() / 5, fix + top + myGame->GetBitMap().GetMapData()[i]->GetBuildingPositionY() / 5 );
                house[myGame->GetBitMap().GetMapData()[i]->GetOwner()][myGame->GetBitMap().GetMapData()[i]->GetHomeLevel()][i].ShowBitmap(scale);
            }
        }
    }

}
