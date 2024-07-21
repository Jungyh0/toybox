#include<bits/stdc++.h>
#define MAX 10000
using namespace std;

class sta{
private:
	int top,number;
	int* arr;
		
public:
	sta(){
		arr=new int[MAX];	top=-1;	number=0;
	}
	~sta(){
		delete[] arr;
	}
	void push(int num);
	void pop();
	void size();
	void empty();
	void Top();
};

void sta::push(int num){
	if(number>=MAX){
		return;
	}
	arr[++top]=num;
	number++;
}
void sta::pop(){
	if(number<=0){
		cout<<-1<<endl;
		return;
	}
	cout<<arr[top--]<<endl;
	number--;
}
void sta::size(){
	cout<<number<<endl;
}
void sta::Top(){
	if(number<=0){
		cout<<-1<<endl;
		return;
	}
	cout<<arr[top%MAX]<<endl;
}
void sta::empty(){
	if(number<=0){
		cout<<1<<endl;
		return;
	}
	cout<<0<<endl;
}

int main(){
	int ans_num=0, v=0;
	string fun;
	sta s;
	
	cin>>v;
	for(int i=0;i<v;i++){
		cin>>fun;
		if(fun=="push"){
			cin>>ans_num;
			s.push(ans_num);
		}
		else if(fun=="pop")
			s.pop();
		else if(fun=="size")
			s.size();
		else if(fun=="top")
			s.Top();
		else if(fun=="empty")
			s.empty();
	}
}
