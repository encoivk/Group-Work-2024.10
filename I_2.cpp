#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;
// 烧杯结构体，用于表示每个烧杯的状态
struct Beaker
{
    int index;  // 烧杯编号
    int alpha;  // 烧杯中物质α的量
    int energy; // 发生成功后可以得到的新能源量
    int beta;   // 烧杯中物质β的量（初始化为0）
    // 计算添加一个物质β时的边际收益
    double getMarginalGain() const
    {
        if (beta >= alpha)
            return 0;
        return (double)energy * alpha / ((alpha + beta) * (alpha + beta + 1));
    }
    // 调用运算符，用于优先队列的比较清单顺序
    bool operator<(const Beaker& other) const
    {
        return getMarginalGain() < other.getMarginalGain();
    }
};
int main()
{
    ios::sync_with_stdio(false); // 关闭标准输入输出的同步以加快输入输出速度
    cin.tie(nullptr);            // 离开输入流和输出流的绑定
    int n, t, q;
    cin >> n >> t >> q; // 输入烧杯数量n，物质β的总量t，物质α的变动次数q
    vector<int> p(n), l(n);
    vector<Beaker> beakers(n);
    // 输入烧杯可以得到的新能源量 p[i]
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i];
    }
    // 输入烧杯中物质α的量 l[i]，并初始化烧杯
    for (int i = 0; i < n; ++i)
    {
        cin >> l[i];
        beakers[i] = { i, l[i], p[i], 0 };
    }
    // 读变化的操作，用于这个q次操作
    vector<pair<int, int>> changes(q);
    for (int i = 0; i < q; ++i)
    {
        cin >> changes[i].first >> changes[i].second;
        --changes[i].second; // 将烧杯编号转换为0基类索引
    }
    // 处理每个变化，并输出应当的期望值
    for (int i = 0; i < q; ++i)
    {
        int type = changes[i].first;
        int r = changes[i].second;
        // 调整物质α的量
        if (type == 1)
        {
            ++beakers[r].alpha; // 增加一毫升物质α
        }
        else
        {
            --beakers[r].alpha; // 减少一毫升物质α
            // 确保物质β不超过物质α
            if (beakers[r].beta > beakers[r].alpha)
            {
                beakers[r].beta = beakers[r].alpha;
            }
        }
        // 重置物质β的分配，为重新分配作准备
        for (int j = 0; j < n; ++j)
        {
            beakers[j].beta = 0;
        }
        // 分配物质β并计算期望值
        priority_queue<Beaker> pq;
        for (int j = 0; j < n; ++j)
        {
            if (beakers[j].beta < beakers[j].alpha)
                pq.push(beakers[j]);
        }
        int remainingBeta = t;
        double expectedValue = 0.0;
        while (remainingBeta > 0 && !pq.empty())
        {
            Beaker top = pq.top();
            pq.pop();
            double marginalGain = top.getMarginalGain(); // 计算添加一毫升物质β的边际收益
            expectedValue += marginalGain;               // 更新期望值
            ++top.beta;                                  // 增加物质β
            beakers[top.index].beta = top.beta;          // 更新并保存烧杯中的物质β
            if (top.beta < top.alpha)
            {
                pq.push(top); // 如果物质β仍小于物质α，再次将烧杯放入优先队列
            }
            --remainingBeta;
        }
        // 输出当前变化后的期望值
        cout << fixed << setprecision(9) << expectedValue << "\n";
    }
    return 0;
}
