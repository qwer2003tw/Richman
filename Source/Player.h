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
        Player(int t, int o);
        void LoadBitmap();							// ���J�ϧ�
        void OnMove();			                    // ����
        void OnShow(int sx, int sy);				// �N�ϧζK��e�� 
        int GetMapX();                              // ���o�H���a�Ϯy�� X
        int GetMapY();                              // ���o�H���a�Ϯy�� Y
        int GetSpeed();
        bool GetBankruptcy();
        void SetMap(Map* m);                        // 
        void SetRemaining(int r);
        void SetSpeed(int sp);
        void SetStop(int stop);
        int GetStop();
        int GetRemaining();
        int GetNow();
        int GetMoney();                             //��o����
        int GetType();
        void AdjMoney(int amount);                  //�W�[�δ�֪���                           
        void AdjEstate(int amount);                 //
        void OnShowState();
        void GiveProp(int index,int amount);
        void PropInit();
        void SetInjury(bool injury);
        void SetHaveBombs(bool bombs);
        void SetTimeBombsCounter(int count);
        bool GetInjury();
        bool GetBombs();
        int GetTimeBombsCounter();
        vector<Props*> prop;
    protected:
        Map* map;
        MapData** mapData;                          //Ū���a�ϸ�T
    private:
        int dx, dy;					                // �H���a�Ϯy��
        bool Bankruptcy;                            // �O�_�}��
        int now;                                    // �ثe�Ҧb��m
        int remaining;                              // �Ѿl�B��
        int stop;                                   // ����^�X��
        //   �H�U���H���]��
        int money;                                  // �֦����B
        int estate;                                 // �Цa���ƶq

        //  �H�U���ʵe����
        int w, h;                                   // �Ϥ��e�שM����
        CMovingBitmap bmp[10][5];			        // �H���Ϥ�
        CMovingBitmap bmpInjury;                    // �H�����˪��Ϥ�
        CMovingBitmap playerHead[4];                // ���a�Y��
        CMovingBitmap timeBombs;                    // �w�ɬ��u �H���Y�W���
        int direct;                                 // 2�U 6�k 8�W 4��
        int speed;                                  // ���ʳt��
        int type;                                   // �H������ 0�h��A�� 1�p�� 2�D�� 3�j�� 4�R��
        int order;                                  // ���a����
        int count;                                  // ��e
        int countmax;                               // �C�X��ONMOVE���U�@�i��
        int ani;                                    // ��e
        int animax;                                 // �`�@�ϼ�
        int fector;                                 // �Y��j�p
        bool isInjury;                              // �O�_����
        bool isHaveTimeBombs;                       // �O�_�֦����u
        int TimeBombsCounter;                       // �w�ɬ��u�˼ƭp�ɾ�
        CMovingBitmap number[2][10];                    // �w�ɬ��u�˼�
    };
}
