#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// s contains a full random order of dict
// "aaaa",{"a","a",,"a"} => {0,1}
// "abcdcab", {"a","b","c"} => {0,4}
// solution: sliding window
vector<int> match(string const& s, vector<string> const& dict){
	auto n = dict.size(), m = dict[0].size(), l = s.size();

	vector<int> indexes;
	for(auto i=0; i<m && i+m*n <= l; ++i){
		unordered_map<string,int16_t> diff; 
		for(auto j=0; j<n; ++j){
			++diff[dict[j]];
		}
		for(auto j=0; j<n; ++j){
			auto w = s.substr(i+j*m,m);
			auto& v = diff[w];
			if(--v==0){
				diff.erase(w);	
			}
		}
		if(diff.empty()){
			indexes.push_back(i);
		}
			
		for(auto j=0; i+m*(n+j+1)<=l; ++j){
			// add substr(i+m*(n+j),m)
			auto w = s.substr(i+m*(n+j),m);
			if(++diff[w]==0){
				diff.erase(w);
			}
			// remove substr(i+m*j,m)
			w = s.substr(i+j*m,m);
			if(--diff[w]==0){
				diff.erase(w);	
			}
			if(diff.empty()){
				indexes.push_back(i+(j+1)*m);
			}
		}
	}

	return  indexes;
}

template<class T>
void print(vector<T> vec){
	copy(vec.begin(), vec.end(), ostream_iterator<T>(cout, "\t"));
	cout << '\n';
}

int main(){
	print(match("aaaa",{"a","a","a"}));	
	print(match("abcadcab",{"a","b","c"}));	

	return  0;
}
