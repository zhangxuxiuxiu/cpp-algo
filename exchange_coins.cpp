#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// exchange 100 coins from collection(1,2,5,10,20,50,100)
using namespace std;

int exchangeCounts(vector<int> const& coins, int k){
	auto counts =vector<vector<int64_t>>(coins.size(),vector<int64_t>(k+1,0));	

	for( auto i=0; i<coins.size(); ++i){
		auto c = coins[i];
		for( auto j=1; j<k+1; ++j){
			// not use current coins
			auto upper = 0;
			if (i>0){
				upper = counts[i-1][j];
			}
			// use current coins
			auto left = 1;
			if (j > c){
				left = counts[i][j-c];
			} else if (j<c){
				left = 0;
			}
			counts[i][j] = upper+left;
		}
	}
	//for(auto row : counts){
	//	copy(row.begin()+1, row.begin()+11, ostream_iterator<int64_t>(cout,"\t"));
	//	cout << endl;
	//}
	return counts[coins.size()-1][k];
}

int impl2(vector<int> const& coins, vector<vector<int64_t>> & counts, int coinId, int k){
	if(counts[coinId][k]==0){
		auto v = 0;
		if(k==0){
			v = 1;
		} else if(coinId==0){
			v = (k%coins[coinId]==0);
		} else {
			auto c = coins[coinId];
			for( auto j=0; j*c<=k; ++j){
				v += impl2(coins, counts, coinId-1, k-j*c);
			}
		}

		counts[coinId][k] = v;
	}
	return counts[coinId][k];
}

int exchangeCounts2(vector<int> const& coins, int k){
	auto counts =vector<vector<int64_t>>(coins.size(),vector<int64_t>(k+1,0));	
	return impl2(coins, counts, coins.size()-1, k);
}

int main(int argc, char* argv[]){
	if(argc==1){
		// 7.60s user 0.01s system 99% cpu 7.617 total
		for(auto k=100;k<10000; ++k){
			auto e = exchangeCounts({1,2,5,10,20,50,100},k);
			//cout << "final exchanges:" << e << endl;
		}
	} else {
		//0.20s user 0.00s system 94% cpu 0.213 total
		for(auto k=100;k<10000; ++k){
			auto e2 = exchangeCounts2({1,2,5,10,20,50,100},100);
		}
		//cout << "final exchanges:" << e2 << endl;
	}
	return 0;
}
