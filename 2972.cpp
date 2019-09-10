#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5 , inf = 0x7fffffff;
int n;
int A[MAXN],Ans[MAXN];
int Q[3][MAXN];
int read()
{
	char ch = getchar();
	int w = 0 , f = 1;
	while(ch != '-' && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	f = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w * f;
}
void Read()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++)
		A[i] = read();
}
int Solve(int diff)//求极差小于等于diff的最大区间长度 
{
	int head1,tail1,head2,tail2,lef,ans;
	head1 = tail1 = head2 = tail2 = lef = ans = 1;
	Q[1][1] = Q[2][1] = 1;
	for(int i = 2 ; i <= n ; i ++)
	{
		while(head1 <= tail1 && A[Q[1][tail1]] >= A[i])	tail1 --;//全部小于A[i]的递增序列 
		while(head2 <= tail2 && A[Q[2][tail2]] <= A[i])	tail2 --;//全部大于A[i]的递减序列
		Q[1][++ tail1] = i , Q[2][++ tail2] = i;
		while(head1 <= tail1 && head2 <= tail2 && A[Q[2][head2]] - A[Q[1][head1]] > diff)
		{
			lef ++;
			if(Q[1][head1] < lef)	head1 ++;
			if(Q[2][head2] < lef)	head2 ++;
		}		
		ans = max(ans,i - lef + 1);
	} 
	return ans;
}
void Calc()
{
	int lastlen = 1;
	for(int i = 0 ; i <= 1050000 ; i = max(i + 1,(int)(i * 1.05)))
	{
		int len = Solve(i);
		if(len > lastlen)	
		{
			for(int j = lastlen + 1 ; j <= len ; j ++)	Ans[j] = i;
			lastlen = len;
		}
	}
	for(int i = 2 ; i <= n ; i ++)	printf("%d\n",Ans[i]);
}
int main()
{
	freopen("2972.in","r",stdin);
	freopen("2972.out","w",stdout);
	Read();
	Calc();
	return 0;
}
