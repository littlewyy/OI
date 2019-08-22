#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3E6 + 5;
int n,m,cur;
int Cnt[MAXN],Fa[MAXN],f[MAXN];
struct wyy
{
	int to,next;
}Edge[MAXN];
int read()
{
	char ch = getchar();
	int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++)	f[i] = read();
	for(int i = 1 ; i <= m ; i ++)
	{
		int tar = read();
		Cnt[tar] ++;
	} 
}
int findA(int x)
{
	if(x == Fa[x])	return x;
	return Fa[x] = findA(Fa[x]);
}
void Calc()
{
	for(int i = 1 ; i <= n ; i ++)	
	{
		if(Cnt[i])	Fa[i] = i;
		else	Fa[i] = f[i];
	}
	long long ans = 0;
	for(int i = n ; i >= 1 ; i --)
	{
		int root = findA(i);
		if(Cnt[root] > 0)
		{
			Cnt[root] --;
			ans += i;
			if(Cnt[root] == 0 && root > 0)	Fa[root] = f[root];	
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("2955.in","r",stdin);
	freopen("2955.out","w",stdout);
	Read();
	Calc();
	return 0;
}
