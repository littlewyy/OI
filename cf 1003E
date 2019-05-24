#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 4E5 + 5;
int n,d,k,cur,Stop;
int Dep[MAXN],Stack[MAXN],Turn[MAXN],X[MAXN],Y[MAXN],Degree[MAXN];
void Calc()
{
	for(int i = 1 ; i <= d + 1 ; i ++)	Dep[i] = i , Stack[++ Stop] = i , Turn[i] = i;
	for(int i = 1 ; i <= d ; i ++)	X[i] = i , Y[i] = i + 1;
	for(int i = 2 ; i <= d ; i ++)	Degree[i] = 2;
	Degree[1] = Degree[d + 1] = 1;
	cur = d + 1;//点数 
	while(Stop)
	{
		int x = Stack[Stop --];
		int dis1 = Dep[x] - 1 , dis2 = Dep[x] - Dep[Turn[x]] + d - Dep[Turn[x]] + 1;
		if(dis1 < d && dis2 < d)	
		{
			while(Degree[x] < k)
			{
				if(cur == n)	break;//遇到边界，无论如何立即退出。 
				int y = ++ cur;
				Dep[y] = Dep[x] + 1 , Turn[y] = Turn[x] , Stack[++ Stop] = y;
				X[cur - 1] = x , Y[cur - 1] = y; 
				Degree[x] ++ , Degree[y] = 1;
			}	
		}
		if(cur == n)	
		{
			printf("YES\n");
			for(int i = 1 ; i < cur ; i ++)	printf("%d %d\n",X[i],Y[i]);
			break;
		}
	}
	if(cur < n)	printf("NO\n");	
}
int main()
{
	freopen("zyc.in","r",stdin);
	freopen("zyc.out","w",stdout);
	scanf("%d%d%d",&n,&d,&k);
	if(d + 1 > n || (n > 2 && k < 2))	printf("NO\n");
	else	Calc();	
	return 0;
}
