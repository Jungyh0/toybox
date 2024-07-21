#include<bits/stdc++.h>
using namespace std;


int calc(int n, int m, int k, vector<vector<char> > &vec1, int x, int y){
	int total = 0, max_value = 0;
	char max_key = 0;
	map<char, int> cnt;
	
	for (int i = x; i < n; i += k){
		for (int j = y; j < m; j += k){
			cnt[vec1[i][j]]++;
		}
	}
	
	for (map<char, int>::iterator it = cnt.begin(); it != cnt.end(); it++){
		total += it->second;
		if (it->second > max_value){
			max_value = it->second;
			max_key = it->first;
		}
	}
	
	for (int i = x; i < n; i += k){
		for (int j = y; j < m; j += k){
			vec1[i][j] = max_key;
		}
	}
	
	return total - max_value;
}

void solve(){
	int n, m, k, ans = 0;
	cin >> n >> m >> k;
	vector<vector<char> > vec (n, vector<char>(m) );
	
	for (int i = 0; i < n; i ++){
		for (int j = 0; j < m; j ++){
			cin >> vec[i][j];
		}
	}
	
	for (int i = 0; i < n; i ++){
		for (int j = 0; j < m; j ++){
			ans += calc(n, m, k, vec, i, j);
		}
	}
	
	cout << ans << "\n";
	
	for (int i = 0; i < n; i ++){
		for (int j = 0; j < m; j ++){
			cout << vec[i][j];
		}
		cout << "\n";
	}
}

int main(){
	solve();
}
