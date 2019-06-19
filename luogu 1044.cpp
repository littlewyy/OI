#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 6E4 + 5;
int n,type;
LL f[2][MAXN];
int main()
{
	scanf("%d",&n);
	f[0][0] = 1;
	for(int i = 2 ; i <= n + 1; i ++)
	{
		type ^= 1;
		f[type][0] = 1;
		for(int j = 1 ; j <= i - 1 ; j ++)
			f[type][j] = f[type][j - 1] + f[type ^ 1][j];
	}
	printf("%lld\n",f[type][n]);
	return 0;
}
