#pragma once
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
        money      = 300000;
    }
    Player::Player(int t)
    {
        dx         = 96;
        dy         = 96;
        now        = 0;
        remaining  = 0;
        Bankruptcy = false;
        speed      = 64;     //192/8=24 24*(1/30)sec 移動一格       
        direct     = 2;
        ani        = 0;
        count      = 0;
        type       = t;
        money = 300000;
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
        else if (type == 1)
        {
            bmp[2][0].LoadBitmap("res/Suneo_01.bmp", RGB(255, 255, 255));
            bmp[2][1].LoadBitmap("res/Suneo_02.bmp", RGB(255, 255, 255));
            bmp[2][2].LoadBitmap("res/Suneo_03.bmp", RGB(255, 255, 255));
            bmp[2][3].LoadBitmap("res/Suneo_04.bmp", RGB(255, 255, 255));
            bmp[4][0].LoadBitmap("res/Suneo_05.bmp", RGB(255, 255, 255));
            bmp[4][1].LoadBitmap("res/Suneo_06.bmp", RGB(255, 255, 255));
            bmp[4][2].LoadBitmap("res/Suneo_07.bmp", RGB(255, 255, 255));
            bmp[4][3].LoadBitmap("res/Suneo_08.bmp", RGB(255, 255, 255));
            bmp[6][0].LoadBitmap("res/Suneo_09.bmp", RGB(255, 255, 255));
            bmp[6][1].LoadBitmap("res/Suneo_10.bmp", RGB(255, 255, 255));
            bmp[6][2].LoadBitmap("res/Suneo_11.bmp", RGB(255, 255, 255));
            bmp[6][3].LoadBitmap("res/Suneo_12.bmp", RGB(255, 255, 255));
            bmp[8][0].LoadBitmap("res/Suneo_13.bmp", RGB(255, 255, 255));
            bmp[8][1].LoadBitmap("res/Suneo_14.bmp", RGB(255, 255, 255));
            bmp[8][2].LoadBitmap("res/Suneo_15.bmp", RGB(255, 255, 255));
            bmp[8][3].LoadBitmap("res/Suneo_16.bmp", RGB(255, 255, 255));
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
    }
    
    void Player::OnMove()
    {       
        mapData = map->GetMapData();
        //移動
        if (remaining != 0)
        {
            int tx, ty;
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
                if (remaining == 0)
                    if (mapData[now]->GetType() == 2) {
                        money -= 500;
                    }
                    mapData[now]->Arrive();
            }
        }
    
        //動畫控制
        count++;
        if (count >= countmax) {
            count = 0;
            if(remaining!=0)ani++;
            else
            {
                ani = 0;
                direct = 2;
            }
            if (ani >= animax)ani = 0;
        }
    }
    
    void Player::OnShow(int sx, int sy)
    {
        mapData = map->GetMapData();
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
   int Player::GetMoney()
   {
       return money;
   }
   void Player::AdjMoney(int amount)
   {
       money += amount;
   }
   void Player::AdjEstate(int amount)
   {
       estate += amount;
   }
   void Player::OnShowState()
   {
       CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
       CFont f, *fp;
       f.CreatePointFont(240, "Times New Roman");	// 產生 font f; 160表示16 point的字
       fp = pDC->SelectObject(&f);					// 選用 font f
       pDC->SetBkColor(RGB(238, 224, 175));
       pDC->SetTextColor(RGB(0, 0, 0));
       char str[80], name[80];								// Demo 數字對字串的轉換
       sprintf(name, "玩家：%d", type + 1);
       sprintf(str, "財產：%d", money);
       pDC->TextOut(1600, 50, name);
       pDC->TextOut(1600, 100, str);


       pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
       CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
   }
}