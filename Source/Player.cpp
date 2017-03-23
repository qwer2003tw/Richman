#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Player.h"
#include "mygame.h"

namespace game_framework {
    Player::Player()
    {
        dx = positionX[0] = 96;
        dy = positionY[0] = 96;
        positionNum = 0;
        prePositionNum = 0;
        state = 0;
        for (int i = 1; i < 10; i++)                   //產生人物移動路徑座標 0-36
        {
            positionX[i] = positionX[i - 1] + 192;
            positionY[i] = 96;
        }
        for (int i = 10; i < 19; i++)
        {
            positionX[i] = positionX[9];
            positionY[i] = positionY[i - 1] + 192;
        }
        for (int i = 19; i < 28; i++)
        {
            positionX[i] = positionX[i - 1] - 192;
            positionY[i] = positionY[18];
        }
        for (int i = 28; i < 36; i++)
        {
            positionX[i] = positionX[27];
            positionY[i] = positionY[i - 1] - 192;
        }
    }
    void Player::LoadBitmap()
    {
        bmp.LoadBitmap("res/ball.bmp", RGB(0, 0, 0));
    }
    void Player::OnMove()
    {       
        if (state == 1) {
            //從當前位置到累加位置一格一格遞增
            if (positionNum != prePositionNum && dx == positionX[prePositionNum] && dy == positionY[prePositionNum])
            {
                prePositionNum++;           
                prePositionNum %= 36;
            }
            if (dx < positionX[prePositionNum]) dx += 8;
            else if (dx > positionX[prePositionNum]) dx-=8;
            if (dy < positionY[prePositionNum]) dy+=8;
            else if (dy > positionY[prePositionNum]) dy-=8;
            if (prePositionNum == positionNum && dx == positionX[prePositionNum] && dy == positionY[prePositionNum])
                state = 0;
        }
    }
    void Player::OnShow(int sx, int sy)
    {
        bmp.SetTopLeft(dx - bmp.Height() / 2 - sx, dy - bmp.Width() / 2 -sy);
        bmp.ShowBitmap();
    }
    int Player::GetMapX()
    {
        return dx;
    }
    int Player::GetMapY()
    {
        return dy;
    }
    void Player::SetPositionNum(int amount)
    {
        prePositionNum = positionNum % 36;
        positionNum += amount;
        positionNum %= 36;
    }
    void Player::SetState(int ns)
    {
        state = ns;
    }
}