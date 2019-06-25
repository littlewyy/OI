#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 7505;
int n,k;
int Fa[MAXN],Siz[MAXN],Dis[MAXN][MAXN];
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = i + 1 ; j <= n ; j ++)
			Dis[j][i] = (2019201913LL * i + 2019201949LL * j) % 2019201997LL;
	}
}
int findA(int x)
{
	if(Fa[x] == x)	return x;
	return Fa[x] = findA(Fa[x]);
}
void Calc()
{
	int block = n,ans = -1;
	for(int i = 1 ; i <= n ; i ++)	Fa[i] = i,Siz[i] = 1;
	for(int i = n ; i >= 2 ; i --)
	{
		for(int j = i - 1 ; j >= 1 ; j --)
		{
			int rootx = findA(i) , rooty = findA(j);
			if(rootx != rooty)
			{
				if(block == k)
				{
					ans = Dis[i][j];
					break;
				}
				else
				{
					if(Siz[rootx] < Siz[rooty])	Fa[rootx] = rooty , Siz[rooty] += Siz[rootx];
					else	Fa[rooty] = rootx , Siz[rootx] += Siz[rooty];
					block --;
				}
			}
		}
		if(ans != -1)	break;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("2914.in","r",stdin);
	freopen("2914.out","w",stdout);
	Read();
	Calc();
	return 0;
}
/*
2019201865 1817 1769 
-48
�ݼ�
ͬ1��x,����y������dis(x,y)�����ݼ�
ͬ1��y,����x������dis(x,y)�����ݼ�
��ˣ���С��Ϊ���½Ǵ�n,n-1 ; Ȼ��Ϊn,n-2 ; ��Ϊn,n-3�������1��ѡ�� 
*/
 
