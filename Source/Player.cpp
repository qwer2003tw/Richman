#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "Player.h"
#include "mygame.h"


namespace game_framework {
    Player::Player()
    {
        dx         = 96;
        dy         = 96;
        now        = 0;
        remaining  = 0;
        Bankruptcy = false;
        speed      = 8;      // 192/8=24 24*(1/30)sec 移動一格       
        direct     = 2;  
        ani        = 0;
        count      = 0;
        type       = 0;      //預設為0
    }
    Player::Player(int t)
    {
        dx         = 96;
        dy         = 96;
        now        = 0;
        remaining  = 0;
        Bankruptcy = false;
        speed      = 8;     //192/8=24 24*(1/30)sec 移動一格       
        direct     = 2;
        ani        = 0;
        count      = 0;
        type       = t;
    
    }
    void Player::LoadBitmap()
    {    
        //type=0 doreamon
        if (type == 0)
        {
            bmp[2][0].LoadBitmap("res/doreamon_swap_part1x1.bmp", RGB(0, 0, 0));
            bmp[2][1].LoadBitmap("res/doreamon_swap_part1x2.bmp", RGB(0, 0, 0));
            bmp[2][2].LoadBitmap("res/doreamon_swap_part1x3.bmp", RGB(0, 0, 0));
            bmp[2][3].LoadBitmap("res/doreamon_swap_part1x4.bmp", RGB(0, 0, 0));
            bmp[4][0].LoadBitmap("res/doreamon_swap_part2x1.bmp", RGB(0, 0, 0));
            bmp[4][1].LoadBitmap("res/doreamon_swap_part2x2.bmp", RGB(0, 0, 0));
            bmp[4][2].LoadBitmap("res/doreamon_swap_part2x3.bmp", RGB(0, 0, 0));
            bmp[4][3].LoadBitmap("res/doreamon_swap_part2x4.bmp", RGB(0, 0, 0));
            bmp[6][0].LoadBitmap("res/doreamon_swap_part3x1.bmp", RGB(0, 0, 0));
            bmp[6][1].LoadBitmap("res/doreamon_swap_part3x2.bmp", RGB(0, 0, 0));
            bmp[6][2].LoadBitmap("res/doreamon_swap_part3x3.bmp", RGB(0, 0, 0));
            bmp[6][3].LoadBitmap("res/doreamon_swap_part3x4.bmp", RGB(0, 0, 0));
            bmp[8][0].LoadBitmap("res/doreamon_swap_part4x1.bmp", RGB(0, 0, 0));
            bmp[8][1].LoadBitmap("res/doreamon_swap_part4x2.bmp", RGB(0, 0, 0));
            bmp[8][2].LoadBitmap("res/doreamon_swap_part4x3.bmp", RGB(0, 0, 0));
            bmp[8][3].LoadBitmap("res/doreamon_swap_part4x4.bmp", RGB(0, 0, 0));
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
    }
    
    void Player::OnMove()
    {       
        //移動
        if (remaining != 0)
        {
            int tx, ty;
            MapData** mapData;
            mapData = map->GetMapData();
            tx = mapData[(now + 1) % map->GetMapCount()]->GetPositionX();
            ty = mapData[(now + 1) % map->GetMapCount()]->GetPositionY();
            if (tx > dx)
            {
                direct = 6;
                dx += speed;
            }
            if (tx < dx)
            {
                direct = 4;
                dx -= speed;
            }
            if (ty > dy)
            {
                direct = 2;
                dy += speed;
            }
            if (ty < dy)
            {
                direct = 8;
                dy -= speed;
            }
            
            if (dx == tx && dy == ty)
            {
                now = (now + 1) % map->GetMapCount();
                mapData[now]->Through();
                remaining--;
                if(remaining==0)
                    mapData[now]->Arrive();
            }
        }
    
        //動畫控制
        count++;
        if (count >= countmax) {
            count = 0;
            if(remaining!=0)ani++;
            else direct = 2;
            if (ani >= animax)ani = 0;
        }
    }
    
    void Player::OnShow(int sx, int sy)
    {
        
        bmp[direct][ani].SetTopLeft(dx -w/2  - sx, dy -h/2 - sy);
        bmp[direct][ani].ShowBitmap(fector);
      
    }
    int Player::GetMapX()
    {
        return dx;
    }
    int Player::GetMapY()
    {
        return dy;
    }
    int Player::GetSpeed()
    {
        return speed;
    }
    bool Player::GetBankruptcy()
    {
        return Bankruptcy;
    }
   void Player::SetMap(Map * m)
    {
        map = m;
    }
   void Player::SetRemaining(int r)
   {
       remaining = r;
   }
   int Player::GetRemaining()
   {
       return remaining;
   }
   int Player::GetNow()
   {
       return now;
   }
}