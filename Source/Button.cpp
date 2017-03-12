#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Button.h"

namespace game_framework {
    Button::Button()
    {
        x = 0;
        y = 0;
        state = 0;
        enable = false;
        n = 0;
    }
    Button::Button(int sn)
    {
        x = 0;
        y = 0;
        enable = false;
        n = sn;
        state = 0;

    }
    void Button::LoadBitmap()
    {
        bmp[0].LoadBitmap(IDB_BUTTON_START_1, RGB(255, 255, 255));
        bmp[1].LoadBitmap(IDB_BUTTON_START_2, RGB(255, 255, 255));
    }
    void Button::OnShow()
    {
        bmp[state].SetTopLeft(x, y);
        if (enable)
            bmp[state].ShowBitmap();
    }
    void Button::SetXY(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
    void Button::SetEnable(bool e)
    {
        enable = e;
    }
    void Button::OnClick(CPoint point)
    {
        int mx = point.x;
        int my = point.y;
        int w = bmp[0].Width();
        int h = bmp[0].Height();
        int t = -12;
        int x1 = x - t;
        int x2 = x + w + t;
        int y1 = y - t;
        int y2 = y + h + t;
        if (mx >= x1&&mx <= x2&&my >= y1&&my <= y2)
        {
            state=1;
            cga->GotoGameState(GAME_STATE_RUN);
            //GotoGameState(GAME_STATE_RUN);
        }
    }
    void Button::OnNoClick()
    {
        state = 0;
    }
    void Button::OnMove(CPoint point)
    {
        int mx = point.x;
        int my = point.y;
        int w = bmp[0].Width();
        int h = bmp[0].Height();
        int t = 2;
        int x1 = x - t;
        int x2 = x + w + t;
        int y1 = y - t;
        int y2 = y + h + t;
        if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2) // 表示滑鼠目前在按鍵位置上
            state = 1;     
        else
            state = 0;          
    }
    void Button::Setcga(CGameState * c)
    {
        cga = c;
    }
}