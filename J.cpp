//	//	//J
#include <iostream>
using namespace std;
#include <vector>
static int mod = 1e9 + 7;
int gys(int a, int b) {//最大公约数
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
bool areCoprime(int a, int b) {//是否互质
    return gys(a, b) == 1;
}
int countCoprimePairs(int n, vector<int>& a) {
    int pos = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            if (i != j && areCoprime(i, j)) pos++;
    }
    int num = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && a[i - 1] != 0 && a[j - 1] != 0 && areCoprime(a[i - 1], a[j - 1]))
                num++;
        }
    }
    num = num > 1 ? num : 1;
    return (num * pos) % mod;
}
int main() {
    int T;
    cin >> T; //数据组数
    while (T--) {
        int n;
        cin >> n; //槽位数量
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i]; //新能源量
        int result = countCoprimePairs(n, a);
        cout << result << endl; // 输出结果
    }
}