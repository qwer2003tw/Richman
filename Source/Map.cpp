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
        for (int i = 0; i < 40; i++)mapData[i] = nullptr;
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
            mapData[i]->SetOwner(99);       // 初始
            mapData[i]->SetHomeLevel(0);    // 初始
            mapData[i]->SetType(0);         // 初始
            mapData[i]->SetPropIndex(99);   // 初始
        }
        for (int i = 2; i < 8; i++)         
        {
            // 上排區
            mapData[i]->SetType(1);             // 1住宅區
            mapData[i]->SetBuildingPoisitionX(mapData[i]->GetPositionX() - 96);
            mapData[i]->SetBuildingPoisitionY(mapData[i]->GetPositionY() + 96);
            mapData[i]->SetOwner(99);
            mapData[i]->SetPrice(800);
            // 右排區
            mapData[i + 9]->SetType(1);         // 1住宅區
            mapData[i + 9]->SetBuildingPoisitionX(mapData[i + 9]->GetPositionX() - 288);
            mapData[i + 9]->SetBuildingPoisitionY(mapData[i + 9]->GetPositionY() - 96);
            mapData[i + 9]->SetOwner(99);
            mapData[i + 9]->SetPrice(1200);
            // 下排區
            mapData[i + 18]->SetType(1);         // 1住宅區
            mapData[i + 18]->SetBuildingPoisitionX(mapData[i + 18]->GetPositionX() - 96);
            mapData[i + 18]->SetBuildingPoisitionY(mapData[i + 18]->GetPositionY() - 288);
            mapData[i + 18]->SetOwner(99);
            mapData[i + 18]->SetPrice(1000);
            // 左排區
            mapData[i + 27]->SetType(1);         // 1住宅區
            mapData[i + 27]->SetBuildingPoisitionX(mapData[i + 27]->GetPositionX() + 96);
            mapData[i + 27]->SetBuildingPoisitionY(mapData[i + 27]->GetPositionY() - 96);
            mapData[i + 27]->SetOwner(99);
            mapData[i + 27]->SetPrice(1500);
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
    Map::~Map()
    {
        for (int i = 0; i < 36; i++) if (mapData != nullptr) delete mapData[i];
    }
    void Map::LoadBitmap()
    {
        map.LoadBitmap("res/MAP.bmp", RGB(255, 255, 255));
        // 人物種類 0多拉A夢 1胖虎 2靜香 3大雄 4小夫

        house[0][0].LoadBitmap("res/House_level0_0.bmp", RGB(0, 0, 0));
        house[1][0].LoadBitmap("res/House_level0_2.bmp", RGB(0, 0, 0));
        house[2][0].LoadBitmap("res/House_level0_4.bmp", RGB(0, 0, 0));
        house[3][0].LoadBitmap("res/House_level0_3.bmp", RGB(255, 255, 255)); //眼鏡白底的
        house[4][0].LoadBitmap("res/House_level0_1.bmp", RGB(0, 0, 0));

        house[0][1].LoadBitmap("res/House_level1_0.bmp", RGB(0, 0, 0));
        house[1][1].LoadBitmap("res/House_level1_2.bmp", RGB(0, 0, 0));
        house[2][1].LoadBitmap("res/House_level1_4.bmp", RGB(0, 0, 0));
        house[3][1].LoadBitmap("res/House_level1_3.bmp", RGB(0, 0, 0));
        house[4][1].LoadBitmap("res/House_level1_1.bmp", RGB(0, 0, 0));

        house[0][2].LoadBitmap("res/House_level2_0.bmp", RGB(0, 0, 0));
        house[1][2].LoadBitmap("res/House_level2_2.bmp", RGB(0, 0, 0));
        house[2][2].LoadBitmap("res/House_level2_4.bmp", RGB(0, 0, 0));
        house[3][2].LoadBitmap("res/House_level2_3.bmp", RGB(0, 0, 0));
        house[4][2].LoadBitmap("res/House_level2_1.bmp", RGB(0, 0, 0));

        house[0][3].LoadBitmap("res/House_level3_0.bmp", RGB(0, 0, 0));
        house[1][3].LoadBitmap("res/House_level3_2.bmp", RGB(0, 0, 0));
        house[2][3].LoadBitmap("res/House_level3_4.bmp", RGB(0, 0, 0));
        house[3][3].LoadBitmap("res/House_level3_3.bmp", RGB(0, 0, 0));
        house[4][3].LoadBitmap("res/House_level3_1.bmp", RGB(0, 0, 0));

        props[0].LoadBitmap("res/Landmine.bmp", RGB(255, 255, 255));
        props[1].LoadBitmap("res/Roadblocks.bmp", RGB(255, 255, 255));
        props[2].LoadBitmap("res/Timebombs.bmp", RGB(255, 255, 255));
        props[3].LoadBitmap("res/Remotedice.bmp", RGB(255, 255, 255));
    }

    void Map::OnShow(int sx, int sy)
    {
        map.SetTopLeft(-sx, -sy);
        map.ShowBitmap();
        for (int i = 0; i < 36; i++)
        {
            if (mapData[i]->GetOwner() != 99 && mapData[i]->GetType() == 1)
            {
                 house[mapData[i]->GetOwner()][mapData[i]->GetHomeLevel()].SetTopLeft(-sx + mapData[i]->GetBuildingPositionX(), -sy + mapData[i]->GetBuildingPositionY());
                 house[mapData[i]->GetOwner()][mapData[i]->GetHomeLevel()].ShowBitmap();
            }
            if (mapData[i]->GetPropIndex() != 99)
            {
                // 道具置中 45
                props[mapData[i]->GetPropIndex()].SetTopLeft(mapData[i]->GetPositionX() - sx - 45, mapData[i]->GetPositionY() - sy - 45);
                props[mapData[i]->GetPropIndex()].ShowBitmap(1.5);
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

    void Map::SetPropIndex(int index, int position)
    {
        mapData[position]->SetPropIndex(index);
    }
    int Map::GetPropIndex(int position)
    {
        return mapData[position]->GetPropIndex();
    }
    CMovingBitmap* Map::GetHouse()
    {
        return &house[0][0];
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


