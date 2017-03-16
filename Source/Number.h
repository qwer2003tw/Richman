namespace game_framework {
    class Number
    {
    public:
        Number();
        void Initialize();				// 設定擦子為初始值
        void LoadBitmap();				// 載入圖形
        void OnShow(int value);					// 將擦子圖形貼到畫面
        void SetXY(int nx, int ny);		// 設定擦子左上角座標
    protected:
        CMovingBitmap digitbmp[10];
        int x, y;
    };
}

