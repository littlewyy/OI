#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN=2E5+5,MAXL=20;
const LL mod=998244353; 
int n,cur=-1,q;
int A[MAXN],D[MAXN],Head[MAXN],Que[MAXN],Dep[MAXN];
int Jump[MAXN][MAXL],Fa[MAXN],maxa;
LL Diff[MAXN],Val[MAXN];
LL Ori[MAXN],Squ[MAXN];
struct wyy
{
	int to,next;
	LL p;
}Edge[2*MAXN];
void Add(int from,int to,LL p)
{
	Edge[++cur].to=to;
	Edge[cur].next=Head[from];
	Edge[cur].p=p;
	Head[from]=cur;
	
	Edge[++cur].to=from;
	Edge[cur].next=Head[to];
	Edge[cur].p=p;
	Head[to]=cur;
}
void Read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d%d",&A[i],&D[i]);
	memset(Head,-1,sizeof(Head));
	for(int i=1;i<n;i++)
	{
		int x,y,v;
		scanf("%d%d%d",&x,&y,&v);
		Add(x,y,v);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)	scanf("%d",&Que[i]);
}
void Dfs(int x,int fa)
{
	for(int h=Head[x];h!=-1;h=Edge[h].next)
	{
		int y=Edge[h].to;
		if(y!=fa)	
		{
			Dep[y]=Dep[x]+1;
			Fa[y]=Jump[y][0]=x;
			Dfs(y,x);
		}
	}
}
void DpFa()
{
	for(int L=1;(1<<L)<=n;L++)
	{
		for(int i=1;i<=n;i++)
		{
			int mid=Jump[i][L-1];
			if(mid)	Jump[i][L]=Jump[mid][L-1];
		}
	}
}
void PostTag()
{
	maxa=log(n)/log(2);
	for(int i=1;i<=n;i++)
	{
		//Diff[i]+=A[i];
		Diff[i]=(Diff[i]+A[i])%mod;
		int len = D[i];
		if( len < Dep[i] )	
		{
			int cur=i;
			for(int j = maxa ;j >= 0; j --)
				if( ( len & (1<<j) ) > 0)
					cur=Jump[cur][j];
			//Diff[Fa[cur]]-=A[i];
			Diff[Fa[cur]]=(Diff[Fa[cur]]-A[i]+mod)%mod;
		}
	}
}
void CalcVal(int x,int fa)
{
	Val[x]=Diff[x];
	for(int h=Head[x];h!=-1;h=Edge[h].next)
	{
		int y=Edge[h].to;
		if(y!=fa)	
		{
			CalcVal(y,x);
			Val[x]=(Val[x]+Val[y])%mod;
			//Val[x]+=Val[y];
		}
	}
}
void Init()
{
	//进行第一次深搜：记录fa
	Dfs(1,0);
	//外重循环为L，计算Jump[i][j] 
	DpFa();
	//计算Val（F）值。统一打标记，再DFS计数
	PostTag();
	CalcVal(1,0); 
}
void Dp(int x,int fa)
{
	Ori[x]=Val[x],Squ[x]=Val[x]*Val[x]%mod;
	for(int h=Head[x];h!=-1;h=Edge[h].next)
	{
		int y=Edge[h].to;
		if(y!=fa)
		{
			Dp(y,x);
			//Ori[x]必须为未得到y之前的，与新来的y相匹配 
			Squ[x]=(Squ[x]+Edge[h].p*((Squ[y]+2ll*Ori[x]%mod*Ori[y]%mod)%mod)%mod)%mod;
			Ori[x]=(Ori[x]+Edge[h].p*Ori[y]%mod)%mod;
		}
	}
}
void NewRoot(int x,int fa)//会不会是 
{
	for(int h=Head[x];h!=-1;h=Edge[h].next)
	{
		int y=Edge[h].to;
		if(y!=fa)
		{
			LL tempOri=(Ori[x]-Edge[h].p*Ori[y]%mod+mod)%mod;//换根后 x（即原根）不含y这棵子树 ； 这也是原本遇到y这个子树前i的状态 
			LL tempSqu=(Squ[x]-Edge[h].p*((Squ[y]+2ll*Ori[y]%mod*tempOri%mod)%mod)%mod+mod)%mod;
			Squ[y]=(Squ[y]+(Edge[h].p*(tempSqu+2ll*tempOri%mod*Ori[y]%mod)%mod)%mod)%mod;
			Ori[y]=(Ori[y]+Edge[h].p*tempOri%mod)%mod;
			NewRoot(y,x);
		}
	}
}
void Query()
{
	for(int i=1;i<=q;i++)
		printf("%lld\n",Squ[Que[i]]);
}
void Calc()
{ 
	//先以1为根计算
	Dp(1,0);
    //再逐次换根
    NewRoot(1,0);
    Query();
}
int main()
{
	freopen("2699.in","r",stdin);
	freopen("2699.out","w",stdout);
	Read();
	Init();
	Calc();
	return 0;
}
