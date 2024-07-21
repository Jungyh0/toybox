#include<bits/stdc++.h>
#define MAX 12000
using namespace std;
typedef pair<int,int> pii;

int parent[MAX];
int v,m,ans;
vector<pair<int, pii > >vec;

void input(){
	int num1,num2,num3;
	cin>>v>>m;
	for(int i=0;i<m;i++){
		cin>>num1>>num2>>num3;
		vec.push_back({num3,{num1,num2}});
	}
	sort(vec.begin(), vec.end());
}

int find_parent(int num){
	if(parent[num]==num)	return num;
	else	return parent[num]=find_parent(parent[num]);
}

bool same_parent(int num1, int num2){
	num1=find_parent(num1);
	num2=find_parent(num2);
	if(num1==num2) return true;
	
	return false;
}
void Union(int num1,int num2){
	num1=find_parent(num1);
	num2=find_parent(num2);
	if(num1!=num2){
		parent[num2]=num1;
	}	
}

void solution(){
	for(int i=1;i<=v;i++){
		parent[i]=i;
	}
	for(int i=0;i<m;i++){
		if(same_parent(vec[i].second.first,vec[i].second.second)==false){
			Union(vec[i].second.first,vec[i].second.second);
			ans=ans+vec[i].first;
			}

	}
}

int main(){

	input();
	solution();
	cout << ans << endl;
	return 0;
}
