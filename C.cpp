#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double func1(double x, double a);
double func2(double x, double b);
double sum_of_functions(double x, double a, double b);
int main() {
    double a, b;
    cin >> a >> b;
    // 设置x的搜索范围和步长
    double x_min = -100.0;
    double x_max = 100.0;
    double step = 0.01;
    // 寻找最小值
    double min_x = x_min;
    double min_sum = sum_of_functions(x_min, a, b);
    for (double x = x_min; x <= x_max; x += step) {
        double current_sum = sum_of_functions(x, a, b);
        if (current_sum < min_sum) {//若新的最小和小于记录的最小和，则更新最小和
            min_sum = current_sum;
            min_x = x;
        }
    }
    cout <<fixed << setprecision(6) << min_sum << endl;
    return 0;
}
double func1(double x, double a) {
    return sqrt(x * x + a);
}
double func2(double x, double b) {
    return sqrt((b - x) * (b - x) + 1);
}
double sum_of_functions(double x, double a, double b) {
    return func1(x, a) + func2(x, b);
}