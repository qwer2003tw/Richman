/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/
#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Map.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////


CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

CGameStateInit::~CGameStateInit()
{
    delete startButton;
    delete helpButton;
}

void CGameStateInit::OnInit()
{   
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
    beginground.LoadBitmap("res/BEGIN_BACKGROUND.bmp");

    startButton = new Button(1);
    startButton->LoadBitmap("res/BUTTON_START_1.bmp", "res/BUTTON_START_2.bmp", RGB(255, 255, 255));
    helpButton = new Button(1);
    helpButton->LoadBitmap("res/BUTTON_HELP_1.bmp", "res/BUTTON_HELP_2.bmp", RGB(255, 255, 255));
    selectcharactor.LoadBitmap("res/SelectCharactor.bmp",RGB(80,228,255));
    arrow.LoadBitmap("res/arrow.bmp",RGB(255,255,255));
    arrow1.LoadBitmap("res/arrow1.bmp", RGB(255, 255, 255));
    arrow2.LoadBitmap("res/arrow2.bmp", RGB(255, 255, 255));
    helpInfo.LoadBitmap("res/helpinfo.bmp",RGB(0, 0, 0));
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
    const char KEY_RIGHT = 0x27;
    const char KEY_LEFT = 0x25;
    const char KEY_ENTER = 0x0D;
	/*if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);	*/					// ������GAME_STATE_RUN
	if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��

    else if (nChar == KEY_RIGHT)
    {
        if (ancor <= 3)
        {
            if (++arrow_index[ancor] >= 5)arrow_index[ancor] = 0;
            dump = false;
            for (int i = 0; i < ancor; i++) if (arrow_index[ancor] == arrow_index[i]) dump = true;
        }   
    }
    else if (nChar == KEY_LEFT)
    {
        if (ancor <= 3)
        {
            if (--arrow_index[ancor] < 0)arrow_index[ancor] = 4;
            dump = false;
            for (int i = 0; i < ancor; i++) if (arrow_index[ancor] == arrow_index[i]) dump = true;
        }
        
    }
    else if (nChar == KEY_ENTER)
    {
        dump = false;
        for (int i = 0; i < ancor; i++) if (arrow_index[ancor] == arrow_index[i]) dump = true; 
        if (!dump && ancor <= 3)
        {
            ancor++;
            if (ancor == 4)
            {
                SelectCharactor::getInstance()->setData(arrow_index);
                GotoGameState(GAME_STATE_RUN);
            }
            if (arrow_index[ancor] == arrow_index[ancor - 1]) dump = true;
        }
    }
}
void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)   //���U�ƹ�����
{
    showHelp = false;
}
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)   //���U�ƹ�����
{
    if (startButton != nullptr)
        startButton->OnClick(point);
    if (startButton->GetSignal())
    {
        SelectCharactor::getInstance()->setData(arrow_index);
        GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
    }
    if (helpButton != nullptr)
        helpButton->OnClick(point);
    if (helpButton->GetSignal())
    {
        showHelp = true;
        helpButton->SetSignal(0);
    }

}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)     //���U�u�_�ƹ�����
{
    if (startButton != nullptr)
        startButton->OnNoClick();
    if (helpButton != nullptr)
        helpButton->OnNoClick();

}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)     //�ƹ��ƹL
{   
    if (startButton != nullptr)
        startButton->OnMove(point);
    if (helpButton != nullptr)
        helpButton->OnMove(point);
}

void CGameStateInit::OnShow()
{
    //
    // �K�Wbeginbackground�Mbutton
    //
    beginground.SetTopLeft(0, 0);    
    beginground.ShowBitmap(1.2);      
    startButton->SetXY((SIZE_X - 484) / 2+25, SIZE_Y / 2+225);
    startButton->SetEnable(true);
    startButton->OnShow();        
    helpButton->SetXY((SIZE_X - 484) / 2 + 25, SIZE_Y / 2 + 375);
    helpButton->SetEnable(true);
    helpButton->OnShow();

    selectcharactor.SetTopLeft(360,  180);
    selectcharactor.ShowBitmap();
    //
    int bx = 601 - arrow.Width() / 2;
    int by = 445 - arrow.Height() + 15;
    if (++acount == 12)acount = 0;

   for (int i = 0; i < 4; i++)
    {
       if (ancor == i)
       {
           if (dump == true)
           {
               arrow2.SetTopLeft(bx + arrow_index[i] * 180, by + i * 70);
               arrow2.ShowBitmap();
           }
           else if (acount >= 6)
           {
               arrow1.SetTopLeft(bx + arrow_index[i] * 180, by + i * 70);
               arrow1.ShowBitmap();
           }
           else
           {
               arrow.SetTopLeft(bx + arrow_index[i] * 180, by + i * 70);
               arrow.ShowBitmap();
           }
       }
       else
       {
           arrow.SetTopLeft(bx + arrow_index[i] * 180, by + i * 70);
           arrow.ShowBitmap();
       }
    }
   if (showHelp)
   {
       helpInfo.SetTopLeft((SIZE_X - 484) / 2 -30, SIZE_Y / 2 - 380);
       helpInfo.ShowBitmap(1.5);
   }
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
    PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	ShowInitProgress(66);
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Microsoft JhengHei");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)
{
    for (int i = 0; i < 4; i++) player[i] = nullptr;
}

CGameStateRun::~CGameStateRun()
{
    for (int i = 0; i < 4; i++) if (player[i] != nullptr) delete player[i];
}

void CGameStateRun::OnBeginState()
{
    player[0] = new Player(SelectCharactor::getInstance()->getCharactor()[0], 0);//�᭱�޼Ʊ�TYPE ORDER
    player[0]->LoadBitmap();
    player[0]->SetMap(&bigMap);
    player[1] = new Player(SelectCharactor::getInstance()->getCharactor()[1], 1);//�᭱�޼Ʊ�TYPE ORDER
    player[1]->LoadBitmap();
    player[1]->SetMap(&bigMap);
    player[2] = new Player(SelectCharactor::getInstance()->getCharactor()[2], 2);//�᭱�޼Ʊ�TYPE ORDER
    player[2]->LoadBitmap();
    player[2]->SetMap(&bigMap);
    player[3] = new Player(SelectCharactor::getInstance()->getCharactor()[3], 3);//�᭱�޼Ʊ�TYPE ORDER
    player[3]->LoadBitmap();
    player[3]->SetMap(&bigMap);

	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;

	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��

}

void CGameStateRun::OnMove()							// ���ʹC������
{
    if (ui.GetState() == 10 && ui.GetYesOrNoBuy() == 1)
        GotoGameState(GAME_STATE_OVER);
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);

    ui.OnMove();
    
    //ui ��l�ǭ�
    if (ui.GetState() == 2)
    {
        player[nowPlayer]->SetRemaining(ui.GetAmount());        // 2-3 �ǤJ��
        ui.SetState(3); // player runing
        if(player[nowPlayer]->GetTimeBombsCounter() > 0)
            CAudio::Instance()->Play(AUDIO_TICKING, true);
        else 
            CAudio::Instance()->Stop(7);
        CAudio::Instance()->Play(AUDIO_WALK, true);
    }
    // ���b��i�� �]�t��F
    if (ui.GetState() == 3){
        // ����
        if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPropIndex() == 1)
        {
            CAudio::Instance()->Play(AUDIO_STOP, true);
            CAudio::Instance()->Play(AUDIO_STOP, false);
            CAudio::Instance()->Stop(7);
            CAudio::Instance()->Stop(6);
            player[nowPlayer]->SetRemaining(0);
            bigMap.GetMapData()[player[nowPlayer]->GetNow()]->SetPropIndex(99);
            ui.SetMessage(6, 0); // �T������ ����
            ui.SetDisplay(1);
            ui.SetState(9);
        }
    }
    // ���b��i��
    if (player[nowPlayer]->GetRemaining() != 0 && ui.GetState() == 3)
    {
        if (player[nowPlayer]->GetBombs())
        {
            for (int i = 0; i < playercount; i++)
            {
                if (i != nowPlayer)
                {
                    if (player[nowPlayer]->GetNow() == player[i]->GetNow())
                    {
                        player[i]->SetHaveBombs(true);
                        player[i]->SetTimeBombsCounter(player[nowPlayer]->GetTimeBombsCounter()); // �B�Ƴ]�w                           
                        player[nowPlayer]->SetHaveBombs(false);
                        player[nowPlayer]->SetTimeBombsCounter(0);
                        break;
                    }
                }
            }
        }
    }
    // �w��F
    if (player[nowPlayer]->GetRemaining() == 0 && ui.GetState() == 3)
    {
        CAudio::Instance()->Stop(7);
        CAudio::Instance()->Stop(6);
        // �I��a�p
        if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPropIndex() == 0)
        {
            CAudio::Instance()->Play(AUDIO_BOOMER, true);
            CAudio::Instance()->Play(AUDIO_BOOMER, false);
            bigMap.SetPropIndex(99, player[nowPlayer]->GetNow()); // ���o���H�Ϥ���index �í��m
            player[nowPlayer]->SetStop(2);    // �Ѿl�Ȱ��^�X
            ui.SetMessage(4, 3);              // �T������ �Ȱ��^�X
            ui.SetDisplay(1);
            ui.SetState(6);
            isExplosion = true;
            player[nowPlayer]->SetInjury(true);
            player[nowPlayer]->SetHaveBombs(false); // ��֦����u �I��a�p �z����� �w�ɬ��u���A���m
            explosionCount = 0;
        }
        // �S�]�Ȱ��^�X ��ܩw�ɬ��u�Ҷ�
        else if (player[nowPlayer]->GetInjury() && player[nowPlayer]->GetStop() == 0)
        {
            CAudio::Instance()->Play(AUDIO_BOOMER, true);
            CAudio::Instance()->Play(AUDIO_BOOMER, false);
            player[nowPlayer]->SetStop(2);    // �Ѿl�Ȱ��^�X
            ui.SetState(6);
            isExplosion = true;
            player[nowPlayer]->SetInjury(true);
            player[nowPlayer]->SetHaveBombs(false); // ��֦����u �I��a�p �z����� �w�ɬ��u���A���s
            explosionCount = 0;
        }
        // �I��w�ɬ��u
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPropIndex() == 2)
        {
            bigMap.SetPropIndex(99, player[nowPlayer]->GetNow()); // ���o���H�Ϥ���index �ó]�m�bmap�W
            player[nowPlayer]->SetHaveBombs(true);
            player[nowPlayer]->SetTimeBombsCounter(15); // �B�Ƴ]�w
            ui.SetMessage(7, 15);                       // �T������ �P�W�B�Ƴ]�w
            ui.SetDisplay(1);
            ui.SetState(9);
        }
        // �i�H�\�Фl
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() == 99 && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetType() == 1)
        {
            ui.SetButton(1);
            ui.SetMessage(1, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice());
            ui.SetDisplay(1);
            ui.SetState(4); // player stopping & display buy button
        }
        // �i�H�ɯ�
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() == player[nowPlayer]->GetType() && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() < 3)
        {
            ui.SetButton(1);
            if(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 0) ui.SetMessage(2, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice()+200);
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 1) ui.SetMessage(2, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice()+400);
            else ui.SetMessage(2, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice()+600);
            ui.SetDisplay(1);
            ui.SetState(5); // player stopping & display upgrade button
        }
        // ���O�H���a
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() != player[nowPlayer]->GetType() && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() != 99)
        {
            int owner = 0;
            for (int i = 0; i < playercount; i++)
            {
                if (player[i]->GetType() == bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner())
                    owner = i;
            }
            if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 0)
            {
                ui.SetMessage(3, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice());
                player[nowPlayer]->AdjMoney(-bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice());
                player[owner]->AdjMoney(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice());
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 1)
            {
                ui.SetMessage(3, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice()+200);
                player[nowPlayer]->AdjMoney(-(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice()+200));
                player[owner]->AdjMoney(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice()+200);
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 2)
            {
                ui.SetMessage(3, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 400);
                player[nowPlayer]->AdjMoney(-(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 400));
                player[owner]->AdjMoney(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 400);
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 3)
            {
                ui.SetMessage(3, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 600);
                player[nowPlayer]->AdjMoney(-(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 600));
                player[owner]->AdjMoney(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 600);
            }
            ui.SetDisplay(1);
            ui.SetState(6);
        }
        // �ƥ��
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetType() == 2)
        {
            ui.RandomEvent();
            if (ui.GetEvent() == 0) player[nowPlayer]->AdjMoney(-3000);         // �Ǹo
            else if(ui.GetEvent() == 1) player[nowPlayer]->AdjMoney(3000);      // �_��
            else if (ui.GetEvent() == 2) player[nowPlayer]->AdjMoney(-500);     // �S��
            else if (ui.GetEvent() == 3) player[nowPlayer]->AdjMoney(-500);     // �ǯ�
            ui.SetState(7);
        }
        else
        {
            ui.SetState(6);
        }
    }
    if (ui.GetState() == 6)                                 // ���𪬺A �������a
    {
        if(player[nowPlayer]->GetMoney() < 0)
            ui.SetState(10);
        else if (delayCount > 0)
            delayCount--;
        else
        {
            delayCount = DELAY;
            ui.SetState(0);                                 // ���𵲧� ���^�}�l���A
            ui.SetDisplay(0);
            
            if (nowPlayer < playercount) // �������a
            {
                nowPlayer++;
                nowPlayer %= playercount;
                if (player[nowPlayer]->GetStop() != 0)
                {
                    int s = player[nowPlayer]->GetStop();
                    ui.SetMessage(5, player[nowPlayer]->GetStop());    // �T������ �Ȱ��^�X
                    player[nowPlayer]->SetStop(s - 1);
                    ui.SetDisplay(1);
                    ui.SetState(6);
                }
                else if (player[nowPlayer]->GetStop() == 0)player[nowPlayer]->SetInjury(false);
            }
        }
    }
    if (ui.GetState() == 9)                                 // ���𪬺A �~��Ӯ�R�� �ɯ� �ƥ� �������A
    {
        if (delayCount > 0)
            delayCount--;
        else
        {
            delayCount = DELAY;
            ui.SetState(3);                                 // ���𵲧� ���^�P�_���A
            ui.SetDisplay(0);
        }
    }
    for (int i = 0; i < playercount; i++)
    {
        player[i]->OnMove();
    }
    //�ץ��ù��y��
    ui.SetXY(player[nowPlayer]->GetMapX(), player[nowPlayer]->GetMapY(), player[nowPlayer]->GetSpeed());    
    
    if (player[nowPlayer]->GetRemaining() == 0 && ui.GetState() == 0)
        canThrowDies = true;
    else canThrowDies = false;
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    srand((int)time(NULL));
    ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%

    background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
    ui.LoadBitmap();                                        // ���JUI
    bigMap.LoadBitmap();                                    // ���J�a��
    nowPlayer = 0;
    playercount = 4;
    ui.SetMyGame(this);
    isExplosion = false;

    help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				    // ���J�������ϧ�
    explosion[0].LoadBitmap("RES/explosion/explosion_1.bmp", RGB(0, 0, 0));
    explosion[1].LoadBitmap("RES/explosion/explosion_2.bmp", RGB(0, 0, 0));
    explosion[2].LoadBitmap("RES/explosion/explosion_3.bmp", RGB(0, 0, 0));
    explosion[3].LoadBitmap("RES/explosion/explosion_4.bmp", RGB(0, 0, 0));
    explosion[4].LoadBitmap("RES/explosion/explosion_5.bmp", RGB(0, 0, 0));
    explosion[5].LoadBitmap("RES/explosion/explosion_6.bmp", RGB(0, 0, 0));
    explosion[6].LoadBitmap("RES/explosion/explosion_7.bmp", RGB(0, 0, 0));
    explosion[7].LoadBitmap("RES/explosion/explosion_8.bmp", RGB(0, 0, 0));

    CAudio::Instance()->Load(AUDIO_BGM, "sounds\\BGM.mp3");	        // ���J�s��3���n��BGM.mp3
    CAudio::Instance()->Load(AUDIO_BOOMER, "sounds\\BOOMER.mp3");   // ���J�s��4���n��BOOMER.mp3 
    CAudio::Instance()->Load(AUDIO_STOP, "sounds\\STOP.wav");       // ���J�s��5���n��STOP.mp3
    CAudio::Instance()->Load(AUDIO_WALK, "sounds\\WALK.mp3");       // ���J�s��6���n��WALK.mp3
    CAudio::Instance()->Load(AUDIO_TICKING, "sounds\\TICKING.mp3"); // ���J�s��7���n��TICKING.mp3
    CAudio::Instance()->Play(AUDIO_BGM, true);
}
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC    = 27;
    const char KEY_1TO9_1 = 49; // 1:49
    const char KEY_1TO9   = 97; // 1:97
    const char KEY_Z      = 90; // �ɯ�
    const char KEY_SPACE  = 32; // 
    const unsigned int KEY_ADD    = 187;
    const unsigned int KEY_SUB    = 189;
    const char KEY_ADD1 = 107;
    const char KEY_SUB1 = 109;


    if(ui.GetState() == 0 && !ui.GetCardDisplay())
    {
        if (nChar - KEY_1TO9 + 1 <= 9 && nChar - KEY_1TO9 + 1 >= 1)
        {
            ui.SetAmount(nChar - KEY_1TO9 + 1);
            ui.SetState(2);
        }
        if (nChar - KEY_1TO9_1 + 1 <= 9 && nChar - KEY_1TO9_1 + 1 >= 1)
        {
            ui.SetAmount(nChar - KEY_1TO9_1 + 1);
            ui.SetState(2);
        }
    }
    if (nChar == KEY_Z && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() < 3) bigMap.Upgrade(player[nowPlayer]->GetNow());;
    if (nChar == KEY_ESC) PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
    if (nChar == KEY_SPACE)
    {
        CPoint point;
        point.x = 520; point.y = 600;
        OnLButtonDown(nFlags,point);    // space ���N mouse
    }
    if(nChar==KEY_ADD || nChar == KEY_ADD1)
    {
        player[nowPlayer]->AdjMoney(2000);
    }
    if ((nChar == KEY_SUB || nChar == KEY_SUB1) && player[nowPlayer]->GetMoney() >= 2000)
    {
        player[nowPlayer]->AdjMoney(-2000);
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    if (canThrowDies && (point.y > 60) && !ui.GetCardDisplay())
    {
        ui.RollDice();
    }
    ui.OnLClick(point);
    if (ui.GetState() == 4)
    {
        if (ui.GetYesOrNoBuy() == 1)
        {
            if (player[nowPlayer]->GetMoney() < bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice())
                ui.SetMessage(8, 0);
            else
            {
                player[nowPlayer]->AdjMoney(-bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice());
                bigMap.Build(player[nowPlayer]->GetType(), player[nowPlayer]->GetNow());
            }
            ui.SetButton(0);
            ui.SetState(6);
            ui.SetDisplay(0);
        }
        else if (ui.GetYesOrNoBuy() == 0)
        {
            ui.SetButton(0);
            ui.SetState(6);
            ui.SetDisplay(0);
        }
    }
    else if (ui.GetState() == 5)
    {
        if (ui.GetYesOrNoBuy() == 1)
        {
            //�ɯŶO��
            if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 0)
            {
                if(player[nowPlayer]->GetMoney()<(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 200))
                    ui.SetMessage(9, 0);
                else
                    player[nowPlayer]->AdjMoney(-(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 200));
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 1)
            {
                if (player[nowPlayer]->GetMoney()<(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 400))
                    ui.SetMessage(9, 0);
                else
                    player[nowPlayer]->AdjMoney(-(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 400));
            }
            else
            {
                if (player[nowPlayer]->GetMoney()<(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 600))
                    ui.SetMessage(9, 0);
                else
                    player[nowPlayer]->AdjMoney(-(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPrice() + 600));
            }
            
            bigMap.Upgrade(player[nowPlayer]->GetNow());
            ui.SetButton(0);
            ui.SetState(6);
            ui.SetDisplay(1);
        }
        else if (ui.GetYesOrNoBuy() == 0)
        {
            ui.SetButton(0);
            ui.SetState(6);
            ui.SetDisplay(0);
        }
    }
    else if (ui.GetState() == 7)                // �ƥ� �������a
    {
        if (player[nowPlayer]->GetMoney() < 0)
        {
            (*ui.GetyesButton())->SetSignal(0);
            ui.SetState(10);
        }
        else
        {
            ui.InitEvent();
            ui.SetState(0);
            if (nowPlayer < playercount) // �������a
            {
                nowPlayer++;
                nowPlayer %= playercount;
                if (player[nowPlayer]->GetStop() != 0)
                {
                    int s = player[nowPlayer]->GetStop();
                    ui.SetMessage(5, player[nowPlayer]->GetStop());    // �T������ �Ȱ��^�X
                    player[nowPlayer]->SetStop(s - 1);
                    ui.SetDisplay(1);
                    ui.SetState(6);
                }
                else if (player[nowPlayer]->GetStop() == 0)player[nowPlayer]->SetInjury(false);
            }
        }
       
    }
    else if (ui.GetState() == 8 && ui.GetFollowMouse() != 99) // ��ܹD���m��m
    {
        int px, py;
        for (int i = 0; i < 36; i++)
        {
            px = bigMap.GetMapData()[i]->GetPositionX() - 96;
            py = bigMap.GetMapData()[i]->GetPositionY() - 96;
            if (point.x >= px - ui.GetSx() && point.x <= px - ui.GetSx() + 192 && point.y >= py - ui.GetSy() && point.y <= py - ui.GetSy() + 192 && bigMap.GetMapData()[i]->GetPropIndex() == 99 && point.x < SIZE_X - 390)
            {
                bigMap.SetPropIndex(ui.GetFollowMouse(), i); // ���o���H�Ϥ���index �ó]�m�bmap�W
                GetPlayer()[GetNowPlayer()]->GiveProp(ui.GetNowUseProp(), -1);
                ui.initFollowMouse();
                ui.SetState(0);
            }
        }
    }
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
    ui.OnMouseMove(nFlags, point);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    ui.OnRClick(point);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

Map *CGameStateRun::GetBitMap()
{
    return &bigMap;
}

Player **CGameStateRun::GetPlayer()
{
    return player;
}


int CGameStateRun::GetNowPlayer()
{
    return nowPlayer;
}

int CGameStateRun::GetPlayerCount()
{
    return playercount;
}

void CGameStateRun::OnShow()
{

    bigMap.OnShow(ui.GetSx(), ui.GetSy());
    // �H�����
    for (int i = playercount - 1; i >= 0; i--)
    {
        if (!player[i]->GetBankruptcy())
            player[i]->OnShow(ui.GetSx(), ui.GetSy());
    }
    if (isExplosion == true)
    {
        explosion[explosionCount].SetTopLeft(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPositionX()-ui.GetSx() - 100, bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPositionY() - ui.GetSy() - 100);
        explosion[explosionCount].ShowBitmap();
        explosionCount++;
        if (explosionCount == 8)
        {
            isExplosion = false;
        }
    }
    // UI���
    ui.OnShow();
}
}