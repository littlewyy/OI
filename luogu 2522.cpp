#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 5E4 + 5;
bool Vis[MAXN];
int T,a,b,c,d,k,p;
int Miu[MAXN],Prime[MAXN / 10],Sum[MAXN];
LL ans;
void GetMiu()
{
	Miu[1] = 1;
	for(int i = 2 ; i <= 5e4 ; i ++)
	{
		if(!Vis[i])	Prime[++ p] = i , Miu[i] = -1;
		for(int j = 1 ; j <= p ; j ++)
		{
			LL tar = LL(i) * Prime[j];
			if(tar > 5e4)	break;
			Vis[tar] = 1;
			if(i % Prime[j])	Miu[tar] = Miu[i] * Miu[Prime[j]];
			else	{Miu[tar] = 0;break;}
		}
	}
	for(int i = 1 ; i <= 5e4 ; i ++)	Sum[i] = Sum[i - 1] + Miu[i];
}
LL GetNum(int n,int m)
{
	n /= k , m /= k;
	int nn = min(n,m);	LL ans = 0;
	for(int d = 1 , end ; d <= nn ; d = end + 1)
	{
		int st = d , end1 = n / (n / d) , end2 = m / (m / d);
		end = min(min(end1,end2),nn);
		ans += LL(Sum[end] - Sum[st - 1]) * (n / d) * (m / d);
	}
	return ans;
}
void Query()
{
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
	printf("%lld\n",GetNum(b,d) - GetNum(a - 1 ,d) - GetNum(b,c - 1) + GetNum(a - 1 , c - 1));
}
int main()
{
	freopen("luogu 2522.in","r",stdin);
	freopen("luogu 2522.out","w",stdout);
	GetMiu();
	scanf("%d",&T);
	while(T --)	Query();	
	return 0;
}
