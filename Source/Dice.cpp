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
        value = 0;
        state = 0;
        count = 0;
        stops = 30;
        playerRun = 0;
    }
    void Dice::LoadBitmap()
    {
        dicebmp[0].LoadBitmap("res/DICE_1.BMP", RGB(1, 0, 0));
        dicebmp[1].LoadBitmap("res/DICE_2.BMP", RGB(1, 0, 0));
        dicebmp[2].LoadBitmap("res/DICE_3.BMP", RGB(1, 0, 0));
        dicebmp[3].LoadBitmap("res/DICE_4.BMP", RGB(1, 0, 0));
        dicebmp[4].LoadBitmap("res/DICE_5.BMP", RGB(1, 0, 0));
        dicebmp[5].LoadBitmap("res/DICE_6.BMP", RGB(1, 0, 0));
    }
   void Dice::OnShow()
    {
        dicebmp[value].SetTopLeft(x, y);
        dicebmp[value].ShowBitmap();
    }

   void Dice::Onmove()
   {
       if (state == 1)
       {
           RandomValue();
           count++;
           
           if (count >= stops)
           {
                state = 0;
                playerRun = 1;
           }
       }
   }
    
    void Dice::SetXY(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
    void Dice::OnLButtonDown()
    {
        if (state == 0)
        {
            state = 1;
            count = 0;
            playerRun = 0;
        }
    }
    void Dice::RandomValue()
    {
        value = rand() % 6;
    }
    int Dice::GetValue()
    {
        return value + 1;
    }
    bool Dice::GetState()
    {
        if (state == 1) return true;
        else return false;
    }
    int Dice::GetPlayerRun()
    {
        return playerRun;
    }
    void Dice::SetPlayerRun(int set)
    {
        playerRun = set;
    }
}
