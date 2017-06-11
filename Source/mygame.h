#pragma once
#include "Dice.h"
#include "Number.h"
#include "Player.h"
#include "Map.h"
#include "MapData.h"
#include "UI.h"
#include "SelectCharactor.h"
#define DELAY 40
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��

                                //AUDIO_DING,				// 0
		//AUDIO_LAKE,				// 1
		//AUDIO_NTUT,	            // 2
        AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT,	            // 2
        AUDIO_BGM,              // 3
        AUDIO_BOOMER,           // 4
        AUDIO_STOP,             // 5
        AUDIO_WALK,             // 6
        AUDIO_TICKING           // 7

    };
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
        ~CGameStateInit();
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnRButtonDown(UINT nFlags, CPoint point);
        void OnLButtonUp(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnMouseMove(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
        Button* startButton = nullptr;                  // ���s
        Button* helpButton = nullptr;               
		CMovingBitmap logo;								// csie��logo
        CMovingBitmap beginground;                      // ��l�e��
        CMovingBitmap selectcharactor;                  // �﨤��
        CMovingBitmap arrow;                            // �﨤�b�Y
        CMovingBitmap arrow1;
        CMovingBitmap arrow2;                           //�}�⭫�ƿ��~�b�Y
        CMovingBitmap helpInfo;
        int arrow_index[4] = {0,1,2,3};
        int ancor = 0;
        int acount = 0;
        bool showHelp = false;
        bool dump = false;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        Map* GetBitMap();
        Player **GetPlayer();
        int GetNowPlayer();
        int GetPlayerCount();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
        CMovingBitmap   explosion[8];
        Player *player[4];          // 4�Ӫ��a
        UI ui;                      // User Interface
        int playercount;
        int nowPlayer;              // ��e���a
        Map bigMap;                 // �a��
        int amount;                 // �I�ƩM
        bool canThrowDies;          
        bool isExplosion;
        int explosionCount;
        int delayCount = DELAY;     // ���� �H�K���a�s���ثe���A 
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}