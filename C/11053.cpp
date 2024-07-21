#include<bits/stdc++.h>
using namespace std;
#define MAX 1010

int arr1[MAX], dp[MAX];
int n;

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }
}

void solution() {
    int lis_length = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1; // 자기 자신만으로 구성된 부분 수열의 길이는 1
        for (int j = 0; j < i; j++) {
            if (arr1[i] > arr1[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        lis_length = max(lis_length, dp[i]);
    }
    for (int i =0;i < n; i++){
    	cout << "dp[" << i << "]: " << dp[i] << " ";
	}
    cout << "\n" << lis_length << endl;
}

int main() {
    input();
    solution();
    return 0;
}

