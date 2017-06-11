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
        void Through();//�g�L
        void Arrive();//��F
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
        int type;                                     // ��l������ 0->�i�\�Фl 1->�w�\�Фl 2->�ƥ��l
        int homeLevel;
        int buildingPositionX, buildingPositionY;
        int propIndex;                                // ��m���D��
    };
}
