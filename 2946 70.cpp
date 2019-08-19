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
int getPos(int l,int r,int num)
{
	//返回最后1个小于等于num的位置。 
	int lo = l - 1, hi = r + 1;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(A[1][mid] <= num)	lo = mid;
		else	hi = mid;
	}
	return lo;
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
			int l = read() , r = read() , ll = read() , rr = read();
			//二分套二分：2个log
			//先找到左边的最后1个位置，满足lnum + rnum <= (len + 1) / 2
			//若num恰好等于，输出，否则答案在右边，右边向右移动差值位即为所求。
			int len = r - l + 1 + rr - ll + 1 , half = (len + 1) >> 1;
			int lo = l - 1, hi = r + 1 , lonum = 0 , lop = 0;
			while(lo + 1 < hi)
			{
				int mid = (lo + hi) >> 1;
				int rpos = getPos(ll,rr,A[0][mid]);
				int lnum = mid - l + 1 , rnum = rpos - ll + 1;
				if(lnum + rnum <= half)	lo = mid , lonum = lnum + rnum , lop = rpos;
				else	hi = mid;
			} 
			if(lonum == half)	printf("%d\n",A[0][lo]);
			else	if(lo == l - 1)	printf("%d\n",A[1][ll + half - 1]);
			else	printf("%d\n",A[1][lop + half - lonum]);
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
