#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
using namespace std;

int asendingN(vector<int> const& ratings, int m){
	auto n = ratings.size();
	vector<int> first(n,1), second(n,0);
	auto cnt = 0;
	for(auto i=0; i<m-1; ++i){
		for(auto j=0; j<n; ++j){
			second[j] = 0;
			for(auto k=0; k<j; ++k){
				if(ratings[k]<ratings[j]){
					second[j]+=first[k];
				}
			}
		}
		copy(second.begin(), second.end(), ostream_iterator<int>(cout, "\t"));
		cout << '\n';
		swap(first, second);
	}
		
	return accumulate(first.begin(), first.end(), 0, plus<int>());	
}

int main(){
	cout << asendingN({3,5,2,4,1,6}, 3) << '\n'; 
	return  0;
}
