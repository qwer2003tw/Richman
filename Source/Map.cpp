#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include <vector>
#include "MapData.h"
#include <math.h>
namespace game_framework {
    Map::Map()
    {
        int dx[4] = { 192,0,-192,0 };
        int dy[4] = { 0,192,0,-192 };
        int nx = 96;
        int ny = 96;
        for (int i = 0; i < 36; i++)
        {
            mapData[i] = new MapData();
            mapData[i]->SetPositionX(nx);
            mapData[i]->SetPositionY(ny);
            nx += dx[i / 9];
            ny += dy[i / 9];
            mapData[i]->SetOwner(99);        // 初始
            mapData[i]->SetHomeLevel(0);
            mapData[i]->SetType(0);         // 初始
        }
        for (int i = 2; i < 8; i++)         
        {
            // 上排區
            mapData[i]->SetType(1);             // 1住宅區
            mapData[i]->SetBuildingPoisitionX(mapData[i]->GetPositionX() - 96);
            mapData[i]->SetBuildingPoisitionY(mapData[i]->GetPositionY() + 96);
            mapData[i]->SetOwner(99);
            // 右排區
            mapData[i + 9]->SetType(1);         // 1住宅區
            mapData[i + 9]->SetBuildingPoisitionX(mapData[i + 9]->GetPositionX() - 288);
            mapData[i + 9]->SetBuildingPoisitionY(mapData[i + 9]->GetPositionY() - 96);
            mapData[i + 9]->SetOwner(99);
            // 下排區
            mapData[i + 18]->SetType(1);         // 1住宅區
            mapData[i + 18]->SetBuildingPoisitionX(mapData[i + 18]->GetPositionX() - 96);
            mapData[i + 18]->SetBuildingPoisitionY(mapData[i + 18]->GetPositionY() - 288);
            mapData[i + 18]->SetOwner(99);
            // 左排區
            mapData[i + 27]->SetType(1);         // 1住宅區
            mapData[i + 27]->SetBuildingPoisitionX(mapData[i + 27]->GetPositionX() + 96);
            mapData[i + 27]->SetBuildingPoisitionY(mapData[i + 27]->GetPositionY() - 96);
            mapData[i + 27]->SetOwner(99);
        }
        // 事件格設定
        for (int i = 0; i < 3; i++) {
            if((i-1)==-1) mapData[35]->SetType(2);
            else mapData[i-1]->SetType(2);                // 2事件格
            mapData[i+8]->SetType(2);              // 2事件格
            mapData[i+17]->SetType(2);             // 2事件格
            mapData[i+26]->SetType(2);             // 2事件格
        }

    }
    void Map::LoadBitmap()
    {
        map.LoadBitmap("res/MAP.bmp", RGB(255, 255, 255));
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 36; j++)
            {
                if (i == 1)house[i][0][j].LoadBitmap("res/House_level0_1.bmp", RGB(0, 0, 0));
                else house[i][0][j].LoadBitmap("res/House_level0.bmp", RGB(0, 0, 0));
                house[i][1][j].LoadBitmap("res/House_level1.bmp", RGB(0, 0, 0));
                house[i][2][j].LoadBitmap("res/House_level2.bmp", RGB(0, 0, 0));
                house[i][3][j].LoadBitmap("res/House_level3.bmp", RGB(0, 0, 0));
            }
        }
    }

    void Map::OnShow(int sx, int sy)
    {
        map.SetTopLeft(-sx, -sy);
        map.ShowBitmap();
        for (int i = 0; i < 36; i++)
        {
            if (GetMapData()[i]->GetOwner() != 99 && GetMapData()[i]->GetType() == 1)
            {
                house[mapData[i]->GetOwner()][mapData[i]->GetHomeLevel()][i].SetTopLeft(-sx + mapData[i]->GetBuildingPositionX(), -sy + mapData[i]->GetBuildingPositionY());
                house[mapData[i]->GetOwner()][mapData[i]->GetHomeLevel()][i].ShowBitmap();
            }
        }
    }
    void Map::Build(int nowPlayer, int nowPosition)
    {
        mapData[nowPosition]->SetOwner(nowPlayer);
        mapData[nowPosition]->SetHomeLevel(0);
    }
    void Map::Upgrade(int nowPosition)
    {
        mapData[nowPosition]->SetHomeLevel(mapData[nowPosition]->GetHomeLevel() + 1);
    }
    MapData ** Map::GetMapData()
    {
        return mapData;
    }
    int Map::GetMapCount()
    {
        return mapcount;
    }
}


