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

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
    beginground.LoadBitmap("res/BEGIN_BACKGROUND.bmp");
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
    startButton = new Button(1);
    startButton->LoadBitmap("res/BUTTON_START_1.bmp", "res/BUTTON_START_2.bmp", RGB(255, 255, 255));
    startButton->SetXY((SIZE_X - 484) / 2, SIZE_Y / 2);
    startButton->SetEnable(true);
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)   //���U�ƹ�����
{
    if (startButton != nullptr)
        startButton->OnClick(point);
    if(startButton->GetSignal())
	    GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)     //���U�u�_�ƹ�����
{
    if (startButton != nullptr)
        startButton->OnNoClick();
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)     //�ƹ��ƹL
{   
    if (startButton != nullptr)
        startButton->OnMove(point);
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	//logo.ShowBitmap();

    //
    // �K�Wbeginbackground�Mbutton
    //
    beginground.SetTopLeft(0, 0);    
    beginground.ShowBitmap(1.2);        
    startButton->OnShow();           
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
    /*
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(240,"Microsoft JhengHei");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(SIZE_X/4, SIZE_Y/2,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,825,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,865,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,905,"Press Alt-F4 or ESC to Quit.");

    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
    */
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
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
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
: CGameState(g), NUMBALLS(28)
{
	ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;

	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	//CAudio::Instance()->Play(AUDIO_LAKE, true);	    // ���� WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);	    // ���� MIDI

    CAudio::Instance()->Play(AUDIO_BGM, true);	    // ���� MIDI

}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	//
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);

    ui.OnMove();
    
    //ui ��l�ǭ�
    if (ui.GetState() == 2)
    {
        player[nowPlayer]->SetRemaining(ui.GetAmount());        // 2-3 �ǤJ��
        ui.SetState(3); // player runing
    }
    if (player[nowPlayer]->GetRemaining() == 0 && ui.GetState() == 3)   // �w�]��
    {
        // �i�H�\�Фl
        if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() == 99 && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetType() == 1)
        {
            ui.SetButton(1);
            ui.SetMessage(1, 800);
            ui.SetDisplay(1);
            ui.SetState(4); // player stopping & display buy button
        }
        // �i�H�ɯ�
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() == player[nowPlayer]->GetType() && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() < 3)
        {
            ui.SetButton(1);
            if(bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 0) ui.SetMessage(2, 1200);
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 1) ui.SetMessage(2, 2000);
            else ui.SetMessage(2, 2800);
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
                ui.SetMessage(3, 800);
                player[nowPlayer]->AdjMoney(-800);
                player[owner]->AdjMoney(800);
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 1)
            {
                ui.SetMessage(3, 1200);
                player[nowPlayer]->AdjMoney(-1200);
                player[owner]->AdjMoney(1200);
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 2)
            {
                ui.SetMessage(3, 2000);
                player[nowPlayer]->AdjMoney(-2000);
                player[owner]->AdjMoney(2000);
            }
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 3)
            {
                ui.SetMessage(3, 2800);
                player[nowPlayer]->AdjMoney(-2800);
                player[owner]->AdjMoney(2800);
            }
            ui.SetDisplay(1);
            ui.SetState(6);
        }
        // �ƥ��
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetType() == 2)
        {
            ui.RandomEvent();
            if (ui.GetEvent() == 0) player[nowPlayer]->AdjMoney(-3000);     // �Ǹo
            else if(ui.GetEvent() == 1) player[nowPlayer]->AdjMoney(3000);  // �_��
            else if (ui.GetEvent() == 2) player[nowPlayer]->AdjMoney(-500); // �S��
            else if (ui.GetEvent() == 3) player[nowPlayer]->AdjMoney(-500); // �ǯ�
            ui.SetState(7);
        }
        // ������
        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetPropIndex() == 1)
        {

        }
        else
        {
            ui.SetState(6);
        }
    }
    if (ui.GetState() == 6)                                 // ���𪬺A
    {
        if (delayCount > 0)
            delayCount--;
        else
        {
            delayCount = DELAY;
            ui.SetState(0);                                 // ���𵲧� ���^�}�l���A
            ui.SetDisplay(0);
            if (nowPlayer < playercount - 1) nowPlayer++;   // �������a
            else nowPlayer = 0;
        }
    }
    TRACE("OWNER:%d", bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner());
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
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//

	background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
    ui.LoadBitmap();                                        // ���JUI
    bigMap.LoadBitmap();                                    // ���J�a��
    nowPlayer = 0;
    playercount = 4;
    ui.SetMyGame(this);
    //�N�|�Ӫ��a�ХX��
    /*for (int i = 0; i < playercount; i++)
    {
        player[i] = new Player(0);//�᭱�޼Ʊ�TYPE
        player[i]->LoadBitmap();
        player[i]->SetMap(&bigMap);
    }*/
    player[0] = new Player(2, 0);//�᭱�޼Ʊ�TYPE ORDER
    player[0]->LoadBitmap();
    player[0]->SetMap(&bigMap);
    player[1] = new Player(3, 1);//�᭱�޼Ʊ�TYPE ORDER
    player[1]->LoadBitmap();
    player[1]->SetMap(&bigMap);
    player[2] = new Player(0, 2);//�᭱�޼Ʊ�TYPE ORDER
    player[2]->LoadBitmap();
    player[2]->SetMap(&bigMap);
    player[3] = new Player(1, 3);//�᭱�޼Ʊ�TYPE ORDER
    player[3]->LoadBitmap();
    player[3]->SetMap(&bigMap);

    //
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				    // ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);						    	// ���J�����ϧ�
	corner.ShowBitmap(background);						    	// �Ncorner�K��background
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid

    CAudio::Instance()->Load(AUDIO_BGM,  "sounds\\BGM.mp3");	// ���J�s��2���n��BGM.mp3
    //
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC    = 27;
    const char KEY_1TO9   = 49; // 1:49  9:57
    const char KEY_Z      = 90; // �ɯ�

    if(ui.GetState() == 0)
    {
        if (nChar - KEY_1TO9 + 1 <= 9 && nChar - KEY_1TO9 + 1 >= 1)
        {
            ui.SetAmount(nChar - KEY_1TO9 + 1);
            ui.SetState(2);
        }
    }
    if (nChar == KEY_Z && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() < 3) bigMap.Upgrade(player[nowPlayer]->GetNow());;
    if (nChar == KEY_ESC) PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
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
            player[nowPlayer]->AdjMoney(-800);
            bigMap.Build(player[nowPlayer]->GetType() , player[nowPlayer]->GetNow());
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
            if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 0) player[nowPlayer]->AdjMoney(-1200);
            else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() == 1) player[nowPlayer]->AdjMoney(-2000);
            else  player[nowPlayer]->AdjMoney(-2800);
            
            bigMap.Upgrade(player[nowPlayer]->GetNow());
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
    else if (ui.GetState() == 7)                // �������a
    {
        ui.InitEvent();
        ui.SetState(0);
        if (nowPlayer < playercount - 1) nowPlayer++;   
        else nowPlayer = 0;
    }
    else if (ui.GetState() == 8 && ui.GetFollowMouse() != 99) // ��ܹD���m��m
    {
        int px, py;
        for (int i = 0; i < 36; i++)
        {
            px = bigMap.GetMapData()[i]->GetPositionX() - 96;
            py = bigMap.GetMapData()[i]->GetPositionY() - 96;
            if (point.x >= px - ui.GetSx() && point.x <= px - ui.GetSx() + 192 && point.y >= py - ui.GetSy() && point.y <= py - ui.GetSy() + 192 && bigMap.GetMapData()[i]->GetPropIndex() == 99)
            {
                bigMap.SetPropIndex(ui.GetFollowMouse(), i); // ���o���H�Ϥ���index �ó]�m�bmap�W
                GetPlayer()[GetNowPlayer()]->GiveProp(ui.GetNowUseProp(), -1);
                ui.initFollowMouse();
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

Map CGameStateRun::GetBitMap()
{
    return bigMap;
}

Player **CGameStateRun::GetPlayer()
{
    return player;
}


int CGameStateRun::GetNowPlayer()
{
    return nowPlayer;
}

void CGameStateRun::OnShow()
{
    //
    //  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
    //        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
    //        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
    //
    //

    bigMap.OnShow(ui.GetSx(), ui.GetSy());
    // �H�����
    for (int i = 0; i < playercount; i++)
    {
        if (!player[i]->GetBankruptcy())
            player[i]->OnShow(ui.GetSx(), ui.GetSy());
    }
    // UI���
    ui.OnShow();
}
}