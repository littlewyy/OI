#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005 , MAXK = 25;
int T,k;
int C[MAXN][MAXN],Sum[MAXN][MAXN];
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Init()
{
	T = read() , k = read();
	for(int i = 0 ; i < MAXN ; i ++)
	{
		for(int j = 0 ; j <= i ; j ++)
		{
			if(j == 0 || j == i)	C[i][j] = 1 % k;
			else	C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % k;
			if(C[i][j] == 0)	Sum[i][j] = 1;//模数为0的个数 
			if(j > 0)	Sum[i][j] += Sum[i][j - 1];
		}
	}
}
void Calc()
{
	Init();
	while(T --)//多组数据？预处理就好啦反正k一样 
	{
		int n = read() , m = read() , ans = 0;
		for(int i = 0 ; i <= n ; i ++)
		{
			int j = min(m,i);
			ans += Sum[i][j];
		}
		printf("%d\n",ans);
	}
}
int main()
{
	freopen("luogu 2822.in","r",stdin);
	freopen("luogu 2822.out","w",stdout);
	Calc();
	return 0;
}
