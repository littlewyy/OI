#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 1E6 + 5;
int n;
int top[2],St[2][MAXN],Sum[MAXN],Max[MAXN];
int read()//读入别忘了负号! 
{
	char ch = getchar();
	int w = 0 , tmp = 1;
	while((ch < '0' || ch > '9') && ch != '-')	ch = getchar();
	if(ch == '-')	tmp = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w * tmp;
}
void Init()
{
	top[0] = top[1] = 0;
	Max[0] = -0x7fffffff;	//边界：存在负数时，Max值注意初值不为0。 
}
void Calc()
{
	while(n --)
	{
		char type = getchar();
		while(type < 'A' || type > 'Z')	type = getchar();
		if(type == 'I')
		{
			int cur = read();
			St[0][++ top[0]] = cur;
			Sum[top[0]] = Sum[top[0] - 1] + cur;
			Max[top[0]] = max(Max[top[0] - 1],Sum[top[0]]);			
		}
		if(type == 'D' && top[0] > 0)	top[0] --;
		if(type == 'L' && top[0] > 0)	St[1][++ top[1]] = St[0][top[0] --];
		if(type == 'R' && top[1] > 0)	
		{
			St[0][++ top[0]] = St[1][top[1] --];
			Sum[top[0]] = Sum[top[0] - 1] + St[0][top[0]];
			Max[top[0]] = max(Max[top[0] - 1],Sum[top[0]]);
		}
		if(type == 'Q')	
		{
			int k = read();
			printf("%d\n",Max[k]);
		}
	}
}
int main()
{
	//Q1、Sum、Maxa;Q2
	while(scanf("%d",&n) != EOF)
	{
		Init();
		Calc();
	}
	return 0;
}
