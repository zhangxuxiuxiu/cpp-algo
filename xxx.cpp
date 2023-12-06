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

vector<int> impl(vector<int>  postfix, int * arr, int len, int cnt){	
	if(cnt<1 || cnt > len) return postfix;

	if(cnt == len){ //  all values make a number	
		int n =0;
		for(int i=0; i<len; ++i) n=n*10+arr[i];
		for(int& k : postfix) k = n*pow(10, log10(k))+k;
		if(postfix.empty()) postfix.push_back(n);
		return postfix;
	}

	vector<int> r;
	append(r, impl(postfix, arr, len-1, cnt)); // not consider arr[len-1]	
		
	for(int& k : postfix) k=arr[len-1]*pow(10, log10(k))+k; 
	if(postfix.empty()) postfix.push_back(arr[len-1]);
	append(r, impl(postfix, arr, len-1, cnt-1)); // consider arr[len-1]
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
		append( rets, impl({}, arr, n, i+1));	
	}	
	return rets;
}

int main(){

	auto r = algo(4);	
	std::copy(r.begin(), r.end(), std::ostream_iterator<int>(cout, "\t")) ;

	return 0;
}
