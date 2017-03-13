#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Dice.h"

namespace game_framework {
    Dice::Dice()
    {
        Initialize();
    }
    void Dice::Initialize()
    {
        x = 120; y = 120;
    }
    void Dice::LoadBitmap()
    {
        animation.AddBitmap("res/DICE_1.BMP", RGB(1, 0, 0));
        animation.AddBitmap("res/DICE_2.BMP", RGB(1, 0, 0));
        animation.AddBitmap("res/DICE_3.BMP", RGB(1, 0, 0));
        animation.AddBitmap("res/DICE_4.BMP", RGB(1, 0, 0));
        animation.AddBitmap("res/DICE_5.BMP", RGB(1, 0, 0));
        animation.AddBitmap("res/DICE_6.BMP", RGB(1, 0, 0));
    }
    void Dice::OnRoll()
    {
        animation.SetDelayCount(3);
        if(isStartRoll)
            animation.OnMove();
    }
    void Dice::OnShow()
    {
        animation.SetTopLeft(x, y);
        animation.OnShow();
    }
    void Dice::SetStartRoll(bool flag)
    {
        isStartRoll = flag;
    }
    void Dice::SetXY(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
}
