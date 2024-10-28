#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

struct Beaker {
    int pi; // 合成后的量
    int li; // 杯内有的α量
    vector<double> expectations; // 存储所有可能的β分配情况下的期望值
};

// 计算单个烧杯在给定α量和β量下的期望值
double calculate_expectation(int pi, int li, int bi) {
    if (bi > li) return 0; // β的量不能超过α
    return (double)pi * bi / (li + bi);
}

// 将物质β分配到每个烧杯并计算期望值
void distribute_beta(vector<Beaker>& beakers, int beta) {
    int n = beakers.size();
    for (int i = 0; i < n; ++i) {
        for (int bi = 0; bi <= min(beakers[i].li, beta); ++bi) { // β的分配范围从0到烧杯α量和β总量的较小者
            beakers[i].expectations.push_back(calculate_expectation(beakers[i].pi, beakers[i].li, bi));
        }
    }
}

// 从所有可能的期望值中找到最大值
double find_max_expectation(vector<Beaker>& beakers, int beta) {
    int n = beakers.size();
    double max_exp = 0.0;
    for (int i = 0; i < pow(beta + 1, n); ++i) { // 对于每种β的分配方式
        int idx = i;
        double exp = 0.0;
        int remaining_beta = beta;
        for (int j = 0; j < n; ++j) {
            int bi = idx % (beta + 1);
            idx /= (beta + 1);
            if (bi <= remaining_beta && bi <= beakers[j].li) {
                exp += beakers[j].expectations[bi];
                remaining_beta -= bi;
            }
            else {
                exp = 0; // 如果β分配不合法，则期望值为0
                break;
            }
        }
        max_exp = max(max_exp, exp);
    }
    return max_exp;
}

int main() {
    int n, t, q;
    cin >> n >> t >> q;
    vector<Beaker> beakers(n);

    for (int i = 0; i < n; ++i) cin >> beakers[i].pi;
    for (int i = 0; i < n; ++i) cin >> beakers[i].li;

    // 分配物质β并计算期望值
    distribute_beta(beakers, t);
    // 找到最大期望值
    double max_expectation = find_max_expectation(beakers, t);
    cout << fixed << setprecision(9) << max_expectation << endl;

    // 对于每次物质α的变化，重新计算最大期望值
    for (int i = 0; i < q; ++i) {
        int tj, rj;
        cin >> tj >> rj;
        --rj; // 转换为基于0的索引

        // 更新物质α的量
        if (tj == 1) {
            beakers[rj].li++;
        }
        else {
            beakers[rj].li--;
        }

        // 重新计算期望值
        for (Beaker& beaker : beakers) beaker.expectations.clear();
        distribute_beta(beakers, t);
        max_expectation = find_max_expectation(beakers, t);
        cout << max_expectation << endl;
    }

    return 0;
}