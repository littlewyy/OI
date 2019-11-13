#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 55 , MAXL = 30;
const LL mod = 990804011;
char S[MAXN][MAXL];
int n,maxlen;
int Len[MAXN],A[MAXN][MAXL];
LL f[MAXL][MAXN][MAXN][MAXL];
void Read()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%s",S[i] + 1);
		Len[i] = strlen(S[i] + 1);
		maxlen = max(maxlen,Len[i]);
		for(int j = 1 ; j <= Len[i] ; j ++)
		{
			if(S[i][j] == '?')	A[i][j] = -1;
			else	A[i][j] = S[i][j] - 'a' + 1;
		}
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = Len[i] + 1 ; j <= maxlen ; j ++)	
			A[i][j] = 0;
	}
	memset(f,-1,sizeof(f));
}
LL Dp(int x,int l,int r,int end)
{
	if(l > r)	return 1;	
	if(end < 0)	return 0;	
	if(x == maxlen + 1)	return l == r;	
	if(f[x][l][r][end] != -1)	return f[x][l][r][end];
	f[x][l][r][end] = Dp(x,l,r,end - 1);
	for(int i = r ; i >= l ; i --)
	{
		if((A[i][x] != -1 && A[i][x] != end) || (A[i][x] == -1 && end == 0))	break;
		f[x][l][r][end] = (f[x][l][r][end] + Dp(x,l,i - 1,end - 1) * Dp(x + 1,i,r,26) % mod) % mod;
	}
	return f[x][l][r][end];
}
int main()
{
	freopen("2974.in","r",stdin);
	freopen("2974.out","w",stdout);
	Read();
	printf("%lld\n",Dp(1,1,n,26));
	return 0;
}
