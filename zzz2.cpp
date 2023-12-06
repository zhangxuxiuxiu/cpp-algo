#include <vector>
#include <iostream>

// 输入：3
// 输出：1，2，3，12，13，23，123

using namespace std;

void impl(vector<int>* digits ,int curIndex,int max, int cnt,int base){	
	if(cnt < 1){
		digits->push_back(base);
		return;
	}
	if (curIndex > max){
		return;
	}
	impl(digits, curIndex+1, max, cnt-1, base*10+curIndex);
	impl(digits, curIndex+1, max, cnt, base);
	return;
}

vector<int> populate(int n){
	vector<int> digits{};
	for(int i=0; i<n; ++i){
		impl(&digits,1,n,i+1,0);	
	}
	return move(digits);
} 


int main(){
	for(int k: populate(3)){
		cout << '\t' << k ;
	}
	cout << endl;
	return  0;
}

