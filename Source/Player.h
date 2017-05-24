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
        void LoadBitmap();							// 載入圖形
        void OnMove();			                    // 移動
        void OnShow(int sx, int sy);				// 將圖形貼到畫面 
        int GetMapX();                              // 取得人物地圖座標 X
        int GetMapY();                              // 取得人物地圖座標 Y
        int GetSpeed();
        bool GetBankruptcy();
        void SetMap(Map* m);                        // 
        void SetRemaining(int r);
        void SetSpeed(int sp);
        void SetStop(int stop);
        int GetStop();
        int GetRemaining();
        int GetNow();
        int GetMoney();                             //獲得金錢
        int GetType();
        void AdjMoney(int amount);                  //增加或減少金錢                           
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
        MapData** mapData;                          //讀取地圖資訊
    private:
        int dx, dy;					                // 人物地圖座標
        bool Bankruptcy;                            // 是否破產
        int now;                                    // 目前所在位置
        int remaining;                              // 剩餘步數
        int stop;                                   // 停止回合數
        //   以下為人物財產
        int money;                                  // 擁有金額
        int estate;                                 // 房地產數量

        //  以下為動畫控制
        int w, h;                                   // 圖片寬度和高度
        CMovingBitmap bmp[10][5];			        // 人物圖片
        CMovingBitmap bmpInjury;                    // 人物受傷的圖片
        CMovingBitmap playerHead[4];                // 玩家頭像
        CMovingBitmap timeBombs;                    // 定時炸彈 人物頭上顯示
        int direct;                                 // 2下 6右 8上 4左
        int speed;                                  // 移動速度
        int type;                                   // 人物種類 0多拉A夢 1小夫 2胖虎 3大雄 4靜香
        int order;                                  // 玩家順序
        int count;                                  // 當前
        int countmax;                               // 每幾個ONMOVE換下一張圖
        int ani;                                    // 當前
        int animax;                                 // 總共圖數
        int fector;                                 // 縮放大小
        bool isInjury;                              // 是否受傷
        bool isHaveTimeBombs;                       // 是否擁有炸彈
        int TimeBombsCounter;                       // 定時炸彈倒數計時器
        CMovingBitmap number[2][10];                    // 定時炸彈倒數
    };
}
