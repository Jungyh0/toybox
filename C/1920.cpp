#include<bits/stdc++.h>
#define MAX 100000
using namespace std;
bool saerch_num(int num);
int arr1[MAX];
int n,m,num=0;
bool x=true;

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n;

	for(int i=0;i<n;i++){
		cin>>num;
		arr1[i]=num;
	}

	sort(arr1,arr1+n);
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>num;
		x=saerch_num(num);
		cout<<x<<"\n";
	}
	return 0;
}

bool saerch_num(int num){
	int low=0, high=n-1;	bool found=false;
	while(low<=high){
		int mid=low+(high-low)/2;
		if(num==arr1[mid]){
			found=true;
			break;
		}
		else if(num>arr1[mid]){
			low=mid+1;
		}
		else if(num<arr1[mid]){
			high=mid-1;
		}
	}
	return found;
}
