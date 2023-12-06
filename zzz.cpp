// 输入：3
// 输出：1，2，3，12，13，23，123

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int log10(int n){
	int k =0;
	while(n>0){
		n/=10;
		++k;
	}
	return k;
}

void append(vector<int>& r, vector<int> const& k){
	for(auto i : k) r.push_back(i);
}

vector<int> impl(vector<int>  prefix, int * arr,int from, int to, int cnt){	
	if(cnt<1 || from>=to || cnt > to - from) return prefix;

	if(cnt == to - from){ //  all values make a number	
		int n =0;
		for(int i=from; i<to; ++i) n=n*10+arr[i];
		for(int& k : prefix) k = k*10+n;
		if(prefix.empty()) prefix.push_back(n);
		return prefix;
	}

	vector<int> r;
	append(r, impl(prefix, arr, from+1, to, cnt)); // not consider arr[from]	
		
	for(int& k : prefix) k= k*10+arr[from]; // consider arr[from] 
	if(prefix.empty()) prefix.push_back(arr[from]);
	append(r, impl(prefix, arr, from+1, to, cnt-1)); 
	return r;
}

vector<int> algo(int n){  // 2^n -1 
	if(n<1) return {};

	auto arr = new int[n];
	for(int i=0; i<n; ++i){
		arr[i] = i+1;
	}

	vector<int> rets;	
	
	for(int i=0; i<n; ++i){
		append( rets, impl({}, arr, 0, n, i+1));	
	}	
	return rets;
}

int main(){

	auto r = algo(4);	
	std::copy(r.begin(), r.end(), std::ostream_iterator<int>(cout, "\t")) ;

	return 0;
}
