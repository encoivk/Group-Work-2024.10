#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
struct point {
    double x, y, z;
};
double distance(const point& a, const point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
double closeline(const point& a, const point& b, const point& c, double r) {
    point ac = { c.x - a.x, c.y - a.y, c.z - a.z };
    point ab = { b.x - a.x, b.y - a.y, b.z - a.z };
    double dot_product = ac.x * ab.x + ac.y * ab.y + ac.z * ab.z;//计算点积判断夹角
    double mochang_ab = distance(a, b); // 计算ab的长度
    double touying_length = dot_product / mochang_ab; // 计算ac在ab上的投影长度

    point closest_point = { a.x + touying_length * (ab.x / mochang_ab),
                          a.y + touying_length * (ab.y / mochang_ab),
                          a.z + touying_length * (ab.z / mochang_ab) };

    if (distance(closest_point, c) < r) {
        // 如果在球内，返回球面上的点
        double distance_to_surface = sqrt(r * r - (touying_length * touying_length));//计算点到球面的距离
        return distance(a, closest_point) + distance_to_surface;
    }
    else {
        // 如果不在球内，返回直线距离
        return distance(a, b);
    }
}
int main() {
    point a, b, c;
    cin >> a.x >> a.y >> a.z;
    cin >> b.x >> b.y >> b.z;
    cin >> c.x >> c.y >> c.z;
    double r;
    cin >> r;
    double close_distance = closeline(a, b, c, r);
    cout << fixed << setprecision(2) << close_distance << endl;
    return 0;
}