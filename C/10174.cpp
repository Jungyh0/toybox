#include<bits/stdc++.h>
using namespace std;
int counter = 0;
string input_str;
bool check = true;

bool ex(string str){
	check = true;
	int num = str.length();
	for (int i = 0; i < num / 2; i++){
		if (str[i] != str[num - i - 1]){
			check = false;
			continue;
		}
	}
	return check;
}

void input(){
	for (int i = 0; i < counter; i++){
		getline (cin, input_str);
		for (int j = 0; j < input_str.length(); j++){
			if (input_str[j] >= 'A' && input_str[j] <= 'Z'){
				input_str[j] = input_str[j] - 'A' + 'a';
			}
		}
		check = ex(input_str);
		if (check == true)
			cout << "YES" << "\n"; 
		else
			cout << "NO" << "\n"; 
	}
}

int main(){
	cin >> counter;
	cin.ignore();
	input();
}
