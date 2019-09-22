#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 105 , MAXL = 1E4 + 5 , MAXM = 1E6 + 5;
int n,m;
int p[4] = {10067,10133,10267,10607};
int A[4][MAXN],Num[4][MAXN];
char S[MAXN][MAXL];
bool Vis[MAXM];
void read(int i)
{
	scanf("%s",S[i] + 1);
	int len = strlen(S[i] + 1);
	for(int t = 0 ; t < 4 ; t ++)
	{
		int w = 0 , sym = 1;
		for(int j = 1 ; j <= len ; j ++)
		{
			if(S[i][j] == '-')	sym = -1;
			else	w = (w * 10 % p[t] + S[i][j] - '0') % p[t];
		}
		if(sym == -1)	w = p[t] - w;
		A[t][i] = w;
	}
}
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i = 0 ; i <= n ; i ++)
		read(i);
}
LL CalcNum(int t,int x)
{
	LL ans = 0;
	for(int i = n ; i >= 0 ; i --)	
		ans = (ans * x % p[t] + A[t][i]) % p[t];
	return ans;
}
void Init()
{
	memset(Vis,0,sizeof(Vis));
	for(int t = 0 ; t < 4 ; t ++)
	{
		for(int i = 1 ; i <= p[t] ; i ++)
		{
			Num[t][i] = CalcNum(t,i);
			if(Num[t][i])
			{
				Vis[i] = 1;
				for(int j = 1 ; i + p[t] * j <= m ; j ++)	
					Vis[i + p[t] * j] = 1;
			}
		}
	}
}
void Calc()
{
	int ans = 0;
	for(int i = 1 ; i <= m ; i ++)	if(!Vis[i])	ans ++;
	printf("%d\n",ans);
	for(int i = 1 ; i <= m ; i ++)	if(!Vis[i])	printf("%d\n",i);
}
int main()
{
	freopen("luogu 2312.in","r",stdin);
	freopen("luogu 2312.out","w",stdout);
	Read();
	Init();
	Calc();
	return 0;
}
