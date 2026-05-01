#include <iostream>
#include <vector>
#include <string>
#include <random> // 現代隨機數標頭檔
#include <ctime>   // 用於取得系統時間作為種子

using namespace std;

// 定義機率常數
const int CHANCE_SSR = 2;   // 2%
const int CHANCE_SR = 10;   // 10%

class GachaSystem {
private:
    int pityCounter = 0;     // 保底計數器
    const int MAX_PITY = 90; // 90 抽必中 SSR

    // 隨機數引擎與分佈器
    mt19937 gen; 
    uniform_int_distribution<int> dis; // 產生 1 到 100 之間的整數

public:
    GachaSystem() : dis(1, 100) {
        // 修正後的種子設定：使用 static_cast<unsigned int> 進行型別轉換
        gen.seed(static_cast<unsigned int>(time(0)));
    }

    string draw() {
        pityCounter++;
        
        // 1. 先判定是否達到保底觸發條件
        if (pityCounter >= MAX_PITY) {
            pityCounter = 0; 
            return "【SSR】(觸發 90 抽保底！)";
        }

        // 2. 產生 1-100 的隨機數
        int result = dis(gen);

        // 3. 根據區間判定結果
        if (result <= CHANCE_SSR) {
            pityCounter = 0; // 抽中 SSR，重置計數器
            return "【SSR】";
        } 
        else if (result <= (CHANCE_SSR + CHANCE_SR)) {
            // 落在 3 ~ 12 之間，機率為 10%
            return "【SR】";
        } 
        else {
            // 落在 13 ~ 100 之間，機率為 88%
            return "【R】";
        }
    }

    int getPityCount() { return pityCounter; }
};

int main() {
    GachaSystem myGacha;
    int choice;

    cout << "========================================" << endl;
    cout << "              抽卡模擬系統              " << endl;
    cout << "   機率設定：SSR 2%, SR 10%, R 88%      " << endl;
    cout << "   保底機制：90 抽必中 SSR              " << endl;
    cout << "========================================" << endl;

    while (true) {
        cout << "\n[ 目前保底累積：" << myGacha.getPityCount() << " / 90 ]" << endl;
        cout << "請選擇動作 (1:單抽, 2:十連抽, 0:結束): ";
        
        if (!(cin >> choice)) break; // 防止輸入非數字導致無窮迴圈

        if (choice == 0) break;

        if (choice == 1) {
            cout << ">>> 結果: " << myGacha.draw() << endl;
        } 
        else if (choice == 2) {
            cout << ">>> 十連抽結果如下：" << endl;
            for (int i = 0; i < 10; i++) {
                cout << "   (" << i + 1 << ") " << myGacha.draw() << endl;
            }
        }
    }

    cout << "模擬結束，祝你下次抽卡歐氣滿滿！" << endl;
    return 0;
}