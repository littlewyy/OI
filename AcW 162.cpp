#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 3E4 + 5;
int n,m;
int Num[MAXN],Rank[MAXN],Pre[MAXN],Next[MAXN],Ans[MAXN];//��������ָ���������ĸ����� 
struct wyy
{
	int num,id;
}A[MAXN];
void Read()
{
	scanf("%d%d",&m,&n);
	for(int i = 1 ; i <= m ; i ++)	
	{
		scanf("%d",&A[i].num);
		A[i].id = i;
	}
	for(int i = 1 ; i <= n ; i ++)	scanf("%d",&Num[i]);
}
bool cmp(wyy x , wyy y)
{
	return x.num < y.num;
}
void Calc()
{
	int used = Num[n];//�ڶ��е���Ŀ 
	sort(A + 1 , A + 1 + used ,cmp);//���մ�С���� 
	for(int i = 1 ; i <= used ; i ++)	Rank[A[i].id] = i;//��i�������Ĵ�С������ 
	
	Pre[0] = 0 , Next[0] = 1;
	Pre[used + 1] = used , Next[used + 1] = used + 1;
	for(int i = 1 ; i <= used ; i ++)	Pre[i] = i - 1 , Next[i] = i + 1;
	
	int point = n + 1, inQ = used;
	for(int i = n; i >= 1 ; i --)
	{
		point = Pre[point];//i-- , �����Զ����� 
		while(inQ > Num[i])	
		{
			int del = Rank[inQ --];
			if(del <= point)	point = Next[point];
			int pre = Pre[del] , next = Next[del];
			Next[pre] = next , Pre[next] = pre;
		}
		Ans[i] = A[point].num;
	}
}
void Print()
{
	for(int i = 1 ; i <= n ; i ++)
		printf("%d\n",Ans[i]);
}
int main()
{
	freopen("AcW 162.in","r",stdin);
	freopen("AcW 162.out","w",stdout);
	//��������������ģ�⡣��������ɾ������ɾ����Ԫ���ǹ����ߵ�������ָ�롣���򲻱䡣 
	//���ڴ���Ԫ��ɾ������˫������ά���� 
	//��һ�����⣺������ֵ������������±��ӳ���ϵ�������ӳ���ȥ�ɡ�
	Read();
	Calc(); 
	Print();
	return 0;
}
