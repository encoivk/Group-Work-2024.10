//
// Created by XXS on 2024/10/24.
//
#include <iostream>
#include <vector>
using namespace std;

//B
bool isEco(long n) {
    // 遍历所有可能的x*y=n
    for (long x = 1; x <= n; x++) {
        long y = n / x;
        if (x <= y) continue; // 重复
        if (x * y == n) {
            long a = (x + y) / 2;
            long b = (x - y) / 2;
            if (a * a - b * b == n && a > 0 && b > 0)return true;
        }
    }
    return false;
}
long EcoNum(long index) {
    long num=3;
    for (long count = 1; count < index;) {
        num++;
        if (isEco(num))count++;
    }
    return num;
}
int main() {
    vector<long> EcoNumberIndex;
    long n;
    cin >> n;
    for (long i=0;i<n;i++) {
        long index;
        cin >> index;
        EcoNumberIndex.push_back(index);
    }
    for (long index:EcoNumberIndex) {
        cout << EcoNum(index) << endl;
    }
}





