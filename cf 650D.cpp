#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=4e5+5;
int n,m,maxlen,cur=-1,newN;
int A[MAXN],Tree[MAXN],Ori[MAXN]; //LIS��Ҫ��ɢ����ֵ��
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
		scanf("%d",&A[i]);//ԭ���� 
		Ori[i]=A[i];//�����ֵ��������Ori 
	}
	sort(Ori+1,Ori+1+n);
	newN=unique(Ori+1,Ori+1+n)-Ori-1;//ȥ��
	//��Ҫ���ñ����� 
	//ע�����ڷ�������ĩ+1λ����Ӧ�ټ�1�� 
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
		f[i]=AskMax(nowVal-1);//i֮ǰ(����i)��ĩλ��С��i��LIS�� 
		maxlen=max(maxlen,f[i]+1);
		Update(nowVal,f[i]+1);
	}
	//printf("%d\n",maxlen);
}
void RevLIS()
{
	//��׺���ֵ�󷨣�ת����ǰ׺��
	memset(Tree,0,sizeof(Tree));
	for(int i=n;i>=1;i--)
	{
		int nowVal=lower_bound(Ori+1,Ori+1+newN,A[i])-Ori;
		int newId=newN-nowVal+1;
		g[i]=AskMax(newId-1);//i֮��,ĩλ�ô���i��LIS 
		Update(newId,g[i]+1);
	} 
}
void AskNecessary()
{
	//Vis[i]==0 iΪ��ѡ  Vis[i]==1 i�Ǳ�ѡ 
	//�������ȣ�ѡ i Ҫ�ܹ�ѡ�����ֵ�� 
	
	//����ѯ���Ƿ����j<i,A[j]>=A[i]ʹ��LIS[j]==maxlen ; ����ѯ���Ƿ����j>i,A[j]<=A[i]��ʹ��LIS[j]==maxlen 
	//����أ���f[i]+ 1 + g[i]���� ��״������ val[i]�Ķ�Ӧ���� �����׺���ֵ��
	//����׺���ֵת��Ϊǰ׺���ֵ���� 
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
	for(int i=1;i<=m;i++)//ѯ�� 
	{
		scanf("%d%d",&Que[i].pos,&Que[i].newVal);//�޸�λ�á���ֵ 
		Add(Que[i].pos,i);
		if(Vis[Que[i].pos])	Que[i].ans=maxlen;//�����Ǳ�ѡ 
		else	Que[i].ans=maxlen-1;//����ѡ��ֻ����maxlen-1���� 
	}
	//for(int i=1;i<=m;i++)	printf("%d ",Que[i].ans);
	//printf("\n");
	memset(Tree,0,sizeof(Tree));
	for(int i=1;i<=n;i++)
	{
		for(int h=Head[i];h!=-1;h=Q[h].next)
		{
			int id=Q[h].id;
			//id�ŵ�ѯ�ʣ�ǿ�Ƹ���ֵ������fֵ��
			int last=lower_bound(Ori+1,Ori+1+newN,Que[id].newVal)-Ori;//���ڵ���newVal�ĵ�һ��Ԫ�ء�
			//��last=m+1,��˵�������ڴ��ڵ���newVal��Ԫ�أ�����last-1;����Ҳ��last-1
			Que[id].pre+=AskMax(last-1);//[1,last-1]��ǰ׺���ֵ�� 
		}
		Update(lower_bound(Ori+1,Ori+1+newN,A[i])-Ori,f[i]+1);
	}
	memset(Tree,0,sizeof(Tree));
	for(int i=n;i>=1;i--)
	{
		for(int h=Head[i];h!=-1;h=Q[h].next)
		{
			int id=Q[h].id;
			//id�ŵ�ѯ�ʣ�ǿ������ֵ������gֵ��
			//���������ɢ����Ӧ����newVal:upper_bound����ת������ǰ׺max����
			int last=upper_bound(Ori+1,Ori+1+newN,Que[id].newVal)-Ori;
			//��last=m+1,��˵�������ڴ���newVal��Ԫ�أ����ܸ��¡�
			if(last!=newN+1)	Que[id].pre+=AskMax(newN-last+1); 
		}
		Update(newN-(lower_bound(Ori+1,Ori+1+newN,A[i])-Ori)+1,g[i]+1);
	}
	for(int i=1;i<=m;i++)	
	{
		Que[i].ans=max(Que[i].pre+1,Que[i].ans);//�ǵü����Լ� 
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
