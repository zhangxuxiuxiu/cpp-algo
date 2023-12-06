#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxStone(vector<int> const& stones){
	auto diff = stones;
	auto n = stones.size();
	for (auto i=0; i< n-1; ++i){
		for(auto j=0; j < n-i-1; ++j){
			// dp[l][h] = max( stones[l]-dp[l+1][h], stones[h]-dp[l][h-1])    
			// (l,h) -> (j, i+j+1)
			// dp[l][h] = diff[l]
			diff[j] = max( stones[j]-diff[j+1], stones[i+j+1]-diff[j] );
		}
		copy(diff.begin(), diff.begin() + n -i-1, ostream_iterator<int>(cout, "\t")); 
		cout << '\n';
	}
	return diff[0];
}

int main(){
	cout << maxStone({3,4,2,5}) << '\n';
	return  0;
}
