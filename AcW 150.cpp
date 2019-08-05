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
	for(;;)
	{
		int ok = 0;
		for(int i = 1 ; i <= num ; i ++)
		{
			int pos = Q[i];
			while(Match(pos,Next[pos]))
			{
				ok = 1 , Vis[pos] = Vis[Next[pos]] = 1;//被删除 
				int temp = Pre[pos] , next = Next[Next[pos]];//改链表指针 
				Next[temp] = next , Pre[next] = temp;
				pos = temp;
			}
		}
		if(ok == 0)	break;//没了 
		num = 0;
		for(int i = 1 ; i <= n ; i ++)
		{
			if(!Vis[i] && Match(i,Next[i]))
				Q[++ num] = i;
		}
	}
	int ans = 0;
	for(int i = 0 ; i <= n ; i ++)
	{
		if(!Vis[i])	
			ans = max(ans,Next[i] - i - 1);
	}
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

