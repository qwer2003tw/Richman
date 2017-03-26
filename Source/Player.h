#pragma once
#include "Map.h"
namespace game_framework {
    class Player {
    public:
        Player();
        Player(int t);
        void LoadBitmap();							// ���J�ϧ�
        void OnMove();			            // ����
        void OnShow(int sx, int sy);				// �N�ϧζK��e�� 
        int GetMapX();                              // ���o�H���a�Ϯy�� X
        int GetMapY();                              // ���o�H���a�Ϯy�� Y
        bool GetBankruptcy();
        void SetMap(Map* m);                        // 
        void SetRemaining(int r);
        int  GetRemaining();
    protected:
        Map* map;
    private:
        int dx, dy;					                // �H���a�Ϯy��
        bool Bankruptcy;                            //�O�_�}��
        int now;                                    // �ثe�Ҧb��m
        int remaining;                              //�Ѿl�B��
        //�H�U���ʵe����
        int w, h;//�Ϥ��e�שM����
        CMovingBitmap bmp[10][5];			    // �H���Ϥ�
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
