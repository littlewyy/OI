#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
int n,g,dfn,Stop,cur = -1;
int T[MAXN][2],Head[MAXN],D[MAXN],Bel[MAXN];
int Dfn[MAXN],Low[MAXN],Stack[MAXN],Res[MAXN];
bool Instack[MAXN];
struct wyy
{
	int to,next;
}Edge[MAXN * MAXN];
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
}
bool Check(int x,int s1,int y,int s2)//若会相交，return false; 
{
	int l1,r1,l2,r2;
	if(s1 == 0)	l1 = T[x][0] , r1 = l1 + D[x];
	else	l1 = T[x][1] - D[x] , r1 = T[x][1];
	if(s2 == 0)	l2 = T[y][0] , r2 = l2 + D[y];
	else	l2 = T[y][1] - D[y] , r2 = T[y][1];
	if(l2 >= r1)	return true;
	if(r2 <= l1)	return true;
	return false;
}
void Read()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
	{
		string s[2];
		cin >> s[0] >> s[1] >> D[i];
		T[i][0] = (s[0][0] - '0') * 600 + (s[0][1] - '0') * 60 + (s[0][3] - '0') * 10 + (s[0][4] - '0');
		T[i][1] = (s[1][0] - '0') * 600 + (s[1][1] - '0') * 60 + (s[1][3] - '0') * 10 + (s[1][4] - '0');
		//printf("%d %d\n",T[i][0],T[i][1]);
	}
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		{
			if(i == j)	continue;
			if(!Check(i,0,j,0))	Add(i,j + n);//这两个不能同时存在，则a -> 反b。b -> 反a 
			if(!Check(i,0,j,1))	Add(i,j);
			if(!Check(i,1,j,0))	Add(i + n,j + n);
			if(!Check(i,1,j,1))	Add(i + n,j);
		}
	}
/*	for(int i = 1 ; i <= 2 * n ; i ++)
	{
		printf("%d : ",i);
		for(int h = Head[i] ; h != -1 ; h = Edge[h].next)
			printf("%d ",Edge[h].to);
		printf("\n");
	}*/
}
void Tarjan(int x)
{
	Dfn[x] = Low[x] = ++ dfn;
	Instack[x] = 1 , Stack[++ Stop] = x;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(!Dfn[y])
		{
			Tarjan(y);
			Low[x] = min(Low[x],Low[y]);
		}
		else
		{
			if(Instack[y])	
				Low[x] = min(Low[x],Dfn[y]);
		}
	}
	if(Dfn[x] == Low[x])
	{
		g ++;
		while(1)
		{
			int temp = Stack[Stop --];
			Instack[temp] = 0 , Bel[temp] = g;
			if(temp == x)	break;			
		}
	}
}
void Calc()
{
	for(int i = 1 ; i <= 2 * n ; i ++)	
		if(!Dfn[i])
			Tarjan(i);
//	for(int i = 1 ; i <= 2 * n ; i ++)	printf("%d ",Bel[i]);
//	printf("\n");
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Bel[i] == Bel[i + n])	
		{
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
	for(int i = 1 ; i <= n ; i ++)
	{
		//i所在的联通块拓扑序更小 
		if(Bel[i] < Bel[i + n])	Res[i] = 0 , Res[i + n] = 1;
		else	Res[i + n] = 0 , Res[i] = 1;
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		int s,t;
		if(Res[i] == 0)	s = T[i][0] , t = T[i][0] + D[i];
		else	s = T[i][1] - D[i] , t = T[i][1];
		int h1 = s / 60 , m1 = s % 60 , h2 = t / 60 , m2 = t % 60;
		printf("%d%d:%d%d ",h1 / 10,h1 % 10,m1 / 10,m1 % 10);
		printf("%d%d:%d%d\n",h2 / 10,h2 % 10,m2 / 10,m2 % 10);
	}
}
int main()
{
	freopen("AcW 371.in","r",stdin);
	freopen("AcW 371.out","w",stdout);
	Read();
	Calc();
	return 0; 
}
