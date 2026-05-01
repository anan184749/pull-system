#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <iomanip> // 用於控制輸出格式

using namespace std;

// 設定原始機率
const int CHANCE_SSR = 2;
const int CHANCE_SR = 10;

class GachaSystem {
private:
    int pityCounter = 0;
    const int MAX_PITY = 90;
    mt19937 gen;
    uniform_int_distribution<int> dis;

public:
    long long totalSSR = 0, totalSR = 0, totalR = 0, totalDraws = 0;

    GachaSystem() : dis(1, 100) {
        gen.seed(static_cast<unsigned int>(time(0)));
    }

    void draw() {
        totalDraws++;
        pityCounter++;
        int result = dis(gen);

        // 判定 logic: 保底優先於隨機
        if (pityCounter >= MAX_PITY || result <= CHANCE_SSR) {
            totalSSR++;
            pityCounter = 0; 
        } else if (result <= (CHANCE_SSR + CHANCE_SR)) {
            totalSR++;
        } else {
            totalR++;
        }
    }

    void resetStatistics() {
        totalSSR = totalSR = totalR = totalDraws = pityCounter = 0;
    }
};

int main() {
    GachaSystem myGacha;
    int choice;

    cout << "========================================" << endl;
    cout << "     大數據抽卡機率模擬器 (10連抽版)    " << endl;
    cout << "  原始設定: SSR 2%, SR 10%, 保底 90 抽  " << endl;
    cout << "========================================" << endl;

    while (true) {
        cout << "\n[1] 開始大量十連抽模擬" << endl;
        cout << "[0] 結束程式" << endl;
        cout << "請輸入選項: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            long long cycles;
            cout << "請輸入要模擬幾次「十連抽」？ ";
            cin >> cycles;

            if (cycles <= 0) {
                cout << "請輸入大於 0 的數字！" << endl;
                continue;
            }

            myGacha.resetStatistics();
            cout << "\n模擬計算中，請稍候..." << endl;

            // 執行 10 * cycles 次抽取
            for (long long i = 0; i < cycles * 10; i++) {
                myGacha.draw();
            }

            // 計算實際百分比
            double ssrRate = (double)myGacha.totalSSR / myGacha.totalDraws * 100;
            double srRate = (double)myGacha.totalSR / myGacha.totalDraws * 100;
            double rRate = (double)myGacha.totalR / myGacha.totalDraws * 100;

            cout << "----------------------------------------" << endl;
            cout << " 模擬完成！總共抽取了 " << myGacha.totalDraws << " 次" << endl;
            cout << "----------------------------------------" << endl;
            cout << " [SSR] 數量: " << setw(8) << myGacha.totalSSR << " | 實際機率: " << fixed << setprecision(3) << ssrRate << "%" << endl;
            cout << " [SR ] 數量: " << setw(8) << myGacha.totalSR  << " | 實際機率: " << fixed << setprecision(3) << srRate << "%" << endl;
            cout << " [R  ] 數量: " << setw(8) << myGacha.totalR   << " | 實際機率: " << fixed << setprecision(3) << rRate << "%" << endl;
            cout << "----------------------------------------" << endl;
            cout << "*註: 因為保底機制，SSR 實際機率會略高於理論值 2.000%*" << endl;
        } else {
            cout << "無效選項，請重新輸入。" << endl;
        }
    }

    cout << "程式已結束。" << endl;
    return 0;
}