#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// wrong
double minCost(vector<int> const& quality, vector<int> const& wage, int k){
	int n = quality.size();
	float avgWage;
	vector<float> maxAvg(k),maxAvgPre(k);
	vector<int> sumQuality(k), sumQualityPre(k);

	int minWage = INT_MAX;
	for(auto i =0 ; i < n; ++i){
		avgWage = float(wage[i]) / quality[i];
		for(auto j =0 ; j < k && j<=i; ++j){
			if(j==0){
				if(wage[i] < minWage){
					minWage = wage[i];
					maxAvg[0] = avgWage;
					sumQuality[0] = quality[i];
				} else {
					maxAvg[0] = maxAvgPre[0];
					sumQuality[0] = sumQualityPre[0];
				}
			} else if(i<=j){
				maxAvg[j] = max(avgWage, maxAvgPre[j-1]);
				sumQuality[j] += sumQualityPre[j-1] + quality[i];
			} else {
				auto sumWage = max(maxAvgPre[j-1], avgWage) * (sumQualityPre[j-1] + quality[i]);
				if(sumWage < maxAvgPre[j] * sumQualityPre[j]){
					maxAvg[j] = max(maxAvgPre[j-1], avgWage); 
					sumQuality[j] =  (sumQualityPre[j-1] + quality[i]); 
				} else {
					maxAvg[j] = maxAvgPre[j];
					sumQuality[j] = sumQualityPre[j];
				}
			}
			cout << '[' <<maxAvg[j] << ',' << sumQuality[j] << ']' << '\t';
	 	}
		cout << '\n';
		swap(maxAvg, maxAvgPre);
		swap(sumQuality, sumQualityPre);
	}

	return maxAvgPre[k-1] * sumQualityPre[k-1];
}

// wrong
double minCost2(vector<int> const& quality, vector<int> const& wage, int k){
	int n = quality.size();
	float avgWage;
	vector<float> maxAvg(k+1),maxAvgPre(k+1);
	vector<int> sumQuality(k+1), sumQualityPre(k+1);

	for(auto i =0 ; i < n; ++i){
		avgWage = float(wage[i]) / quality[i];
		for(auto j =1 ; j <= k && j<=i+1; ++j){
			if(i+1<=j || max(maxAvgPre[j-1], avgWage) * (sumQualityPre[j-1] + quality[i]) < maxAvgPre[j] * sumQualityPre[j]){
				maxAvg[j] = max(maxAvgPre[j-1], avgWage); 
				sumQuality[j] =  (sumQualityPre[j-1] + quality[i]); 
			} else {
				maxAvg[j] = maxAvgPre[j];
				sumQuality[j] = sumQualityPre[j];
			}
			cout << '[' <<maxAvg[j] << ',' << sumQuality[j] << ']' << '\t';
	 	}
		cout << '\n';
		swap(maxAvg, maxAvgPre);
		swap(sumQuality, sumQualityPre);
	}

	return maxAvgPre[k] * sumQualityPre[k];
}

double minCost3(vector<int> const& quality, vector<int> const& wage, int k){
	auto n = quality.size();
	vector<pair<float, int>> avgWageQu(n);
	for(auto i=0; i<n; ++i){
		avgWageQu[i] = {float(wage[i])/quality[i], quality[i]};
	}
	sort(avgWageQu.begin(), avgWageQu.end());

	vector<int> qv;
	qv.reserve(k);
	priority_queue<int> q(less<int>(), move(qv));
	auto sumQu = 0;
	float minCost = 0;
	for(auto& wq : avgWageQu){
		if(q.size()<k){
			q.push(wq.second);	
			sumQu += wq.second;
			if(q.size()==k){
				minCost = sumQu * wq.first;
			}
		} else if(wq.second<q.top()) {
			sumQu += wq.second - q.top();
			q.pop();	
			q.push(wq.second);
			minCost = min(sumQu*wq.first, minCost);
		}
	}
	return minCost;
}

int main(){
	vector<int> quality={10,20,5};
	vector<int> wage={ 70,50,30};
	cout << minCost(quality, wage, 2) << endl;
	cout << minCost2(quality, wage, 2) << endl;
	cout << minCost3(quality, wage, 2) << endl;
	return 0;
}
