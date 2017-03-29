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
            mapData[i]->SetOwner(0);        // 0不屬於任何人
        }
        for (int i = 2; i < 8; i++)         
        {
            // 上排區
            mapData[i]->SetType(0);             // 0住宅區
            mapData[i]->SetBuildingPoisitionX(mapData[i]->GetPositionX() - 96);
            mapData[i]->SetBuildingPoisitionY(mapData[i]->GetPositionY() + 96);
            // 右排區
            mapData[i + 9]->SetType(0);         // 0住宅區
            mapData[i + 9]->SetBuildingPoisitionX(mapData[i]->GetPositionX() - 288);
            mapData[i + 9]->SetBuildingPoisitionY(mapData[i]->GetPositionY() - 96);
            // 下排區
            mapData[i + 18]->SetType(0);         // 0住宅區
            mapData[i + 18]->SetBuildingPoisitionX(mapData[i]->GetPositionX() - 96);
            mapData[i + 18]->SetBuildingPoisitionY(mapData[i]->GetPositionY() - 288);
            // 左排區
            mapData[i + 27]->SetType(0);         // 0住宅區
            mapData[i + 27]->SetBuildingPoisitionX(mapData[i]->GetPositionX() + 96);
            mapData[i + 27]->SetBuildingPoisitionY(mapData[i]->GetPositionY() - 96);

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
    }

    void Map::OnShow(int sx, int sy)
    {
        map.SetTopLeft(-sx, -sy);
        map.ShowBitmap();
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


