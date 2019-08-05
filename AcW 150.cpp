#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
const int MAXN = 1E5 + 5;
int n,num;
int Pre[MAXN],Next[MAXN],Vis[MAXN],Q[MAXN];
char S[MAXN];
bool Match(int x,int y)
{
	if(x < 1 || x > n || y < 1 || y > n)	return false;	
	if(S[x] == '(' && S[y] == ')')	return true;
	if(S[x] == '[' && S[y] == ']')	return true;
	if(S[x] == '{' && S[y] == '}')	return true;
	return false;
}
void Read()
{
	scanf("%s",S + 1);
	n = strlen(S + 1);
	for(int i = 1 ; i <= n ; i ++)	
	{
		if(Match(i,i + 1))	Q[++ num] = i;//匹配左端 
		Pre[i] = i - 1 , Next[i] = i + 1;
	}
}
void Calc()
{
	for(int i = 1 ; i <= num ; i ++)
	{
		int x = Q[i];
		while(Match(x,Next[x]))
		{
			int pre = Pre[x] , next = Next[Next[x]];
			Vis[x] = Vis[Next[x]] = 1;
			Next[pre] = next , Pre[next] = pre;
			x = pre;
		}
	}
	int ans = 0;
	for(int i = 0 ; i <= n ; i ++)
		if(Vis[i] == 0)	
			ans = max(ans,Next[i] - i - 1);
	printf("%d\n",ans);
}
int main()
{
	freopen("AcW 150.in","r",stdin);
	freopen("AcW 150.out","w",stdout);
	Read();
	Calc();
	return 0;
}
