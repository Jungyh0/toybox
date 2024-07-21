#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;

queue<int> q;
vector<int> vec[1001];
ll visited[10001];
ll visited_bfs[10001];


void dfs(int V);
void bfs(int V);

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll N,M,V,num1,num2;
    cin>>N>>M>>V;
    for(int i=0;i<M;i++){
    	cin>>num1>>num2;
    	vec[num1].push_back(num2);
    	vec[num2].push_back(num1);
	}

	dfs(V);
    cout<<endl;
    bfs(V);
    return 0;
}
void dfs(int V){
	if(visited[V]==1){
		return;
	}
	visited[V]=1;	
	cout<<V<<" ";
	for(int i=0;i<vec[V].size();i++){
		int x=vec[V][i];
		dfs(x);
	}
}

void bfs(int V)
{
    visited_bfs[V]=1;
    q.push(V);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        cout<<x<<" ";
        for(int i=0;i<vec[x].size();i++){
            int y=vec[x][i];
            if(!visited_bfs[y]){
                visited_bfs[y]=1;
                q.push(y);
            }
        }
    }
}
