#include<bits/stdc++.h>
using namespace std;
#define MAX 32010

int v,e,num1,num2,Index=0;
vector<int> vec[MAX];
int visited[MAX];
priority_queue<int> q;

void input(){
	cin>>v>>e;
	
	for(int i=0;i<e;i++){
		cin>>num1>>num2;
		vec[num1].push_back(num2);
		visited[num2]++;
	}
	
	for (int i = 1; i <= v; i++) {
        if (visited[i] == 0) {
            q.push(-i);
        }
    }
	
	while(!q.empty()){
		int node=-q.top();
		cout<<node<<"\n";	q.pop();
		for(int i=0;i<vec[node].size();i++){
			int Index=vec[node][i];
			if(Index>0){
				visited[Index]--;	
				if(visited[index]==0)	q.push(-Index);
			}
		}		
	}
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	input();
	return 0;
}
