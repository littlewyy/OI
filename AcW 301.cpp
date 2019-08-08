#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 3E5 + 5;
int n,s;
int T[MAXN],C[MAXN],Q[MAXN];
LL SumT[MAXN],SumC[MAXN],f[MAXN];
void Read()
{
	scanf("%d%d",&n,&s);
	SumT[0] = SumC[0] = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d%d",&T[i],&C[i]);
		SumT[i] = SumT[i - 1] + T[i];
		SumC[i] = SumC[i - 1] + C[i];
	}
}
void Dp()
{
	int head = 1 , tail = 1;
	Q[1] = 0 , f[0] = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		f[i] = SumT[i] * SumC[i] + s * SumC[n];
		int temp = SumT[i] + s;
		while(head < tail && temp * (SumC[Q[head + 1]] - SumC[Q[head]]) > f[Q[head + 1]] - f[Q[head]])	
			head ++;
		f[i] += f[Q[head]] - temp * SumC[Q[head]];//边界无论如何要设好，否则head = 1 , i = 1时，会重复计数f[1]. 
		//维护斜率递增的上凸壳 
		while(head < tail && (f[Q[tail]] - f[Q[tail - 1]]) * (SumC[i] - SumC[Q[tail]]) >= (f[i] - f[Q[tail]]) * (SumC[Q[tail]] - SumC[Q[tail - 1]]))	
			tail --;
		Q[++ tail] = i;
	}
	printf("%lld\n",f[n]);
}
int main()
{
	freopen("AcW 301.in","r",stdin);
	freopen("AcW 301.out","w",stdout);
	Read();
	Dp();
	return 0;
}
//目前，t(i) > (F[j2] - F[j1]) / (SumC[j2] - SumC[j1]) , 则j2优于j1。
//大于号：维护下凸壳   t(i)递增：从队首找。   
