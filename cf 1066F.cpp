#include<iostream>
#include<cstdio>
#include<deque>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
int cur = -1,n,Ori[MAXN],Head[MAXN];
int Lef[MAXN],Rig[MAXN];
LL f[MAXN][2];
struct wyy
{
	int x,y,c;
}A[MAXN];
struct gr
{
	int to,next;
}Group[MAXN];
void Add(int g,int to)
{
	Group[++ cur].to = to;
	Group[cur].next = Head[g];
	Head[g] = cur;
}
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		A[i].x = read() , A[i].y = read();
		A[i].c = max(A[i].x,A[i].y);
		Ori[i] = A[i].c;
	}
	sort(Ori + 1 , Ori + 1 + n);
	//for(int i = 1 ; i <= n ; i ++)	printf("%d ",Ori[i]);
	
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)
	{
		int c = A[i].c;
		Add(lower_bound(Ori + 1 , Ori + 1 + n , c) - Ori , i);
	}
	
	for(int i = 1 ; i <= n ; i ++)	Lef[i] = Rig[i] = -1;
	for(int i = 1 ; i <= n ; i ++)//访问各组,得到其0 1距离 
	{
		for(int h = Head[i] ; h != -1 ; h = Group[h].next)
		{
			int to = Group[h].to;
		//	printf("%d %d\n",i,to);
			if(Lef[i] == -1)	Lef[i] = to;
			else	if(A[to].x < A[Lef[i]].x || (A[to].x == A[Lef[i]].x && A[to].y > A[Lef[i]].y))	Lef[i] = to;
			if(Rig[i] == -1)	Rig[i] = to;
			else	if(A[to].x > A[Rig[i]].x || (A[to].x == A[Rig[i]].x && A[to].y < A[Rig[i]].y))	Rig[i] = to;
		}
	}
}
int getDis(int a,int b)
{
	int x = A[a].x , y = A[a].y;
	int xx = A[b].x , yy = A[b].y;
	return abs(x - xx) + abs(y - yy);
}
void Calc()
{
	int last = 0;
	for(int i = 1 ; i <= n ; i ++)	
	{
		if(Head[i] == -1)	continue;
		int dis = getDis(Lef[i],Rig[i]);
		//在0结束（先到1，再到0) 
		if(last == 0)	
		{
			f[i][0] = dis + A[Rig[i]].x + A[Rig[i]].y;
			f[i][1] = dis + A[Lef[i]].x + A[Lef[i]].y;
		}
		else	
		{
			f[i][0] = dis + min(f[last][0] + getDis(Lef[last],Rig[i]),f[last][1] + getDis(Rig[last],Rig[i]));
			f[i][1] = dis + min(f[last][0] + getDis(Lef[last],Lef[i]),f[last][1] + getDis(Rig[last],Lef[i]));
		}		
		last = i;
	}
	printf("%I64d\n",min(f[last][0],f[last][1]));
}
int main()
{
	freopen("cf 1066F.in","r",stdin);
	freopen("cf 1066F.out","w",stdout);
	Read();
	Calc();
	return 0;
}
