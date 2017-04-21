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
        for (int i = 0; i < 15; i++) prop.push_back(new Props);
        PropInit();
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
        money = 300000;
    }
    void Player::LoadBitmap()
    {    
        //type=0 doreamon
        if (type == 0)
        {
            int c = 1;
            char bf[3];
            char s[100];
            char *f = "res/Player/doreamon_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(250, 250, 250));
            }
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
        else if (type == 1)
        {
            int c = 1;
            char bf[3];
            char s[100];
            char *f = "res/Player/Suneo_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
        else if (type == 2)
        {
            int c = 1;
            char bf[3];
            char s[100];
            char *f = "res/Player/Goda_Takeshi_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
        else if (type == 3)
        {
            int c = 1;
            char bf[3];
            char s[100];
            char *f = "res/Player/Minamoto_Shizuka_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
        else if (type == 4)
        {
            int c = 1;
            char bf[3];
            char s[100];
            char *f = "res/Player/Nobi_Nobita_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
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
   void Player::SetSpeed(int sp)
   {
       speed = sp;
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
       f.CreatePointFont(300, "Times New Roman");	// 產生 font f; 160表示16 point的字
       fp = pDC->SelectObject(&f);					// 選用 font f
       pDC->SetBkMode(TRANSPARENT);
       //pDC->SetBkColor(RGB(238, 224, 175));
       pDC->SetTextColor(RGB(0, 0, 0));
       char str[80], name[80];								// Demo 數字對字串的轉換
       sprintf(name, "玩家：%d", type + 1);
       sprintf(str, "財產：%d", money);
       pDC->TextOut(1550, 25, name);
       pDC->TextOut(1550, 100, str);


       pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
       CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
   }

   void Player::GiveProp(int index, int amount)
   {
       if (amount > 0)
       {
           for (int i = 0; i < 15; i++)
           {
               if (prop.at(i)->index == index) {
                   prop.at(i)->amount += amount;
                   return;
               }
           }

           for (int i = 0; i < 15; i++)
           {
               if (prop.at(i)->index == -1)
               {
                   prop.at(i)->amount += amount;
                   prop.at(i)->index = index;
                   return;
               }
           }
       }
       else
       {
           if (index == -1) return;
           vector<Props*>::iterator it;
           for (it = prop.begin(); it != prop.end();)
           {
               if ((*it)->index == index)
               {
                   it=prop.erase(it);
                   continue;
               }
               ++it;
           }
       }
       
       //TRACE("prop[0].index=%d", prop.at(0)->index);
       
   }

   void Player::PropInit()
   {
       for (int i = 0; i < 4; i++) GiveProp(i, 1);
   }
   
}