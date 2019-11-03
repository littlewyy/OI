#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
const int MAXN=55;
int g,n,cur=-1;
int P[MAXN],Head[MAXN],Vis[MAXN];
char Clue[MAXN][MAXN];
void Init()
{
	cur=-1;
	memset(Head,-1,sizeof(Head));
	memset(Clue,0,sizeof(Clue));
}
struct wyy
{
	int to,next;
}Edge[MAXN*MAXN];
void Add(int from,int to)
{
	Edge[++cur].to=to;
	Edge[cur].next=Head[from];
	Head[from]=cur;
}
void Read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&P[i]);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",Clue[i]+1);
		for(int j=1;j<=n;j++)
		{
			if(i==j)	continue;
			if(Clue[i][j]=='Y')	Add(j,i);
		}
	}
}
double DFS(int x)
{
	double nowAns=(100.0-P[x])/100.0;
	Vis[x]=1;
	for(int h=Head[x];h!=-1;h=Edge[h].next)
	{
		int y=Edge[h].to;
		if(Vis[y])	continue;
		nowAns=nowAns*DFS(y);
	}
	return nowAns;
}
void Calc()
{
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		memset(Vis,0,sizeof(Vis));
		double notC=DFS(i);
		//printf("%f\n",notC);
		ans=ans+1-notC;
	}
	printf("%.5lf\n",ans);
}
int main()
{
	freopen("2823.in","r",stdin);
	freopen("2823.out","w",stdout);
	scanf("%d",&g);
	while(g--)
	{
		Init();
		Read();//¶ÁÈë£¬½¨Í¼ 
		Calc();
	}
	return 0;
}
