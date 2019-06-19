#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 5E4 + 5;
bool Vis[MAXN];
int T,n,m,p,k;
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
void Read()
{
	scanf("%d%d%d",&n,&m,&k);
	n /= k , m /= k;
	ans = 0;	
}
void Calc()
{
	int nn = min(n,m);
	for(int d = 1 , end ; d <= nn ; d = end + 1)
	{
		int st = d , end1 = n / (n / d) , end2 = m / (m / d);
		end = min(min(end1,end2),nn);
		ans += LL(Sum[end] - Sum[st - 1]) * (n / d) * (m / d);
	}
	printf("%lld\n",ans);
}
void Query()
{
	Read();
	Calc();
}
int main()
{
	freopen("luogu 3455.in","r",stdin);
	freopen("luogu 3455.out","w",stdout);
	GetMiu();
	scanf("%d",&T);
	while(T --)	Query();	
	return 0;
}
