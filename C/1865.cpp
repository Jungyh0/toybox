#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pill;
#define MAX 510
#define INF 1e9

int s, e, t, tc, n, m, w, start = 1;
vector<pair<int, pill> > vec;
int Distance[MAX];
string ans;

void input(){
	cin >> n >> m >> w;
			
	Distance[0] = 0;
	for (int i = 1; i <= n; i++) {
		vec.push_back(make_pair(0, make_pair(0, i)));
	}
		
	for (int i = 1; i <= n; i++){
		Distance[i] = INF;
	}
	
	for (int i = 0; i < m; i++){
		cin >> s >> e >> t;
		vec.push_back(make_pair(t, make_pair(s, e)));
		vec.push_back(make_pair(t, make_pair(e, s)));
	}
	
	for (int i = 0; i < w; i++){
		cin >> s >> e >> t;
		vec.push_back(make_pair(-t, make_pair(s, e)));
	}
}

void bellman(){
	int from, to, cost;
	
	for (int i =0; i <n-1; i++){
		for (int j = 0; j < vec.size(); j++){
			from = vec[j].second.first;
			to = vec[j].second.second;
			cost = vec[j].first;
			
			if (Distance[to] > Distance[from] + cost)
				Distance[to] = Distance[from] + cost;
		}
	}
	
	ans = "NO";
	
	for(int i = 0; i < vec.size(); i++){
		from = vec[i].second.first;
		to = vec[i].second.second;
		cost = vec[i].first;
			
		if (Distance[to] > Distance[from] + cost)
		{
			ans = "YES";
			break;
		}
	}
}

int main(){
	cin >> tc;
		
	while(tc--){
		vec.clear();
		input();
		bellman();
		cout << ans << "\n";
	}	
	return 0;
}
