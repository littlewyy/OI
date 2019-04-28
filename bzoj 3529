#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5 , MAXQ = 2E4 + 5;
int p = 0 , q;
bool Vis[MAXN];
int Miu[MAXN],Prime[MAXN / 10],MinPow[MAXN],Tree[MAXN],Ans[MAXN];
struct wyy
{
	int num,id;
}Sigma[MAXN];
struct que
{
	int n,m,a,id;
}Q[MAXQ];
void Sift()
{
	Miu[1] = 1 , Sigma[1].num = 1;
	for(int i = 2 ; i <= 1e5 ; i ++)	
	{
		//printf("ok\n");
		if(!Vis[i])	Miu[i] = -1 , Sigma[i].num = 1 + i , Prime[++ p] = i , MinPow[i] = i;
		for(int j = 1 ; j <= p ; j ++)
		{
			LL tar = LL(i) * Prime[j];
			if(tar > 1e5)	break;
			Vis[tar] = 1;
			if(i % Prime[j])	
				Miu[tar] = - Miu[i] , 
				Sigma[tar].num = Sigma[i].num + Sigma[i].num * Prime[j] ,
				MinPow[tar] = Prime[j];
			else	
			{
				Miu[tar] = 0 , 
				Sigma[tar].num = Sigma[i].num + Sigma[i / MinPow[i]].num * MinPow[i] * Prime[j],			    
				MinPow[tar] = MinPow[i] * Prime[j];
				break;
			}	
		}
	}
	//for(int i = 1 ; i <= 20 ; i ++)	
		//printf("%d : %d\n",i,Sigma[i].num);
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
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i ++)
	{
		Q[i].n = read() , Q[i].m = read() , Q[i].a = read();
		Q[i].id = i;
	}
}
bool cmp(wyy x,wyy y)
{
	return x.num < y.num;
}
bool qcmp(que x,que y)
{
	return x.a < y.a;
}
void Init()
{
	for(int i = 1 ; i <= 1e5 ; i ++)	Sigma[i].id = i;
	sort(Sigma + 1 , Sigma + 1 + 100000 , cmp);
	sort(Q + 1 , Q + 1 + q , qcmp);
}
int Ask(int x)
{
	int nowAns = 0;
	for(; x ; x -= x & -x)	nowAns += Tree[x];
	return nowAns;
}
void Update(int x,int y)
{
	for(; x <= 1e5 ; x += x & -x)	Tree[x] += y;
}
int Solve(int n,int m)
{
	if(n > m)	swap(n,m);
	int ans = 0;
	for(int i = 1 , end ; i <= n ; i = end + 1)
	{
		end = min(n / (n / i) , m / (m / i));
		ans += (Ask(end) - Ask(i - 1)) * (n / i) * (m / i);
	}
	return ans;
} 
void Calc()
{
	int point = 0;
	for(int i = 1 ; i <= q; i ++)
	{
		int n = Q[i].n , m = Q[i].m , a = Q[i].a , id = Q[i].id;
		while(point < 1e5 && Sigma[point + 1].num <= a)	
		{
			point ++;
			for(int j = 1 ; j <= 1e5 / Sigma[point].id ; j ++)
				Update(Sigma[point].id * j , Sigma[point].num * Miu[j]);
		}
		Ans[id] += Solve(n,m);
	}
}
void Print()
{
	for(int i = 1 ; i <= q ; i ++)
	{
		Ans[i] = Ans[i] & 2147483647;//取模2^31：用int,并且 &2147483647 
		printf("%d\n",Ans[i]);
	}
}
int main()
{
	freopen("bzoj 3529.in","r",stdin);
	freopen("bzoj 3529.out","w",stdout);
	Sift();
	Read();
	Init();
	Calc();
	Print();
	return 0;
}
