#pragma once
namespace game_framework {
    class MapData {
    public:
        MapData();
        void SetPositionX(int positionX);
        void SetPositionY(int positionY);
        void SetPrice(int price);
        void SetOwner(int owner);
        void SetType(int type);
        void SetHomeLevel(int homeLevel);
        void SetBuildingPoisitionX(int x);
        void SetBuildingPoisitionY(int y);
        void SetPropIndex(int index);
        void Through();//經過
        void Arrive();//到達
        int GetPositionX();
        int GetPositionY();
        int GetPrice();
        int GetOwner();
        int GetType();
        int GetHomeLevel();
        int GetBuildingPositionX();
        int GetBuildingPositionY();
        int GetPropIndex();
    private:
        int positionX, positionY;
        int price;
        int owner;
        int type;                                     // 格子的種類 0->可蓋房子 1->已蓋房子 2->事件格子
        int homeLevel;
        int buildingPositionX, buildingPositionY;
        int propIndex;                                // 放置的道具
    };
}
