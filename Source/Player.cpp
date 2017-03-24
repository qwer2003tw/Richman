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
        count = 0;
        direct = 2;
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
        bmp[0][2][0].LoadBitmap("res/doreamon_swap_part1x1.bmp", RGB(0, 0, 0));
        bmp[0][2][1].LoadBitmap("res/doreamon_swap_part1x2.bmp", RGB(0, 0, 0));
        bmp[0][2][2].LoadBitmap("res/doreamon_swap_part1x3.bmp", RGB(0, 0, 0));
        bmp[0][2][3].LoadBitmap("res/doreamon_swap_part1x4.bmp", RGB(0, 0, 0));
        bmp[0][4][0].LoadBitmap("res/doreamon_swap_part2x1.bmp", RGB(0, 0, 0));
        bmp[0][4][1].LoadBitmap("res/doreamon_swap_part2x2.bmp", RGB(0, 0, 0));
        bmp[0][4][2].LoadBitmap("res/doreamon_swap_part2x3.bmp", RGB(0, 0, 0));
        bmp[0][4][3].LoadBitmap("res/doreamon_swap_part2x4.bmp", RGB(0, 0, 0));
        bmp[0][6][0].LoadBitmap("res/doreamon_swap_part3x1.bmp", RGB(0, 0, 0));
        bmp[0][6][1].LoadBitmap("res/doreamon_swap_part3x2.bmp", RGB(0, 0, 0));
        bmp[0][6][2].LoadBitmap("res/doreamon_swap_part3x3.bmp", RGB(0, 0, 0));
        bmp[0][6][3].LoadBitmap("res/doreamon_swap_part3x4.bmp", RGB(0, 0, 0));
        bmp[0][8][0].LoadBitmap("res/doreamon_swap_part4x1.bmp", RGB(0, 0, 0));
        bmp[0][8][1].LoadBitmap("res/doreamon_swap_part4x2.bmp", RGB(0, 0, 0));
        bmp[0][8][2].LoadBitmap("res/doreamon_swap_part4x3.bmp", RGB(0, 0, 0));
        bmp[0][8][3].LoadBitmap("res/doreamon_swap_part4x4.bmp", RGB(0, 0, 0));

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
            if (dx < positionX[prePositionNum])
            {
                direct = 6;
                dx += 8;
            }
            else if (dx > positionX[prePositionNum])
            {
                direct = 4;
                dx -= 8;
            }
            if (dy < positionY[prePositionNum])
            {
                direct = 2;
                dy += 8;
            }
            else if (dy > positionY[prePositionNum])
            {
                direct = 8;
                dy -= 8;
            }
            if (prePositionNum == positionNum && dx == positionX[prePositionNum] && dy == positionY[prePositionNum])
                state = 0;
        }
    }
    void Player::OnShow(int sx, int sy)
    {
        if (count >= 20) count = 0;
        bmp[0][direct][count/5].SetTopLeft(dx - 3*bmp[0][direct][count/5].Height() / 2 - sx, dy -8* bmp[0][direct][count/5].Width() / 2 - sy);
        bmp[0][direct][count/5].ShowBitmap(5);
        if (state == 0) direct = 2;
        if (state != 0)count++;
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