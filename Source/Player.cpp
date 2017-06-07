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
        speed      = 8;      // 192/8=24 24*(1/30)sec ���ʤ@��       
        direct     = 2;  
        ani        = 0;
        count      = 0;
        type       = 0;      //�w�]��0
        money      = 300000;
    }
    Player::Player(int t, int o)
    {
        for (int i = 0; i < 15; i++) prop.push_back(new Props);
        PropInit();
        dx         = 96;
        dy         = 96;
        now        = 0;
        remaining  = 0;
        stop       = 0;
        Bankruptcy = false;
        speed      = 64;     //192/8=24 24*(1/30)sec ���ʤ@��       
        direct     = 2;
        ani        = 0;
        count      = 0;
        type       = t;
        order      = o;
        money      = 300000;
        isInjury   = false;
        isHaveTimeBombs = false;
        TimeBombsCounter = 0;
    }
    Player::~Player()
    {
        for (unsigned int i = 0; i < prop.size(); i++) delete prop[i];
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
            bmpInjury.LoadBitmap("res/Player/doreamon_injury.bmp", RGB(250, 250, 250));
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
            char *f = "res/Player/Suneo_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            bmpInjury.LoadBitmap("res/Player/Suneo_injury.bmp", RGB(250, 250, 250));
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
            char *f = "res/Player/Goda_Takeshi_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            bmpInjury.LoadBitmap("res/Player/Goda_Takeshi_injury.bmp", RGB(255, 255, 255));
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
            char *f = "res/Player/Nobi_Nobita_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            bmpInjury.LoadBitmap("res/Player/Nobi_Nobita_injury.bmp", RGB(255, 255, 255));
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
            char *f = "res/Player/Minamoto_Shizuka_";
            char *b = ".bmp";
            for (int k = 2; k <= 8; k += 2) for (int j = 0; j < 4; j++)
            {
                sprintf(bf, "%02d", c++);
                sprintf(s, "%s%s%s", f, bf, b);
                bmp[k][j].LoadBitmap(s, RGB(255, 255, 255));
            }
            //bmpInjury.LoadBitmap("res/Player/Nobi_Nobita_injury", RGB(250, 250, 250));
            countmax = 4;
            animax = 4;
            fector = 3;
            w = bmp[2][0].Width()*fector;
            h = bmp[2][0].Height()*fector;
        }
        playerHead[0].LoadBitmap("res/player/doreamon_Head.bmp", RGB(1, 0, 0));
        playerHead[1].LoadBitmap("res/player/Goda_Takeshi_Head.bmp", RGB(1, 0, 0));
        playerHead[2].LoadBitmap("res/player/Minamoto_Shizuka_Head.bmp", RGB(1, 0, 0));
        playerHead[3].LoadBitmap("res/player/Nobi_Nobita_Head.bmp", RGB(1, 0, 0));
        playerHead[4].LoadBitmap("res/player/Suneo_Head.bmp", RGB(1, 0, 0));
        timeBombs.LoadBitmap("res/Timebombs.bmp", RGB(255, 255, 255));
        for (int i = 0; i < 2; i++)
        {
            number[i][0].LoadBitmap("res/BMP0.BMP", RGB(255, 255, 255));
            number[i][1].LoadBitmap("res/BMP1.BMP", RGB(255, 255, 255));
            number[i][2].LoadBitmap("res/BMP2.BMP", RGB(255, 255, 255));
            number[i][3].LoadBitmap("res/BMP3.BMP", RGB(255, 255, 255));
            number[i][4].LoadBitmap("res/BMP4.BMP", RGB(255, 255, 255));
            number[i][5].LoadBitmap("res/BMP5.BMP", RGB(255, 255, 255));
            number[i][6].LoadBitmap("res/BMP6.BMP", RGB(255, 255, 255));
            number[i][7].LoadBitmap("res/BMP7.BMP", RGB(255, 255, 255));
            number[i][8].LoadBitmap("res/BMP8.BMP", RGB(255, 255, 255));
            number[i][9].LoadBitmap("res/BMP9.BMP", RGB(255, 255, 255));
        }
    }
    
    void Player::OnMove()
    {       
        mapData = map->GetMapData();
        //����
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
                if (isHaveTimeBombs)
                {
                    TimeBombsCounter--;
                }
                 mapData[now]->Arrive();
            }
        }
        if (isHaveTimeBombs && TimeBombsCounter == 0)
        {
            remaining = 0;
            isHaveTimeBombs = false;
            isInjury = true;
        }
        //�ʵe����
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
        if (isHaveTimeBombs)
        {
            timeBombs.SetTopLeft(dx - w / 3 + 5 - sx, dy - h / 2 - 33 - sy);
            timeBombs.ShowBitmap(0.6);
            number[0][TimeBombsCounter / 10].SetTopLeft(dx - w / 3 + 13 - sx, dy - h / 2 - 30 - sy);
            number[0][TimeBombsCounter / 10].ShowBitmap(0.2);
            number[1][TimeBombsCounter % 10].SetTopLeft(dx - w / 3 + 23 - sx, dy - h / 2 - 30 - sy);
            number[1][TimeBombsCounter % 10].ShowBitmap(0.2);
        }
        if (isInjury)
        {
            bmpInjury.SetTopLeft(dx - w / 2 - sx, dy - h / 2 - sy);
            bmpInjury.ShowBitmap(fector);
        }
        else
        {
            bmp[direct][ani].SetTopLeft(dx - w / 2 - sx, dy - h / 2 - sy);
            bmp[direct][ani].ShowBitmap(fector);
        }
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
   void Player::SetStop(int stop)
   {
       this->stop = stop;
   }
   int Player::GetStop()
   {
       return stop;
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
   int Player::GetType()
   {
       return type;
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
       playerHead[type].SetTopLeft(1600, 25);
       playerHead[type].ShowBitmap();
       CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
       CFont f, *fp;
       f.CreatePointFont(300, "Microsoft JhengHei");	// ���� font f; 160���16 point���r
       fp = pDC->SelectObject(&f);					// ��� font f
       pDC->SetBkMode(TRANSPARENT);
       //pDC->SetBkColor(RGB(238, 224, 175));
       pDC->SetTextColor(RGB(0, 0, 0));
       char str[80], name[80];								// Demo �Ʀr��r�ꪺ�ഫ
       sprintf(name, "���a�G%d", order + 1);
       sprintf(str, "�]���G%d", money);

       pDC->TextOut(1535, 225, name);
       pDC->TextOut(1535, 300, str);



       pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
       CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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
                   delete *it;
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

   void Player::SetInjury(bool injury)
   {
       isInjury = injury;
   }

   void Player::SetHaveBombs(bool bombs)
   { 
       isHaveTimeBombs = bombs;
   }

   void Player::SetTimeBombsCounter(int count)
   {
       TimeBombsCounter = count;
   }

   bool Player::GetInjury()
   {
       return isInjury;
   }

   bool Player::GetBombs()
   {
       return isHaveTimeBombs;
   }

   int Player::GetTimeBombsCounter()
   {
       return TimeBombsCounter;
   }
   
}