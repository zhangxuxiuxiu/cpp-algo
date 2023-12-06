#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// stock prices: [3,4,1,5], tx cnt: unlimited
int maxProfitX(vector<int> const& prices){
	if(prices.size()<2){
		return 0;
	}

	auto cur =0, low=prices[0], high=0, sum=0;
	while(cur < prices.size()){
		//find lower
		while(cur<prices.size()-1 && prices[cur] >= prices[cur+1]) ++cur;
		low=prices[cur++];
		if (cur >= prices.size()){
			break;
		}
		//find higher 
		while(cur<prices.size()-1 && prices[cur] <= prices[cur+1]) ++cur;
		high=prices[cur++];

//		cout << low << '\t' << high << '\n';
		sum += high-low;
	}
	return sum;
}

// stock prices: [3,4,1], tx cnt:1
int maxProfit1(vector<int> const& prices){
	int min = INT_MAX, profit=0;
	for(auto p : prices){
		if (p<min){
			min =p;
		}	
		if (profit < p-min){
			profit = p - min;
		}
	}
	return profit;
}

//// stock prices: [3,4,1,5], tx cnt:N
int maxProfitN(vector<int> const& prices, int k){
	vector<int> lws{};
	for(auto cur=0; cur<prices.size(); ++cur){
		// find low point	
		while(cur < prices.size()-1 && prices[cur]>=prices[cur+1]) ++cur;
		if( prices.size() - cur-1 < 1){ //less than 1 elements left
			break;
		}
		lws.push_back(prices[cur]);
		++cur;

		// find high point	
		while(cur < prices.size()-1 && prices[cur]<=prices[cur+1]) ++cur;
		lws.push_back(prices[cur]);
	}

	// less low-high intervals than $K
	if(2*k >= lws.size()){
		auto sum =0;
		for(auto idx=0; idx<lws.size(); idx+=2){
			sum += (lws[idx+1]-lws[idx]);
		}
		return sum;
	}

	// dynamic programming
	// matrix[i][j]: max profit with (i+1) intervals and (j+1) tx
	vector<vector<int>> matrix(k+1, vector<int>(lws.size()/2+1,0) );  
	for(auto idx=1; idx< k+1 ; ++idx){ // max tx cnt 
		for(auto j=1; j< lws.size()+1; ++j){ //  price pairs
			auto max=0;
			for(auto c=1; j>=c && idx-1<=j-c; ++c){
				// max( prices[j-c+1,j] + matrix[idx-1][j-c])
				max = std::max(max, (lws[j*2-1]-lws[j*2-c*2]) + matrix[idx-1][j-c]);
			}
			matrix[idx][j] = max; 
		}
	}
	return *max_element(matrix[k].begin(), matrix[k].end()); 
}

//// stock prices: [3,4,1,5], tx cnt:N
int maxProfitN2(vector<int> const& prices, int k){
	auto n = prices.size();
	// maxs[i][j] = max profile in prices[i~j];
	vector<vector<int>> maxs(n, vector<int>(n, 0)); 
	for(auto i=0; i<n; ++i){
		auto minV = INT_MAX; 
		for(auto j=i; j<n; ++j){
			minV = min(minV, prices[j]);	
			maxs[i][j] = prices[j] - minV;
		}
	}

	// second[i] = $round-th max profile in prices[0, i] 
	vector<int> first = maxs[0], second(n, 0);
	for(auto round=1; round<k; ++round){
		for(auto i=0; i<n; ++i){
			second[i] = first[i];
			for(auto j=1; j<=i; ++j){
				second[i] = max(second[i], first[j-1] + maxs[j][i]);
			}
		}
		swap(first, second);
	}

	return *max_element(first.begin(), first.end());
}

int maxProfit2(vector<int> const& prices){
	auto n = prices.size();
	vector<int> left(n), right(n);

        int min = INT_MAX, max = INT_MIN, lgap = INT_MIN, rgap = INT_MIN;
        for(auto i=0; i<n; ++i){
        	if(prices[i]<min){
        		min = prices[i];	
        	}	
        	left[i] = (lgap  = std::max(lgap, prices[i]-min));

		auto j = n -i -1;
        	if(prices[j]>max){
        		max = prices[j];	
        	}	
        	right[j] = (rgap  = std::max(rgap, max - prices[j]));
        }

	auto sum = INT_MIN; 
        for(auto i=1; i<n; ++i){
		sum = std::max(sum, left[i-1] + right[i]);	
	}

	return sum;
}

int main(){
	cout << maxProfit1({3,4,1,8}) << '\n';
	cout << maxProfitX({3,4,1,8}) << '\n';

	cout << maxProfit2({3,4,1,8,5,7}) << '\n';

	cout << maxProfitN({3,4,1,8}, 1) << '\n';
	cout << maxProfitN({3,4,1,8}, 2) << '\n';
	cout << maxProfitN({3,4,1,8}, 3) << '\n';
//	cout << maxProfitN({3,4,1,8,5,7}, 2) << '\n';

	cout << maxProfitN2({3,4,1,8}, 1) << '\n';
	cout << maxProfitN2({3,4,1,8}, 2) << '\n';
	cout << maxProfitN2({3,4,1,8}, 3) << '\n';
	cout << maxProfitN2({3,4,1,8,5,7}, 2) << '\n';

	return  0;
}
