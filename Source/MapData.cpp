#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "MapData.h"

namespace game_framework {
    MapData::MapData()
    {
    }
    void MapData::SetPositionX(int positionX)
    {
        this->positionX = positionX;
    }
    void MapData::SetPositionY(int positionY)
    {
        this->positionY = positionY;
    }
    void MapData::SetPrice(int price)
    {
        this->price = price;
    }
    void MapData::SetOwner(int owner)
    {
        this->owner = owner;
    }
    void MapData::SetType(int type)
    {
        this->type = type;
    }
    void MapData::SetHomeLevel(int homeLevel)
    {
        this->homeLevel = homeLevel;
    }
    void MapData::SetBuildingPoisitionX(int x)
    {
        buildingPositionX = x;
    }
    void MapData::SetBuildingPoisitionY(int y)
    {
        buildingPositionY = y;
    }
    void MapData::Through()
    {
        //
    }
    void MapData::Arrive()
    {
        //做抵達後的事
    }
    int MapData::GetPositionX()
    {
        return positionX;
    }
    int MapData::GetPositionY()
    {
        return positionY;
    }
    int MapData::GetPrice()
    {
        return price;
    }
    int MapData::GetOwner()
    {
        return owner;
    }
    int MapData::GetType()
    {
        return type;
    }
    int MapData::GetHomeLevel()
    {
        return homeLevel;
    }
    int MapData::GetBuildingPositionX()
    {
        return buildingPositionX;
    }
    int MapData::GetBuildingPositionY()
    {
        return buildingPositionY;
    }
}