#pragma once
#include "Map.h"
namespace game_framework {
    class Props
    {
    public:
        Props() {
            index = -1;
            amount = 0;
        }
        int index;
        int amount;
    };
    
    
    class Player {
    public:
        Player();
        Player(int t);
        void LoadBitmap();							// ���J�ϧ�
        void OnMove();			                    // ����
        void OnShow(int sx, int sy);				// �N�ϧζK��e�� 
        int GetMapX();                              // ���o�H���a�Ϯy�� X
        int GetMapY();                              // ���o�H���a�Ϯy�� Y
        int GetSpeed();
        bool GetBankruptcy();
        void SetMap(Map* m);                        // 
        void SetRemaining(int r);
        int  GetRemaining();
        int GetNow();
        int GetMoney();                             //��o����
        void AdjMoney(int amount);                  //�W�[�δ�֪���                           
        void AdjEstate(int amount);                 //
        void OnShowState();
        void GiveProp(int index,int amount);
        void PropInit();
        vector<Props*> prop;
    protected:
        Map* map;
        MapData** mapData;                          //Ū���a�ϸ�T
    private:
        int dx, dy;					                //�H���a�Ϯy��
        bool Bankruptcy;                            //�O�_�}��
        int now;                                    //�ثe�Ҧb��m
        int remaining;                              //�Ѿl�B��

        //   �H�U���H���]��
        int money;                                  //�֦����B
        int estate;                                 //�Цa���ƶq

        //  �H�U���ʵe����
        int w, h;                                   //�Ϥ��e�שM����
        CMovingBitmap bmp[10][5];			        // �H���Ϥ�
        int direct;                                 //2�U 6�k 8�W 4��
        int speed;                                  //���ʳt��
        int type;                                   //�H������1 
        int count;                                  //��e
        int countmax;                               //�C�X��ONMOVE���U�@�i��
        int ani;                                    //��e
        int animax;                                 //�`�@�ϼ�
        int fector;                                 //�Y��j�p
                                  
        //
        
    };
}
