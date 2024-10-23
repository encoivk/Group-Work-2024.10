//
// Created by XXS on 2024/10/18.
//

#include<iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
int main()
{
    vector<vector<int>>numList;
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n-1;i++)
    {
        vector<int> tempList(n-i);
        for(int j=1;j<=n-i;j++)
        {
            cin>>tempList[j];
            cout<<"hello"<<tempList[j]<<endl;
        }
        numList.push_back(tempList);
    }
    map<int,int> numMap;//每条道路经过的人数
    for(int i=1;i<=n-1;i++)
    {
        numMap.insert({i,0});
    }
    for(int i=1;i<=numList.size();i++)
    {
        vector<int> temp=numList[i];
        for(int j=1;j<=temp.size();j++)
        {
            for(int p=j;p>=1;p--)
            {
                numMap[p]+=temp[j];
            }
        }
    }
    int left=1,right=left+k-1,maxNum=0;
    for(int i=1;i<=right;i++)
    {
        maxNum+=numMap[i];
    }
    int tempNum=maxNum;
    while(true)
    {
        right++;
        if(numMap.find(right)==numMap.end())break;
        tempNum+=numMap[right];
        tempNum-=numMap[left];
        left++;
        maxNum=max(tempNum,maxNum);
    }
    cout<<maxNum<<endl;
}