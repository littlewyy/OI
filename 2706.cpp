#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 2005;
int n,m;
int Height[MAXN][MAXN];
int Lef[MAXN],Rig[MAXN],Stack[MAXN];
char S[MAXN][MAXN];
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)	scanf("%s",S[i] + 1);
}
void Init()
{
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)	
			if(S[i][j] == '.')
				Height[i][j] = Height[i - 1][j] + 1;
}
LL getAns(int lef,int cur,int rig,int h)
{
	LL a = LL(1 + rig - cur + 1) * (rig - cur + 1) / 2;
	LL b = LL(cur - lef + 1 + rig - lef + 1) * (rig - cur + 1) / 2;
	LL single = LL(a + b) * (cur - lef + 1) / 2;
	return LL(1 + h) * h / 2 * single;
}
void Calc()
{
	LL ans = 0;
	for(int i = 1 ; i <= n ; i ++)	
	{
		int first,Stop;
		for(int j = 1 ; j <= m ; j ++)
		{
			if(S[i][j - 1] != '.')	
			{
				first = Lef[j] = j;
				Stop = 1 , Stack[1] = j;
			}
			else
			{
				//左边可以接受大于等于的。 
				while(Stop && Height[i][Stack[Stop]] >= Height[i][j])	Stop --;
				if(Stop == 0)	Lef[j] = first;
				else	Lef[j] = Stack[Stop] + 1;
				Stack[++ Stop] = j;
			}
		}
		for(int j = m ; j >= 1 ; j --)
		{
			if(S[i][j + 1] != '.')
			{
				first = Rig[j] = j;
				Stop = 1 , Stack[1] = j;
			}
			else
			{
				//右边只能接受大于 
				while(Stop && Height[i][Stack[Stop]] > Height[i][j])	Stop --;
				if(Stop == 0)	Rig[j] = first;
				else	Rig[j] = Stack[Stop] - 1;
				Stack[++ Stop] = j;	
			}
		}
		for(int j = 1 ; j <= m ; j ++)	ans += getAns(Lef[j],j,Rig[j],Height[i][j]);
	}
	printf("%lld\n",ans);
}
int main()
{//不可以。我可以。 
	freopen("2706.in","r",stdin);
	freopen("2706.out","w",stdout);
	Read();
	Init();
	Calc();
	return 0;
}
