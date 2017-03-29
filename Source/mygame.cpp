/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
    beginground.LoadBitmap("res/BEGIN_BACKGROUND.bmp");
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
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
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)   //按下滑鼠左鍵
{
    if (startButton != nullptr)
        startButton->OnClick(point);
    if(startButton->GetSignal())
	    GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)     //按下彈起滑鼠左鍵
{
    if (startButton != nullptr)
        startButton->OnNoClick();
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)     //滑鼠滑過
{   
    if (startButton != nullptr)
        startButton->OnMove(point);
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	//logo.ShowBitmap();

    //
    // 貼上beginbackground和button
    //
    beginground.SetTopLeft(0, 0);    
    beginground.ShowBitmap();        
    startButton->OnShow();           
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
    /*
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(240,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
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
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
    */
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
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
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	//CAudio::Instance()->Play(AUDIO_LAKE, true);	    // 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);	    // 撥放 MIDI

}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);


    ui.OnMove();
    
    //ui 骰子傳值
    if (ui.GetState() == 2)
    {
        player[nowPlayer]->SetRemaining(ui.GetAmount());        // 2-3 傳入值
        ui.SetState(3); // player runing
    }
    if (player[nowPlayer]->GetRemaining() == 0 && ui.GetState() == 3)   // 已跑完
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
    //修正螢幕座標
    ui.SetXY(player[nowPlayer]->GetMapX(), player[nowPlayer]->GetMapY(), player[nowPlayer]->GetSpeed());    
    
    if (player[nowPlayer]->GetRemaining() == 0 && ui.GetState() == 0)
        canThrowDies = true;
    else canThrowDies = false;

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    srand((int)time(NULL));
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//

	background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
    ui.LoadBitmap();                                        // 載入UI
    bigMap.LoadBitmap();                                    // 載入地圖
    sx = sy = 0;
    nowPlayer = 0;
    playercount = 2;
    //將四個玩家創出來
    /*for (int i = 0; i < playercount; i++)
    {
        player[i] = new Player(0);//後面引數掛TYPE
        player[i]->LoadBitmap();
        player[i]->SetMap(&bigMap);
    }*/
    player[0] = new Player(0);//後面引數掛TYPE
    player[0]->LoadBitmap();
    player[0]->SetMap(&bigMap);
    player[1] = new Player(1);//後面引數掛TYPE
    player[1]->LoadBitmap();
    player[1]->SetMap(&bigMap);
    //
	// 完成部分Loading動作，提高進度
	//
	//ShowInitProgress(50);
	//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				    // 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);						    	// 載入角落圖形
	corner.ShowBitmap(background);						    	// 將corner貼到background
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
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

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
    ui.OnMouseMove(nFlags, point);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}


int CGameStateRun::GetNowPlayer()
{
    return nowPlayer;
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//

    bigMap.OnShow(ui.GetSx(), ui.GetSy());              // 貼上地圖
    //以下為UI
    ui.OnShow();
    //人物顯示
    for (int i = 0; i < playercount; i++)
    {
        if(!player[i]->GetBankruptcy())
            player[i]->OnShow(ui.GetSx(), ui.GetSy());
    }
}

}