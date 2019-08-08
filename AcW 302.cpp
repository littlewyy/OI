#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 3E5 + 5;
int n,s,head,tail;
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
int Dich(int cur)
{
	int lo = head , hi = tail + 1;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(cur * (SumC[Q[mid]] - SumC[Q[mid - 1]]) > f[Q[mid]] - f[Q[mid - 1]])	lo = mid;//可取。
		else	hi = mid;		
	}
	return Q[lo];
}
void Dp()
{
	head = 1 , tail = 1;
	Q[1] = 0 , f[0] = 0;//边界 
	for(int i = 1 ; i <= n ; i ++)
	{
		int temp = SumT[i] + s;
		int pos = Dich(temp);
		f[i] = SumT[i] * SumC[i] + s * SumC[n] + f[pos] - temp * SumC[pos];
		while(head < tail && (f[Q[tail]] - f[Q[tail - 1]]) * (SumC[i] - SumC[Q[tail]]) >= (f[i] - f[Q[tail]]) * (SumC[Q[tail]] - SumC[Q[tail - 1]]))	
			tail --;
		Q[++ tail] = i;
	}
	printf("%lld\n",f[n]);
}
int main()
{
	freopen("AcW 302.in","r",stdin);
	freopen("AcW 302.out","w",stdout);
	Read();
	Dp();
	return 0;
}
//目前，t(i) > (F[j2] - F[j1]) / (SumC[j2] - SumC[j1]) , 则j2优于j1。
//大于号：维护下凸壳   t(i)递增：从队首找。   
