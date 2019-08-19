#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5E5 + 5;
int n,q;
int A[2][MAXN];
int read()
{
	char ch = getchar();
	int w = 0;
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
	n = read() , q = read();
	for(int i = 0 ; i <= 1 ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			A[i][j] = read();
}
int Solve(int l,int r,int ll,int rr,int half)
{
	int lo,hi;
	//右边至多rr - ll + 1个，所以左边最少 half - (rr - ll + 1)个，hi下界l + ... -1 , lo下界  -2 
	lo = max(l - 1,l + half - (rr - ll + 1) - 2);
	hi = min(r,l + half - 2);//左边至多取half - 1个。 
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		int lef = half - (mid - l + 1);
		if(A[1][ll + lef - 1] > A[0][mid])	lo = mid;
		else	hi = mid;
	}
	//可能有边界问题。应考虑完善一些，想不清楚的拍拍就知道了。 
	int left = half - (hi - l + 1);
	if(A[1][ll + left - 1] <= A[0][hi])
	{
		if(ll + left == rr + 1)	return A[0][hi];
		else	if(A[1][ll + left] > A[0][hi])	return A[0][hi];
	}
	
	lo = max(ll - 1 , ll + half - (r - l + 1) - 2);
	hi = min(rr,ll + half - 2);
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		int lef = half - (mid - ll + 1);
		if(A[0][l + lef - 1] > A[1][mid])	lo = mid;
		else	hi = mid;
	}
	return A[1][hi];
}
void Calc()
{
	for(int i = 1 ; i <= q ; i ++)
	{
		int type = read();
		if(type == 1)
		{
			int x = read() , y = read() , z = read();
			A[x][y] = z;
		}
		else
		{
			int l = read() , r = read() , ll = read() , rr = read();//二分。 
			int len = r - l + 1 + rr - ll + 1 , half = (len + 1) >> 1;
			//只有这2种情况，前half个元素仅由单一数组中的元素构成 
			if(r - l + 1 >= half && A[0][l + half - 1] <= A[1][ll])	printf("%d\n",A[0][l + half - 1]);
			else	if(rr - ll + 1 >= half && A[1][ll + half - 1] <= A[0][l])	printf("%d\n",A[1][ll + half - 1]);
			else	printf("%d\n",Solve(l,r,ll,rr,half));
		}
	}
}
int main()
{
	freopen("2946.in","r",stdin);
	freopen("2946.out","w",stdout);
	Read();
	Calc(); 
	return 0;
}
