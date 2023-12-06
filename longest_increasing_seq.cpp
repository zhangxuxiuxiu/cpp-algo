#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int lis(vector<int>& seq){
	auto k = 0ul, n = seq.size();
	auto start = seq.begin();
	for(auto i=0; i<n; ++i){
		auto prefix = lower_bound(start, start + k, seq[i]);
		auto pos = prefix - start;
		if(pos >= k){
			++k;
			seq[pos] = seq[i];
		} else if(seq[i] < seq[pos]){
			seq[pos] = seq[i];
		}
	}
	copy(start, start+k, ostream_iterator<int>(cout, "\t"));
	cout << '\n';
	return k;
}

int lis2(vector<int> const& seq){
	auto n = seq.size();
	vector<int> incSeq;
	for(auto i=0; i<n; ++i){
		auto prefix = lower_bound(incSeq.begin(), incSeq.end(), seq[i]);
		if(prefix == incSeq.end()){
			incSeq.push_back(seq[i]);
		} else if(seq[i] < *prefix){
			*prefix  = seq[i];
		}
	}
	copy(incSeq.begin(), incSeq.end(), ostream_iterator<int>(cout, "\t"));
	cout << '\n';
	return incSeq.size();
}

int main(){
	vector<int> seq={10,9,1,2,8,7,11,3};
	cout << lis2(seq) << '\n';
	cout << lis(seq) << '\n';
	return 0;
}


