#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Player.h"

namespace game_framework {
    Player::Player()
    {
        dx = 96;
        dy = 96;
    }
    void Player::LoadBitmap()
    {
        bmp.LoadBitmap("res/ball.bmp", RGB(255, 255, 255));
    }
    void Player::OnMove(int x,int y)
    {
        if (x == 1 && y == 0) dx += 192;
        else if (x == -1 && y == 0) dx -= 192;
        else if (x == 0 && y == 1) dy -= 192;
        else if (x == 0 && y == -1) dy += 192;
        x = 0;
        y = 0;
    }
    void Player::OnShow()
    {
        SetXY();
        bmp.SetTopLeft(dx - x, dy - y);
        bmp.ShowBitmap();

    }
    void Player::SetXY()
    {
        x = bmp.Height() / 2;
        y = bmp.Width() / 2;
    }
}