#include<bits/stdc++.h>//����ϸ�¼����룬һ�ι��� 
using namespace	std;
const int MAXN=1E5+5,MAXM=2E5+5;
int n,m,cur=-1;
int RealOut[MAXN],Head[MAXN],TempIn[MAXN],Q[MAXN];
double E[MAXN];
struct wyy
{
	int to,next,va;
}Edge[MAXM];//ϸ�Ĺ۲���Ŀ���ݷ�Χ 
void Add(int from,int to,int va)
{
	Edge[++cur].to=to;
	Edge[cur].next=Head[from];
	Edge[cur].va=va;
	Head[from]=cur;
}
void Read()
{
	scanf("%d%d",&n,&m);
	memset(Head,-1,sizeof(Head));
	for(int i=1;i<=m;i++)
	{
		int a,b,c;scanf("%d%d%d",&a,&b,&c);//scanf��Ҫ©�� 
		RealOut[a]++;TempIn[a]++;//ϸ�£� 
		Add(b,a,c);//�浥����� 
	}
}
void TopDp()
{
	E[n]=0;int tail=0;
	for(int i=1;i<=n;i++)	if(TempIn[i]==0)	Q[++tail]=i;
	while(tail)
	{
		int x=Q[tail--];
		for(int h=Head[x];h!=-1;h=Edge[h].next)
		{
			int y=Edge[h].to;
			E[y]+=(E[x]+Edge[h].va)/RealOut[y];
			TempIn[y]--;
			if(TempIn[y]==0)	Q[++tail]=y;
		}
	}
	printf("%.2lf\n",E[1]);
}
int main()
{
	//�̶��ܵĹ���
	freopen("flog.in","r",stdin);
	freopen("flog.out","w",stdout);
	Read();
	TopDp();
	return 0;
}
