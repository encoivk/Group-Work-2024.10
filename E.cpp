#include<iostream>
#include<vector>
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
    int count=1;
    int startA=A,startB=B;
    A=dirX[A];
    B=dirX[B];
    int preA=startA;
    int preB=startB;
    while(true) {
        if((startA==A&&startB==B)||(A==preA&&B==preB)||(A==B))break;
        if(crossType[A]!=crossType[B]) {
            result.push_back(to_string(count));
            return;
        }
        preA=A;
        preB=B;
        A=dirX[A];
        B=dirX[B];
        count++;
    }
    count=1;
    A=dirY[startA];
    B=dirY[startB];
    preA=startA;
    preB=startB;
    while(true) {
        if((startA==A&&startB==B)||(A==preA&&B==preB)||(A==B))break;
        if(crossType[A]!=crossType[B]) {
            result.push_back(count+"");
            return;
        }
        preA=A;
        preB=B;
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