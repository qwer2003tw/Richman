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
        sy = -60;     //�D�����U��
        displayMessage = false;
    }
    void UI::LoadBitmap()
    {
        dice[0].SetXY(576, 475);                                  // �]�w��l1��m
        dice[1].SetXY(676, 475);                                  // �]�w��l2��m
        number[0].SetXY(400, 460);                                // �]�w�Ʀr��l��m
        number[1].SetXY(450, 460);
        yesButton.SetXY(480, 540);
        noButton.SetXY(680, 540);
		cardButton.SetXY(0, 0);
        dice[0].LoadBitmap();
        dice[1].LoadBitmap();
        number[0].LoadBitmap();
        number[1].LoadBitmap();
        yesButton.LoadBitmap("res/YES.bmp", "res/YES_1.bmp", RGB(0, 0, 0));       // �ƹL�e�Ϥ� �ƹL�Ϥ�
        noButton.LoadBitmap("res/NO.bmp", "res/NO_1.bmp", RGB(0, 0, 0));          // �ƹL�e�Ϥ� �ƹL�Ϥ�
		cardButton.LoadBitmap("res/CARD.bmp", "res/CARD.bmp", RGB(0, 0, 0));
		cardButton.SetEnable(true);
        miniMap.LoadBitmap("res/mini_map_1.bmp", RGB(255, 255, 255)); //Ū���p�a��
        status_background.LoadBitmap("res/STATUS_BACKGROUND.bmp");  //Ū���A��I��
        messageFrame.LoadBitmap("res/MESSAGE_FRAME.bmp", RGB(0, 0, 0));
    }
    void UI::OnShow()
    {
        
        //if (state != 3)     //�D�Y������
        //{
        if (state != 5)     //�D�Y������
        {
            dice[0].OnShow();
            dice[1].OnShow();
        }
            //
        if (state == 0) amount = 0;
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
        status_background.SetTopLeft(SIZE_X - 390, 0); //���A��I����m
        status_background.ShowBitmap();       //��ܹϤ�
        miniMap.SetTopLeft(SIZE_X - 390, SIZE_Y - 390);
        miniMap.ShowBitmap();
        myGame->GetPlayer()[myGame->GetNowPlayer()]->OnShowState();
        if (displayMessage)
        {
            messageFrame.ShowBitmap();
            messageFrame.SetTopLeft(440, 260);
        }
        yesButton.OnShow();
        noButton.OnShow();
		cardButton.OnShow();
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
		cardButton.SetSignal(0);
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
        CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
        CFont f, *fp;
        f.CreatePointFont(240, "Times New Roman");	// ���� font f; 160���16 point���r
        fp = pDC->SelectObject(&f);					// ��� font f
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255, 255, 255));
        char str[80], moneyStr[50];								// Demo �Ʀr��r�ꪺ�ഫ
        
        if (messageType == 1)
        {
            sprintf(str, "�O�_�n�ʶR�g�a");
            sprintf(moneyStr, "$ %d", money);
        }
        if (displayMessage)
        {
            pDC->TextOut(490, 335, str);
            pDC->TextOut(490, 410, moneyStr);
        }
        pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
        CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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
}
