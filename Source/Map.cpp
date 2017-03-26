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
        }
        //1~9 10~18 19~27 28~35
        /*
        for (int i = 1; i < 10; i++)                   //產生人物移動路徑座標 0-36
        {
            mapData[i].SetPositionX(mapData[i - 1].GetPositionX() + 192);
            mapData[i].SetPositionY(96);
        }
        for (int i = 10; i < 19; i++)
        {
            mapData[i].SetPositionX(mapData[9].GetPositionX());
            mapData[i].SetPositionY(mapData[i - 1].GetPositionY() + 192);
        }
        for (int i = 19; i < 28; i++)
        {
            mapData[i].SetPositionX(mapData[i - 1].GetPositionX() - 192);
            mapData[i].SetPositionY(mapData[18].GetPositionY());
        }
        for (int i = 28; i < 36; i++)
        {
            mapData[i].SetPositionX(mapData[27].GetPositionX());
            mapData[i].SetPositionY(mapData[i - 1].GetPositionY() - 192);
        }
        */
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


