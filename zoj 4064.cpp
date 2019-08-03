#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 105 , MAXM = 10005;
const LL mod = 1e9 + 7;
int n,m,pos,T;
int A[MAXN],Q[MAXN],Num[MAXN];
LL f[MAXN][MAXM][2];
void Read()
{
	scanf("%d%d",&n,&m);
	pos = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d",&A[i]);
		if(A[i] == 1 || A[i] == 2)	Q[++ pos] = i;
		Num[i] = Num[i - 1];
		if(A[i] == 1)	Num[i] ++;
	}
}
LL getPow(int x,int times)
{
	if(times == 0)	return 1ll;
	LL half = getPow(x,times >> 1);
	LL cur = half * half % mod;
	if(times & 1)	cur = cur * x % mod;
	return cur;
}
void Dp()
{
	memset(f,0,sizeof(f));//������ 
	//�������ʱ,ö�����1�����ɿ�Խλ��������
	//������ˣ���������ڱ�n + 1������Ϊ1������f[n+1]...����Ϊͬ�� 
	f[0][0][0] = 1;
	Q[pos + 1] = n + 1 , A[n + 1] = 1;
	for(int i = 1 ; i <= pos + 1; i ++)//ǿ������Ϊ1 
	{
		int x = Q[i];//��x����i 
		int type = (A[x] == 1) ? 0 : 1;//����˴���Ϊ2�������1�ηǷ���  
		for(int j = i - 1 ; j >= 0 ; j --)//ö����һ�����ɿ�Խλ 
		{
			int y = Q[j] , nume = x - y - 1 , fr = y - 1 - Num[y - 1];//�ɸ���λ����
			for(int k = 0 ; k <= fr * (fr + 1) / 2 ; k ++)//ǰy-1��λ�ö���...����λ 
				for(int t = 0 ; t <= 1 ; t ++)
					f[x][k + nume * (nume + 1) / 2][t ^ type] = (f[x][k + nume * (nume + 1) / 2][t ^ type] + f[y][k][t]) % mod;
			if(A[y] == 1)	break;
		}
	}
}
void Calc()
{
	LL ans = 0 , fr = n - Num[n];
	for(int j = 1 ; j <= fr * (fr + 1) / 2; j ++)	
	{
		for(int t = 0 ; t <= 1 ; t ++)
		{
			if(f[n + 1][j][t] == 0)	continue;
			LL type = (t == 0) ? 1 : -1;
			ans = (ans + mod + type * f[n + 1][j][t] * getPow(j,m) % mod) % mod;
		}
	}
	printf("%lld\n",ans); 
}
int main()
{
	//freopen("zoj 4064.in","r",stdin);
	//freopen("zoj 4064.out","w",stdout);
	scanf("%d",&T);
	while(T --)
	{
		Read();
		Dp();
		Calc();
	}	
	return 0;
}
