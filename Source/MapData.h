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
    private:
        int positionX, positionY;
        int price, owner, type, homeLevel;
        int buildingPositionX, buildingPositionY;
    };
}
