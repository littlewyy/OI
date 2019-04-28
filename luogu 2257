#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 1E7 + 5;
int T;
int Miu[MAXN],Prime[MAXN / 10];
LL S[MAXN];
bool Vis[MAXN];
void Sift()
{
	int p = 0;
	Miu[1] = 1 , S[1] = 0 , Vis[1] = 1;
	for(int i = 2 ; i <= 1e7 ; i ++)
	{
		if(!Vis[i])	Miu[i] = -1 , S[i] = 1 , Prime[++ p] = i;
		for(int j = 1 ; j <= p ; j ++)
		{
			LL tar = i * LL(Prime[j]);
			if(tar > 1e7)	break;
			Vis[tar] = 1;
			if(i % Prime[j])	Miu[tar] = - Miu[i] , S[tar] = Miu[i] - S[i];
			else	{Miu[tar] = 0 , S[tar] = Miu[i]; break;}
		}
	}
	for(int i = 1 ; i <= 1e7 ; i ++)
		S[i] += S[i - 1];
}
void Query()
{
	scanf("%d",&T);
	while(T --)
	{
		LL ans = 0;int n,m;
		scanf("%d%d",&n,&m);
		if(n > m)	swap(n,m);
		for(int t = 1 , end ; t <= n ; t = end + 1)
		{
			end = min(n / (n / t) , m / (m / t));
			ans += LL(n / t) * (m / t) * (S[end] - S[t - 1]);
		}
		printf("%lld\n",ans);
	}
}
int main()
{
	freopen("luogu 2257.in","r",stdin);
	freopen("luogu 2257.out","w",stdout);
	Sift();
	Query();
	return 0;
}
