#include "stdafx.h"
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Number.h" 

namespace game_framework {
    Number::Number()
    {
        Initialize();
    }

    void Number::Initialize()
    {
        x = y = 0;
    }

    void Number::LoadBitmap()
    {
        digitbmp[0].LoadBitmap("res/BMP0.BMP", RGB(255, 255, 255));
        digitbmp[1].LoadBitmap("res/BMP1.BMP", RGB(255, 255, 255));
        digitbmp[2].LoadBitmap("res/BMP2.BMP", RGB(255, 255, 255));
        digitbmp[3].LoadBitmap("res/BMP3.BMP", RGB(255, 255, 255));
        digitbmp[4].LoadBitmap("res/BMP4.BMP", RGB(255, 255, 255));
        digitbmp[5].LoadBitmap("res/BMP5.BMP", RGB(255, 255, 255));
        digitbmp[6].LoadBitmap("res/BMP6.BMP", RGB(255, 255, 255));
        digitbmp[7].LoadBitmap("res/BMP7.BMP", RGB(255, 255, 255));
        digitbmp[8].LoadBitmap("res/BMP8.BMP", RGB(255, 255, 255));
        digitbmp[9].LoadBitmap("res/BMP9.BMP", RGB(255, 255, 255));
    }
    void Number::OnShow(int value)
    {
        digitbmp[value].SetTopLeft(x, y);
        digitbmp[value].ShowBitmap();
    }
    void Number::SetXY(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
}




