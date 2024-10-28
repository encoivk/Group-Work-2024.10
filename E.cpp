#include<iostream>
#include<vector>
#include<set>
using namespace std;

vector<string> result;
vector<int> dirX;
vector<int> dirY;
vector<int> crossType;
void simulate(int A,int B) {
    if(crossType[A]!=crossType[B]) {
        result.push_back("0");
        return;
    }
    set<pair<int,int>>visitedPath;
    pair<int,int> crossPair(A,B);
    visitedPath.insert(crossPair);
    int count=1;
    int startA=A;
    int startB=B;
    A=dirX[A];
    B=dirX[B];
    while(true) {
        pair<int,int> tempPair(A,B);
        if((visitedPath.find(tempPair)!=visitedPath.end())||(A==B))break;
        if(crossType[A]!=crossType[B]) {
            result.push_back(to_string(count));
            return;
        }
        visitedPath.insert(tempPair);
        A=dirX[A];
        B=dirX[B];
        count++;
    }
    count=1;
    set<pair<int,int>>().swap(visitedPath);//清空经过的路口
    visitedPath.insert(crossPair);
    A=dirY[startA];
    B=dirY[startB];

    while(true) {
        pair<int,int> tempPair(A,B);
        if((visitedPath.find(tempPair)!=visitedPath.end())||(A==B))break;
        if(crossType[A]!=crossType[B]) {
            result.push_back(to_string(count));
            return;
        }
        visitedPath.insert(tempPair);
        A=dirY[A];
        B=dirY[B];
        count++;
    }
    result.push_back("GG");
}
int main() {
    int num,n,A,B;
    cin>>num;
    while(num--) {
        cin>>n>>A>>B;
        for(int i=0;i<n;i++) {
            int x,y,t;
            cin>>x>>y>>t;
            dirX.push_back(x);
            dirY.push_back(y);
            crossType.push_back(t);
        }
        simulate(A,B);
        vector<int>().swap(dirX);
        vector<int>().swap(dirY);
        vector<int>().swap(crossType);
    }
    for(auto it=result.begin();it!=result.end();it++) {
        cout<<*it<<endl;
    }
}