using namespace std;
#include<bits/stdc++.h>
#define MAX 1000

class que{
	private:
		int* arr;
		int front, rear, number;
		
	public:
		que(){
			arr=new int[MAX];	front=0;	rear=-1;	number=0;
		}
		~que(){
			delete[] arr;
		}
		void push(int num);
		void pop();
		void Front();
		void back();
		void empty();
		void size();
			
};

void que::push(int num){
	if(number>MAX)
		return;
	arr[++rear % MAX] = num;
	number++;
}
void que::pop(){
	if(number<=0){
		cout<<-1<<endl;
		return;
	}
	cout<<arr[front++%MAX]<<endl;
	number--;
}
void que::back(){
	if(number<=0){
		cout<<-1<<endl;
		return;
	}
	cout<<arr[rear%MAX]<<endl;
}
void que::empty(){
	if(number<=0){
		cout<<1<<endl;
		return;
	}
	else{
		cout<<0<<endl;
		return;
	}
}
void que::Front(){
	if(number<=0){
		cout<<-1<<endl;
		return;
	}
	cout<<arr[front%MAX]<<endl;
}
void que::size(){
	cout<<number<<endl;
}
int main(){
	int ans_num=0,v=0;
	que q;
	string fun;
	cin>>v;
	for(int i=0;i<v;i++){
		cin>>fun;
		if(fun=="push"){
			cin>>ans_num;
			q.push(ans_num);
		}
		else if(fun=="pop")
			q.pop();
		else if(fun=="front")
			q.Front();
		else if(fun=="back")
			q.back();
		else if(fun=="empty")
			q.empty();
		else if(fun=="size")
			q.size();
	}
	return 0;
}
