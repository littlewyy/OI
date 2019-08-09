#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 3E4 + 5;
int n,m;
int Num[MAXN],Rank[MAXN],Pre[MAXN],Next[MAXN],Ans[MAXN];//各个查找指令所含数的个数。 
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
	int used = Num[n];//在队中的数目 
	sort(A + 1 , A + 1 + used ,cmp);//按照大小排序 
	for(int i = 1 ; i <= used ; i ++)	Rank[A[i].id] = i;//第i个操作的大小排名。 
	
	Pre[0] = 0 , Next[0] = 1;
	Pre[used + 1] = used , Next[used + 1] = used + 1;
	for(int i = 1 ; i <= used ; i ++)	Pre[i] = i - 1 , Next[i] = i + 1;
	
	int point = n + 1, inQ = used;
	for(int i = n; i >= 1 ; i --)
	{
		point = Pre[point];//i-- , 排名自动向左。 
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
	//做法：不妨倒着模拟。将插入变成删除。若删除的元素是光标左边的则右移指针。否则不变。 
	//由于存在元素删除，用双向链表维护。 
	//有一个问题：建立数值与排序后数组下标的映射关系。排序后映射回去吧。
	Read();
	Calc(); 
	Print();
	return 0;
}
