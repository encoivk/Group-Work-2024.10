//
// Created by XXS on 2024/10/18.
//

#include<iostream>
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
        vector<int> tempList;
        for(int j=1;j<=n-i;j++)
        {
            cin>>tempList[j];
        }
        numList.push_back(tempList);
    }
    unordered_map<int,int> map;//每条道路经过的人数
    for(int i=1;i<=n-1;i++)
    {
        map.insert(i,0);
    }
    for(int i=1;i<=numList.size();i++)
    {
        vector<int> temp=numList[i];
        for(int j=1;j<=temp.size();j++)
        {
            for(int p=j;p>=1;p--)
            {
                map[p]+=temp[j];
            }
        }
    }
    int left=1,right=left+k-1,maxNum=0;
    for(int i=1;i<=right;i++)
    {
        maxNum+=
    }

}