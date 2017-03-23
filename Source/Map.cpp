#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework {
    Map::Map()
    {
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
}


