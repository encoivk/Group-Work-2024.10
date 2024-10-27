#include<iostream>
using namespace std;
int main()
{
	float N, K;
	long M;
	cin >> N>>M>>K ;
	int years = 0;
	while (N >= M)
	{
		years++;
		N = N*(1 - K/100);
	}
	cout << years;
}
