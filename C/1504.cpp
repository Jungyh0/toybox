#include<bits/stdc++.h>
#define MAX 810
#define INF 1e15
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pill;

ll v, e, v1, v2, start=1;
ll ans=INF;
vector<pill> vec[MAX];
ll Distance1[MAX], Distance2[MAX], Distance3[MAX];

void input(){
	ll node1,node2,dist;
	
	cin>>v>>e;
	for(int i=0;i<e;i++){
		cin>>node1>>node2>>dist;
		vec[node1].push_back(make_pair(node2,dist));
		vec[node2].push_back(make_pair(node1,dist));
	}
	cin>>v1>>v2;
}

void dij(ll start, ll Distance[]){
	priority_queue<pill> pq;
	ll Index, new_dist;
	
	pq.push(make_pair(0, start));
	Distance[start]=0;
	
	while(!pq.empty()){
		ll next_index;
		ll next_dist;
		Index = pq.top().second;
		new_dist = -pq.top().first;
		pq.pop();
		
		if(Distance[Index]<new_dist)
			continue;
		for(int i = 0; i < vec[Index].size(); i++){
			next_index = vec[Index][i].first;
			next_dist = vec[Index][i].second;
			
			if(Distance[next_index] > next_dist + new_dist){
				Distance[next_index] = next_dist + new_dist;
				pq.push(make_pair(-Distance[next_index], next_index));
			}	
		}
	}
}

void soiution(){
	ll path1, path2;
	
	for(int i = 1; i < v+1; i++){
		Distance1[i] = INF;
		Distance2[i] = INF;
		Distance3[i] = INF;
	}
	dij(start, Distance1);
	dij(v1, Distance2);
	dij(v2, Distance3);
	
	path1 = Distance1[v1] + Distance2[v2] + Distance3[v];
	path2 = Distance1[v2] + Distance3[v1] + Distance2[v];
	
	if(path1 != INF || path2 != INF)
		ans = min(path1, path2);
	
	if(ans >= INF)
		ans=-1;
		
	cout << ans << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	soiution();
	return 0;
}
