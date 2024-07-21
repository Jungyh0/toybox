#include<bits/stdc++.h>
#include<iostream>
using namespace std;
#define MAX 20010
#define INF 1e9

typedef pair<int, int> pii;

int v,e,start;
vector<pii> vec[MAX];
int Distance[MAX];

void input(){
	int num1,num2,num3;
	cin>>v>>e>>start;
	for(int i=0;i<e;i++){
		cin>>num1>>num2>>num3;
		vec[num1].push_back(make_pair(num2,num3));
	}
	for(int i=1;i<v+1;i++)
		Distance[i]=INF;
}

void solution(){
	int index, dist;
	priority_queue<pii> pq;
	pq.push(make_pair(0,start));
	Distance[start]=0;
	
	while(!pq.empty()){
		index=pq.top().second;
		dist=-pq.top().first;
		pq.pop();
		
		if(Distance[index]<dist){
			continue;
		}
		
		for(int i=0;i<vec[index].size();i++){
			int next_index=vec[index][i].first;
			int next_dist=vec[index][i].second;
			
			if(Distance[next_index]>dist+next_dist){
				Distance[next_index]=dist+next_dist;
				pq.push(make_pair(-Distance[next_index],next_index));
			}
		}
	}
	
	for(int i=1;i<v+1;i++){
		if(Distance[i]==INF)cout<<"INF"<<"\n";
		else cout<<Distance[i]<<"\n";
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solution();
}
