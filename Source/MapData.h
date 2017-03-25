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
        int GetPositionX();
        int GetPositionY();
        int GetPrice();
        int GetOwner();
        int GetType();
        int GetHomeLevel();
    private:
        int positionX, positionY;
        int price, owner, type, homeLevel;
    };
}
