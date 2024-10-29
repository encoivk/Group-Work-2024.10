#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> side(100);
vector<bool>sideVisited(100,{false});
vector<int>sideSum(100);
vector<int>pointNum(101);
int maxSum=0;//最大光照
int tempSum=0;
int usableNum;//可用边数
int N;
void start() {     //求出每条路径的光照
    for(int i=1;i<N;i++) {
        int sum=pointNum[side[i][0]]*pointNum[side[i][1]];
        sideSum[i]=sum;
    }
}
void backtrack() {
    for(int i=1;i<N;i++) {
        if(usableNum==0) {
            maxSum=max(tempSum,maxSum);
            return;
        }
        if(sideVisited[i]==false) {
            vector<int> temp;
            for(int j=1;j<N;j++) {
                if(((side[j][0]==side[i][0])||(side[j][1]==side[i][1])
                    ||(side[j][1]==side[i][0])||(side[j][0]==side[i][1]))
                    &&sideVisited[j]==false
                    ) {
                    sideVisited[j]=true;
                    temp.push_back(j);
                    usableNum--;
                }
            }
            tempSum+=sideSum[i];
            backtrack();
            tempSum-=sideSum[i];
            for(auto it=temp.begin();it!=temp.end();it++) {
                sideVisited[*it]=false;
                usableNum++;
            }
        }
    }

}
int main() {
    cin>>N;
    usableNum=N-1;
    for (int i = 1; i < N; ++i) {
        int pointA,pointB;
        cin>>pointA>>pointB;
        side[i].push_back(pointA);
        side[i].push_back(pointB);
    }
    for(int i=1;i<=N;i++) {
        int num;
        cin>>num;
        pointNum[i]=num;
    }
    start();
    backtrack();
    cout<<maxSum<<endl;

}