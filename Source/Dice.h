namespace game_framework {
    class Dice
    {
    public:
        Dice();
        void Initialize();				// 設定擦子為初始值
        void LoadBitmap();				// 載入圖形
        void OnRoll();					// 擲骰子
        void OnShow();					// 將擦子圖形貼到畫面
        void SetStartRoll(bool flag);	    // 設定是否開始骰
        void SetXY(int nx, int ny);		// 設定擦子左上角座標
    protected:
        CAnimation animation;		// 擦子的動畫
        int x, y;					// 擦子左上角座標
        bool isStartRoll;			// 是否正開始骰
    };
}
