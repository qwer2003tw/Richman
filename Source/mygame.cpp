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
    startButton->SetXY(420, SIZE_Y / 2);
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
    beginground.ShowBitmap();        
    startButton->OnShow();           
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
    /*
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(240,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(SIZE_X/4, SIZE_Y/2,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,825,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,865,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,905,"Press Alt-F4 or ESC to Quit.");
<<<<<<< HEAD

=======
    
>>>>>>> 29c0cca915a36ab6d8609b38b585a27e306407c1
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
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
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
        if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() == 99 && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetType() == 1)
        {
            ui.SetButton(1);
            ui.SetState(4); // player stopping & display buy button
        }

        else if (bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetOwner() == nowPlayer && bigMap.GetMapData()[player[nowPlayer]->GetNow()]->GetHomeLevel() < 3)
        {
            ui.SetButton(1);
            ui.SetState(5); // player stopping & display upgrade button
        }
        else ui.SetState(0);
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
    sx = sy = 0;
    nowPlayer = 0;
    playercount = 2;
    //�N�|�Ӫ��a�ХX��
    /*for (int i = 0; i < playercount; i++)
    {
        player[i] = new Player(0);//�᭱�޼Ʊ�TYPE
        player[i]->LoadBitmap();
        player[i]->SetMap(&bigMap);
    }*/
    player[0] = new Player(0);//�᭱�޼Ʊ�TYPE
    player[0]->LoadBitmap();
    player[0]->SetMap(&bigMap);
    player[1] = new Player(1);//�᭱�޼Ʊ�TYPE
    player[1]->LoadBitmap();
    player[1]->SetMap(&bigMap);
    //
	// ��������Loading�ʧ@�A�����i��
	//
	//ShowInitProgress(50);
	//Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				    // ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);						    	// ���J�����ϧ�
	corner.ShowBitmap(background);						    	// �Ncorner�K��background
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    if (canThrowDies)
    {
        ui.RollDice();
    }
    ui.OnClick(point);
    if (ui.GetState() == 4)
    {
        if (ui.GetYesOrNoBuy() == 1)
        {
            bigMap.Build(nowPlayer, player[nowPlayer]->GetNow());
            ui.SetButton(0);
            ui.SetState(0);

            if (nowPlayer < playercount - 1) nowPlayer++;
            else nowPlayer = 0;

        }
        else if (ui.GetYesOrNoBuy() == 0)
        {
            ui.SetButton(0);
            ui.SetState(0);

            if (nowPlayer < playercount - 1) nowPlayer++;
            else nowPlayer = 0;
        }

    }
    if (ui.GetState() == 5)
    {
        if (ui.GetYesOrNoBuy() == 1)
        {
            bigMap.Upgrade(player[nowPlayer]->GetNow());
            ui.SetButton(0);
            ui.SetState(0);
            if (nowPlayer < playercount - 1) nowPlayer++;
            else nowPlayer = 0;
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
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
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

    bigMap.OnShow(ui.GetSx(), ui.GetSy());              // �K�W�a��
    //�H�U��UI
    ui.OnShow();
    //�H�����
    for (int i = 0; i < playercount; i++)
    {
        if(!player[i]->GetBankruptcy())
            player[i]->OnShow(ui.GetSx(), ui.GetSy());
    }
}

}