#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int factorial(int n){
	auto k =1;
	for(auto i=0;i < n; ++i){
		k*=(i+1);
	}
	return k;
}


vector<vector<int>> genN(int n){
	if(n == 1){
		return {{1}};
	}

	vector<vector<int>> result;
	auto subs =  genN(n-1);
	result.reserve(n*subs.size());
	for(auto& sub : subs){
		for(auto i=0; i<n;++i){
			vector<int> one;
			one.reserve(n);
			for(int j=0;j<i;++j){
				one.push_back(sub[j]);
			}	
			one.push_back(n);
			for(int j=i;j<n-1;++j){
				one.push_back(sub[j]);
			}	
			result.push_back(move(one));
		}
	}

	for(auto& v : result){
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
		cout << '\n';
	}

	return result;
}


void impl2(vector<int>& state, vector<bool>& used, int pos){
	auto n = used.size();
	if(pos == n){
		copy(state.begin(), state.end(), ostream_iterator<int>(cout, "\t"));
		cout << '\n';
		return;
	}

	// avaiable steps
	for(auto i=0; i<n; ++i){
		if(used[i]){
			continue;
		}	
		state[pos] = i+1;
		used[i] = true;
		impl2(state, used, pos+1);
		// restore state
		used[i] = false;
	}
}

void  genN2(int n){
	vector<int> state(n);
	vector<bool> used(n); 

	impl2(state, used, 0);
}

int main(){
	genN(4);
	cout << '\n';
	genN2(4);
	cout << '\n';

	auto k =1;
	auto i =0;
	for(;k<INT_MAX/(i+1); ++i){
		k*=(i+1);
	}
	cout << "max factorial int is "	<< i+1 << ", result is " << k << '\n';
	
	return 0;
}
