#pragma once
#include "Map.h"
namespace game_framework {
    class Player {
    public:
        Player();
        void LoadBitmap();							// ���J�ϧ�
       // void OnMove();			            // ����
        void OnShow(int sx, int sy);				// �N�ϧζK��e�� 
        int GetMapX();                              // ���o�H���a�Ϯy�� X
        int GetMapY();                              // ���o�H���a�Ϯy�� Y
        void SetPositionNum(int amount);            // �]�w�Ӧ��֥[�I��
        void SetState(int ns);                      // �]�w���A
        int GetState();
        void SetMap(Map* m);
        void Move(int n);
    protected:
        Map* map;
        CMovingBitmap bmp;			                // �H���Ϥ�
        int dx, dy;					                // �H���a�Ϯy��
    private:
        int prePositionNum;                         // �e�@����m�I��
        int positionNum;                            // ��m�I��
        int state;                                  // 0�H�����ʪ��A 1�H�����ʪ��A
    };
}
