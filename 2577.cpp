#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
int n,q,stamp,cur = -1;
int Head[MAXN];
int Siz[MAXN],Fa[MAXN],Dep[MAXN],W[MAXN];
int Top[MAXN],Id[MAXN],Ori[MAXN];
LL Cost[2][MAXN],Sum[2][MAXN],Num[2][MAXN],Val[MAXN];
struct wyy
{
	int to,next;
}Edge[MAXN * 2];
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
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void Read()
{
	n = read() , q = read();
	for(int i = 1 ; i <= n ; i ++)	Val[i] = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		Add(x,y);
	}
}
void DFS1(int x,int fa)
{
	Siz[x] = 1 , Fa[x] = fa , Dep[x] = Dep[fa] + 1 , W[x] = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		DFS1(y,x);
		Siz[x] += Siz[y];//别忘了维护子树大小啊。不然弄不出轻重链。 
		if(Siz[y] > Siz[W[x]])	W[x] = y;		
	}
}
void DFS2(int x,int fa)
{
	Id[x] = ++ stamp , Ori[stamp] = x;
	if(W[x])	Top[W[x]] = Top[x] , DFS2(W[x],x);
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int	y = Edge[h].to;
		if(y == fa || y == W[x])	continue;
		Top[y] = y , DFS2(y,x);
	}
}
void Init()
{
//	for(int i = 1 ; i <= n ; i ++)	printf("%d ",Top[i]);
//	printf("\n");
//	for(int i = 1 ; i <= n ; i ++)	printf("%d ",Ori[i]);
//	printf("\n");
	int end;
	for(int st = 1 ; st <= n ; st = end + 1)
	{
		end = st;
		while(end < n && Top[Ori[end + 1]] == Top[Ori[st]])	end ++;
		//自下而上代价、点权和、下方点数 
		Cost[0][end] = Sum[0][end] = Val[Ori[end]] , Num[0][end] = 0;
		for(int i = end - 1; i >= st ; i --)
			Cost[0][i] = Cost[0][i + 1] + (end - i + 1) * Val[Ori[i]],
			Sum[0][i] = Sum[0][i + 1] + Val[Ori[i]],
			Num[0][i] = Num[0][i + 1] + 1;
		//自上而下代价、点权和、下方点数 
		Cost[1][st] = Sum[1][st] = Val[Ori[st]] , Num[1][st] = 0;
		for(int i = st + 1 ; i <= end ; i ++)//自上而下标号  
			Cost[1][i] = Cost[1][i - 1] + (i - st + 1) * Val[Ori[i]],
			Sum[1][i] = Sum[1][i - 1] + Val[Ori[i]],
			Num[1][i] = Num[1][i - 1] + 1;	
	} 
//	for(int i = 1 ; i <= n ; i ++)
//		printf("%d ",Cost[1][i]);
//	printf("\n");
}
LL getAns(int x,int y)
{
	LL ans1 = 0 , ans2 = 0;
	LL num1 = 0 , sum2 = 0;
	//printf("%d %d\n",Top[x],Top[y]);
	while(Top[x] != Top[y])
	{
		//printf("%d %d\n",x,y);
		//printf("%d %d\n",Dep[Top[x]],Dep[Top[y]]);
		if(Dep[Top[x]] > Dep[Top[y]])//跳s 
		{
			//计算当前段答案  
			int id = Id[x] , idT = Id[Top[x]] , idy = id + 1;
			LL curC = Cost[0][idT];
			if(Top[Ori[idy]] == Top[x])	curC -= Cost[0][idy];
			curC -= Sum[1][id] * Num[0][id];
			
			//跟下方的答案进行合并
			curC += num1 * Sum[1][id];
			ans1 += curC;
			num1 += Num[0][idT] - Num[0][id] + 1;
			
			x = Fa[Top[x]]; 
		}
		else	//跳t 
		{
			int id = Id[y] , idT = Id[Top[y]] , numC = Num[0][idT] - Num[0][id] + 1;
			LL curC = Cost[1][id];
			ans2 += curC;
			ans2 += numC * sum2;
			sum2 += Sum[1][id];
			y = Fa[Top[y]];
		}
	}
	//printf("%d %d\n",x,y);
	//printf("%d %d\n",Id[x],Id[y]);
	//printf("%lld %lld\n",ans1,ans2);
	//0:自下而上  1：自上而下 
	if(Id[x] < Id[y])
	{
		int idx = Id[x] , idy = Id[y] , idu = idx - 1;
		LL curC = Cost[1][idy] , sumC = Sum[1][idy] , numC = Num[1][idy] - Num[1][idx] + 1;
		//Top的下标是原点编号，而不是后标的点编号。注意区分。 
		if(Top[Ori[idu]] == Top[x])	curC -= Cost[1][idu] , sumC -= Sum[1][idu];
		
		curC -= Num[1][idx] * sumC;
		curC += num1 * sumC;
		ans1 += curC;
		
		num1 += numC;
		ans2 += num1 * sum2;
	}
	else
	{
		int idx = Id[x] , idy = Id[y] , idd = idx + 1;
		LL curC = Cost[0][idy] , sumC = Sum[0][idy] , numC = Num[0][idy] - Num[0][idx] + 1;
		if(Top[Ori[idd]] == Top[x])	curC -= Cost[0][idd] , sumC -= Sum[0][idd];
	//	printf("%lld %lld\n",curC,sumC);
		
		curC -= Num[0][idx] * sumC;
		curC += num1 * sumC;
		ans1 += curC;
		
		num1 += numC;
		ans2 += num1 * sum2;
	}
	return ans1 + ans2;
}
void Query()
{
	while(q --)
	{
		int x = read() , y = read();
		//printf("%lld\n",getAns(x,y));
		LL ans = getAns(x,y);
		printf("%lld\n",ans);
	}
}
int main()
{
	freopen("2577.in","r",stdin);
	freopen("2577.out","w",stdout);
	Read();
	DFS1(1,0);
	Top[1] = 1;
	DFS2(1,0);
	Init();
	Query();
	return 0;
}
