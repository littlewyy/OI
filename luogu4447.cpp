#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5;
int n,ans,A[MAXN];
struct que
{
	int las,len;
	bool operator < (const que &a)const//小根堆 
	{
		return len > a.len;
	}
};
priority_queue<que>Q,Tmp; 
void Read()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)	scanf("%d",&A[i]);
}
void Solve()
{
	sort(A + 1 , A + 1 + n);
	//for(int i = 1 ; i <= n ; i ++)	cout << A[i] << endl;
	//流程：对于每一种数值，在每一种数值的结尾，再统一入队
	A[n + 1] = A[n] + 1 , ans = n + 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		//加数前弹出与该数值不能连接的队列 
		while((!Q.empty()) && Q.top().las != (A[i] - 1))	
		{
			ans = min(ans,Q.top().len);
			Q.pop();//之前数值的队列 
		} 
		if(!Q.empty())//已有数列能与该数连接  
		{
			que tmp = Q.top();
			tmp.len ++ , tmp.las ++;
			Tmp.push(tmp);//入队。。 
			Q.pop(); 
		}
		else//已有数列不能与该数连接：自创队列   
		{
			que tmp;
			tmp.len = 1 , tmp.las = A[i];
			//printf("%d %d\n",i,A[i]);
			Tmp.push(tmp);//加入临时队列 
		}
		
		if(A[i] != A[i + 1])//数值末尾，将旧队列弹出，计数，将旧队列入队。 
		{
			//cout << "000" << endl;
			while(!Q.empty()) 
			{
				//接不下去的队列需要统计答案。
				ans = min(ans,Q.top().len); 
				Q.pop();
			}
			while(!Tmp.empty())	
			{
				que tmp = Tmp.top();
				Q.push(tmp);
				//printf()
				Tmp.pop();
			}
		}
	} 
	while(!Q.empty())	//最后统计一次答案 
	{
		ans = min(ans,Q.top().len);
	//	printf("%d\n",Q.top().len);
		Q.pop();
	}
	cout << ans << endl;
}
int main()
{
	freopen("luogu4447.in","r",stdin);
	freopen("luogu4447.out","w",stdout);
	Read();
	Solve();
	return 0;
}
