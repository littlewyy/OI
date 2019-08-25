#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXB = 105;
const LL mod = 1e9 + 7;
LL n;
LL f[MAXB][5];
int main()
{
	freopen("2958.in","r",stdin);
	freopen("2958.out","w",stdout);
	scanf("%lld",&n);
	f[1][0] = 1;
	for(int i = 1 ; i <= 63 ; i ++)
	{
		//转移到f[i+1]
		int tar = ((n & (1ll << (i - 1))) > 0) ? 1 : 0;
		for(int j = 0 ; j <= 1 ; j ++)//接受的进位数目 
		{
			for(int k = 0 ; k <= 2 ; k ++)//这位上取的数目 
			{
				int now = (j + k) % 2;
				if(now == tar)	
					f[i + 1][(j + k) / 2] = (f[i + 1][(j + k) / 2] + f[i][j]) % mod;
			}
		} 
	}
	printf("%lld\n",f[64][0]);
	return 0;
}
