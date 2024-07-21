#include<bits/stdc++.h>
using namespace std;

int n, m, k, ans = 0;

int calc(int n, int m, vector<vector<char> > &vec, int k, int x, int y){
	map<char, int> cnt;
	int max_value = 0, total_calc = 0, total = 0;	char max_key = 0;
	
	for (int i = x; i < n; i += k){
		for (int j = y; j < m; j += k){
			cnt[vec[i][j]] ++;
		}
	}

	for (map<char, int>::iterator it = cnt.begin(); it !=  cnt.end(); it++){
		total += it->second;
		if (it->second > max_value) {
    		max_value = it->second;
    		max_key = it->first;
   		}
	}
	
	for (int i = 0; i < k; i += k){
		for (int j = 0; j < k; j += k){
			vec[i][j] = max_key;
		}
	}
	
	total_calc = total - max_value;
	
	return total_calc;
}

void solve(){
	cin >> n >> m >> k;
	vector<vector<char> > vec1 (n, vector<char>(m) );
	
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			cin >> vec1[i][j];
		}
	}
	
	for (int i = 0; i < k; i ++){
		for (int j = 0; j < k; j ++){
			ans += calc(n, m, vec1, k, i, j);
		}
	}
	
	 cout << ans << "\n";
	
	for (int i = 0; i < n; i++) {
    	for (int j = 0; j < m; j++) {
     		cout << vec1[i][j];
    	}
  }	
}


int main(){
	solve();
	return 0;
}
