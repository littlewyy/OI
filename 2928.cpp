#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
int T,n,p,used;
int Stack[MAXN],Cnt[MAXN],Vis[MAXN],f[MAXN][MAXN];
char S[MAXN],Str[MAXN],Temp[MAXN];
void Read()
{
	scanf("%s",S + 1);
	n = strlen(S + 1);
}
void Init()
{
	memset(Cnt,0,sizeof(Cnt));
	used = 0;
	int last = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(S[i] != S[i + 1])
		{
			Str[++ used] = S[i];
			Cnt[used] = i - last;
			if(Cnt[used] > 2)	while(1);
			last = i;
		}
	}
}
void Dp(int Case)
{
	memset(f,0x3f,sizeof(f));
	n = used;	
	for(int i = 1 ; i <= n ; i ++)	f[i][i] = max(3 - Cnt[i],0);
	for(int l = 2 ; l <= n ; l ++)
	{
		for(int i = 1 ; i + l - 1 <= n ; i ++)
		{
			int j = i + l - 1;
			if(Str[i] == Str[j])	
			{
				f[i][j] = min(f[i][j],f[i + 1][j - 1] + max(3 - Cnt[i] - Cnt[j],0));
				for(int k = i + 2 ; k < j ; k += 2)
					if(Str[k] == Str[i] && Cnt[k] == 1 && Cnt[i] + Cnt[j] <= 3)
						f[i][j] = min(f[i][j],f[i + 1][k - 1] + f[k + 1][j - 1]);
			}			
			for(int k = i ; k < j ; k ++)	f[i][j] = min(f[i][j],f[i][k] + f[k + 1][j]);
		}
	}
	printf("Case #%d: %d\n",Case,f[1][n]);
}
int main()
{
	freopen("2928.in","r",stdin);
	freopen("2928.out","w",stdout);
	scanf("%d",&T);
	for(int i = 1 ; i <= T ; i ++)
	{
		Read();
		Init();
		Dp(i);
	}
	return 0;
}
