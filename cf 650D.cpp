#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=4e5+5;
int n,m,maxlen,cur=-1,newN;
int A[MAXN],Tree[MAXN],Ori[MAXN]; //LIS需要离散化数值。
int f[MAXN],g[MAXN],Vis[MAXN],Head[MAXN]; 
struct wyy
{
	int pos,newVal,id,ans,pre;
}Que[MAXN];
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);//原数组 
		Ori[i]=A[i];//存放数值的容器：Ori 
	}
	sort(Ori+1,Ori+1+n);
	newN=unique(Ori+1,Ori+1+n)-Ori-1;//去重
	//不要复用变量名 
	//注意由于返回容器末+1位，故应再减1。 
}
void Update(int x,int cur)
{
	if(x==0)	return;
	for(;x<=newN;x+=x&-x)
		Tree[x]=max(Tree[x],cur);
}
int AskMax(int x)
{
	int ans=0;
	for(;x;x-=x&-x)
		ans=max(ans,Tree[x]);
	return ans;
}
void LIS()
{
	for(int i=1;i<=n;i++)
	{
		int nowVal=lower_bound(Ori+1,Ori+1+newN,A[i])-Ori;
		f[i]=AskMax(nowVal-1);//i之前(不含i)，末位置小于i的LIS。 
		maxlen=max(maxlen,f[i]+1);
		Update(nowVal,f[i]+1);
	}
	//printf("%d\n",maxlen);
}
void RevLIS()
{
	//后缀最大值求法？转换成前缀！
	memset(Tree,0,sizeof(Tree));
	for(int i=n;i>=1;i--)
	{
		int nowVal=lower_bound(Ori+1,Ori+1+newN,A[i])-Ori;
		int newId=newN-nowVal+1;
		g[i]=AskMax(newId-1);//i之后,末位置大于i的LIS 
		Update(newId,g[i]+1);
	} 
}
void AskNecessary()
{
	//Vis[i]==0 i为必选  Vis[i]==1 i非必选 
	//但是首先，选 i 要能够选出最大值。 
	
	//正向：询问是否存在j<i,A[j]>=A[i]使得LIS[j]==maxlen ; 反向：询问是否存在j>i,A[j]<=A[i]，使得LIS[j]==maxlen 
	//具体地：将f[i]+ 1 + g[i]载入 树状数组中 val[i]的对应点中 ；求后缀最大值。
	//将后缀最大值转化为前缀最大值处理 
	memset(Tree,0,sizeof(Tree));
	for(int i=1;i<=n;i++)
	{
		int nowVal=lower_bound(Ori+1,Ori+1+newN,A[i])-Ori;
		int newId=newN-nowVal+1;
		if(f[i]+g[i]+1<maxlen||AskMax(newId)==maxlen)	Vis[i]=1;
		Update(newId,f[i]+g[i]+1);
	} 
	memset(Tree,0,sizeof(Tree));
	for(int i=n;i>=1;i--)
	{
		int nowVal=lower_bound(Ori+1,Ori+1+newN,A[i])-Ori;
		if(AskMax(nowVal)==maxlen)	Vis[i]=1;
		Update(nowVal,f[i]+g[i]+1);		
	}
	//for(int i=1;i<=n;i++)	printf("%d ",Vis[i]);	
	//printf("\n");
}
struct q
{
	int next,id;
}Q[MAXN];
void Add(int from,int id)
{
	Q[++cur].id=id;
	Q[cur].next=Head[from];
	Head[from]=cur;
}
void Query()
{
	memset(Head,-1,sizeof(Head));
	for(int i=1;i<=m;i++)//询问 
	{
		scanf("%d%d",&Que[i].pos,&Que[i].newVal);//修改位置、新值 
		Add(Que[i].pos,i);
		if(Vis[Que[i].pos])	Que[i].ans=maxlen;//本来非必选 
		else	Que[i].ans=maxlen-1;//若必选则只能用maxlen-1来比 
	}
	//for(int i=1;i<=m;i++)	printf("%d ",Que[i].ans);
	//printf("\n");
	memset(Tree,0,sizeof(Tree));
	for(int i=1;i<=n;i++)
	{
		for(int h=Head[i];h!=-1;h=Q[h].next)
		{
			int id=Q[h].id;
			//id号的询问：强制改新值后的最大f值。
			int last=lower_bound(Ori+1,Ori+1+newN,Que[id].newVal)-Ori;//大于等于newVal的第一个元素。
			//若last=m+1,则说明不存在大于等于newVal的元素，则用last-1;其它也用last-1
			Que[id].pre+=AskMax(last-1);//[1,last-1]的前缀最大值。 
		}
		Update(lower_bound(Ori+1,Ori+1+newN,A[i])-Ori,f[i]+1);
	}
	memset(Tree,0,sizeof(Tree));
	for(int i=n;i>=1;i--)
	{
		for(int h=Head[i];h!=-1;h=Q[h].next)
		{
			int id=Q[h].id;
			//id号的询问：强制用新值后的最大g值。
			//则后面在离散化后应大于newVal:upper_bound；倒转过来当前缀max处理
			int last=upper_bound(Ori+1,Ori+1+newN,Que[id].newVal)-Ori;
			//若last=m+1,则说明不存在大于newVal的元素，则不能更新。
			if(last!=newN+1)	Que[id].pre+=AskMax(newN-last+1); 
		}
		Update(newN-(lower_bound(Ori+1,Ori+1+newN,A[i])-Ori)+1,g[i]+1);
	}
	for(int i=1;i<=m;i++)	
	{
		Que[i].ans=max(Que[i].pre+1,Que[i].ans);//记得加上自己 
		printf("%d\n",Que[i].ans);
	}
}
int main()
{
	//freopen("cf 650D.in","r",stdin);
	//freopen("cf 650D.out","w",stdout);
	Read();
	LIS();
	RevLIS();
	AskNecessary();
	Query();
	return 0;
}
