#include<bits/stdc++.h>
using namespace std;
#define MAX 250010

int n = 0, num_check = 0, number = 1;
int num[MAX];

void input(){
	cin >> n;
	
	for (int i = 0; i < n; i++){
		cin >> num[i];	
	}
}

void solution(){
	input();
	
	for (int i = 0; i < n; i++){
		if (num[i] != number){
			num_check++;
		}
		else if (num[i] == number){
			number++;
		}
	}
	
	cout << num_check;
}

int main(){
	solution();
}
