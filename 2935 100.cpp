#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3E5 + 5;
int n,m,q,k,cur = -1;
int Degree[MAXN],Tag[MAXN];
int Ori[MAXN],Given[MAXN];
vector<int>E[MAXN],G[MAXN];
int read()
{
	char ch = getchar();int w = 0 , sym = 1;
	while(ch != '-' && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	sym = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w * sym;
}
void Read()
{
	n = read() , m = read() , q = read();
	for(int i = 1 ; i <= m ; i ++)
	{
		int u = read() , v = read();
		Degree[u] ++ , Degree[v] ++;
		E[u].push_back(v);E[v].push_back(u);
	}
}
void Rebuild()
{
	k = sqrt(2 * m), cur = -1;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Degree[i] > k)
		{
			int len = E[i].size();
			for(int j = 0 ; j < len ; j ++)
			{
				int y = E[i][j];
				G[y].push_back(i);
			}
		}
	}
}
void Calc()
{
	memset(Tag,-1,sizeof(Tag));
	while(q --)
	{
		int type = read() , x = read();
		if(!type)//Ñ¯ÎÊ¡£
		{
			int curAns = Ori[x] + Given[x] , len = G[x].size();
			for(int i = 0 ; i < len ; i ++)
			{
				int to = G[x][i];
				if(Tag[to] != q)
				{
					curAns += Ori[to];
					Tag[to] = q;
				}				
			}				
			printf("%d\n",curAns);
		}
		else
		{
			int y = read();
			Ori[x] += y;
			if(Degree[x] <= k)
			{				
				int len = E[x].size();
				for(int i = 0 ; i < len ; i ++)
				{
					int to = E[x][i];
					if(Tag[to] != q)
					{
						Given[to] += y;
						Tag[to] = q;
					}
				}
			}
		}
	}
}
int main()
{
	freopen("2935.in","r",stdin);
	freopen("2935.out","w",stdout);
	Read();
	Rebuild();
	Calc();
	return 0;
}
