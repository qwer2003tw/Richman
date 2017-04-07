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
        signal = 0;
    }
    Button::Button(int sn)
    {
        x = 0;
        y = 0;
        enable = false;
        n = sn;
        state = 0;
        signal = 0;

    }
    void Button::LoadBitmap(char* fileName1, char* fileName2, COLORREF colorkey)
    {
        bmp[0].LoadBitmap(fileName1, colorkey);
        bmp[1].LoadBitmap(fileName2, colorkey);
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
        int t = 3;
        int x1 = x;
        int x2 = x + w;
        int ch = x + (w / 2);
        int y1 = y;
        int y2 = y + h;
        int ck = y + (h / 2);

        if (n == 0)
        {
            if (pow((mx - ch + t), 2) + pow((my - ck), 2) <= pow((w / 2), 2))  //圓形不等式
            {
                state = 1;
                signal = 1;
            }
        }
        else
        {
            if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2)
            {
                state = 1;
                signal = 1;
            }
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
        int t = 3;
        int x1 = x;
        int x2 = x + w;
        int ch = x + (w / 2);

        int y1 = y;
        int y2 = y + h;
        int ck = y + (h / 2);
        if (n == 0)
        {
            if (pow((mx - ch + t), 2) + pow((my - ck), 2) <= pow((w / 2), 2)) state = 1;  //圓形不等式
            else state = 0;
        }
        else
        {
            if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2) // 表示滑鼠目前在按鍵位置上
                state = 1;
            else
                state = 0;
        }

              
    }
    int Button::GetSignal()
    {
        return signal;
    }
    void Button::SetSignal(int s)
    {
        signal = 0; // reset
    }
}