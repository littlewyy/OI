#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5;
int n,ans,A[MAXN];
struct que
{
	int las,len;
	bool operator < (const que &a)const//С���� 
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
	//���̣�����ÿһ����ֵ����ÿһ����ֵ�Ľ�β����ͳһ���
	A[n + 1] = A[n] + 1 , ans = n + 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		//����ǰ���������ֵ�������ӵĶ��� 
		while((!Q.empty()) && Q.top().las != (A[i] - 1))	
		{
			ans = min(ans,Q.top().len);
			Q.pop();//֮ǰ��ֵ�Ķ��� 
		} 
		if(!Q.empty())//�������������������  
		{
			que tmp = Q.top();
			tmp.len ++ , tmp.las ++;
			Tmp.push(tmp);//��ӡ��� 
			Q.pop(); 
		}
		else//�������в�����������ӣ��Դ�����   
		{
			que tmp;
			tmp.len = 1 , tmp.las = A[i];
			//printf("%d %d\n",i,A[i]);
			Tmp.push(tmp);//������ʱ���� 
		}
		
		if(A[i] != A[i + 1])//��ֵĩβ�����ɶ��е��������������ɶ�����ӡ� 
		{
			//cout << "000" << endl;
			while(!Q.empty()) 
			{
				//�Ӳ���ȥ�Ķ�����Ҫͳ�ƴ𰸡�
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
	while(!Q.empty())	//���ͳ��һ�δ� 
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
