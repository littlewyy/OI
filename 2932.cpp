#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 2E5 + 5;
LL mod = 1e9 + 7;
int Num,n,M1,M2,fr;
int Node[MAXN][2],Degree[MAXN],Vis[MAXN];
int CntOdd[MAXN],CntEven[MAXN][2],CntCir[MAXN];
LL Fact[MAXN];
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
void Read()
{
	Num = read();
	n = read() , M1 = read() , M2 = read();
	for(int i = 1 ; i <= M1 ; i ++)
	{
		int u = read() , v = read();
		Node[u][0] = v;
		Node[v][0] = u;
		Degree[u] ++ , Degree[v] ++;
	}
	for(int i = 1 ; i <= M2 ; i ++)
	{
		int u = read() , v = read();
		Node[u][1] = v;
		Node[v][1] = u;
		Degree[u] ++ , Degree[v] ++;
	}
}
void Init()
{
	fr = n;//����Ԫ�ظ��� 
	//����Ϊ���������������¼ͷβ��
	//����Ϊż����������Ҫ��¼ͷβ�� 
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Degree[i] == 1 && Vis[i] == 0)//���� 
		{
			if(Node[i][0])
			{
				Vis[i] = 1;
				int temp = Node[i][0] , cur = 0 , num = 1;
				while(temp)
				{
					num ++ , Vis[temp] = 1;
					cur ^= 1 , temp = Node[temp][cur];
				}
				fr -= num;
				if(num % 2)	CntOdd[num] ++;//����Ϊ�����ġ�����Ϊnum�������� 
				else	CntEven[num][0] ++;//����Ϊż���ġ�0��ͷ�ġ�����Ϊnum���������� 
			}
			else
			{
				Vis[i] = 1;
				int temp = Node[i][1] , cur = 1 , num = 1;
				while(temp)
				{
					num ++ , Vis[temp] = 1;
					cur ^= 1 , temp = Node[temp][cur];
				}
				fr -= num;
				if(num % 2)	CntOdd[num] ++;
				else	CntEven[num][1] ++;
			}
		}
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Degree[i] == 2 && Vis[i] == 0)//�ڻ��С� 
		{
			Vis[i] = 1;
			int temp = Node[i][0] , num = 1 , cur = 0;
			while(temp != i)
			{
				num ++ , Vis[temp] = 1;
				cur ^= 1 , temp = Node[temp][cur];
			}
			fr -= num;
			CntCir[num] ++;//����Ϊnum�ĸ��� 
		}
	}
}
void PreFact()
{
	Fact[0] = 1;
	for(int i = 1 ; i <= n ; i ++)
		Fact[i] = Fact[i - 1] * i % mod;
}
LL getFact(int x)
{
	return Fact[x];
}
LL getPow(int x,int times)
{
	if(times == 0)	return 1;
	LL half = getPow(x,times >> 1);
	LL temp = half * half % mod;
	if(times & 1)	temp = temp * x % mod;
	return temp;
}
void Calc()
{
	LL ans = getFact(fr);
	for(int i = 3 ; i <= n ; i += 2)//����Ϊ��������������Ϊż����ÿ�����Լ����ܵ����� 
		if(CntOdd[i])
			ans = ans * getFact(CntOdd[i]) % mod;
	for(int i = 2 ; i <= n ; i += 2)//����Ϊż������������Ϊ������010����ͷ��ͬ���ȼۣ����Լ����Գ�2
	{
		if(CntEven[i][0])	ans = ans * getFact(CntEven[i][0]) % mod * getPow(2,CntEven[i][0]) % mod;
		if(CntEven[i][1])	ans = ans * getFact(CntEven[i][1]) % mod * getPow(2,CntEven[i][1]) % mod;
	}		
	for(int i = 2 ; i <= n ; i ++)
		if(CntCir[i])
			ans = ans * getFact(CntCir[i]) % mod * getPow(i,CntCir[i]) % mod;
	printf("%lld\n",(getFact(n) - ans + mod) % mod);
}
int main()
{
	freopen("2932.in","r",stdin);
	freopen("2932.out","w",stdout);
	//����������Ϊ1�ĵ㡣�һ�������Ϊ2�ĵ㡣
	Read(); 
	Init();
	PreFact();
	Calc();
	return 0;
}
