#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 1E3 + 5;
int T,n,m;
int Height[MAXN][MAXN],Lef[MAXN],Rig[MAXN],Stack[MAXN];
char S[MAXN][MAXN];
void Read()
{
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i ++)	
		for(int j = 1 ; j <= m ; j ++)	
			cin >> S[i][j];
}
void Init()
{
	memset(Height,0,sizeof(Height));
	for(int j = 1 ; j <= m ; j ++)
	{
		for(int i = 1 ; i <= m ; i ++)
		{
			if(S[i][j] == 'F')
				Height[i][j] = Height[i - 1][j] + 1;
			//printf("%d ",Height[i][j]);
		}
		//printf("\n");
	}
}
void Calc()
{
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int first,Stop;
		for(int j = 1 ; j <= m; j ++)	
		{
			if(S[i][j] == 'R')	continue;
			if(S[i][j - 1] != 'F')	
			{
				Stop = 1 ,  Stack[1] = j;
				Lef[j] = j , first = j;
			}
			else	
			{
				while(Stop > 0 && Height[i][Stack[Stop]] >= Height[i][j])	Stop --;
				if(Stop)	Lef[j] = Stack[Stop] + 1; 
				else	Lef[j] = first;
				Stack[++ Stop] = j;
			}
		}
		for(int j = m ; j >= 1 ; j --)
		{
			if(S[i][j] == 'R')	continue;
			if(S[i][j + 1] != 'F')
			{
				Stop = 1 , Stack[1] = j;
				Rig[j] = j , first = j;
			}
			else
			{
				while(Stop > 0 && Height[i][Stack[Stop]] >= Height[i][j])	Stop --;
				if(Stop)	Rig[j] = Stack[Stop] - 1;
				else	Rig[j] = first;
				Stack[++ Stop] = j;
			}
		}
		for(int j = 1 ; j <= m ; j ++)
		{
			if(S[i][j] == 'F')
				ans = max(ans,Height[i][j] * (Rig[j] - Lef[j] + 1));
		}
	}
	cout << ans * 3 << endl;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	while(T --)
	{
		Read();
		Init();
		Calc();
	}
	return 0;
}
