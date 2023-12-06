#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

void NextPermutation(vector<int>& seq){
	int n = seq.size()-1;
	while(n>0 && seq[n-1]>seq[n]) --n;
	if(n==0){
		return;
	}
	cout << "n:seq[n]=>" << n << ":" <<  seq[n] << '\t';
//	auto gt = find_if( seq.rbegin(), seq.rend()+n, [&](int v){ return v > seq[n-1]; } ); 
	auto gt = upper_bound( seq.rbegin(), seq.rend()+n, seq[n-1]);//[&](int v){ return v > seq[n-1]; } ); 
	cout << "swap " << *gt << " " << seq[n-1] << '\t';
	swap( *gt, seq[n-1] );
	reverse(seq.begin()+n, seq.end());
//	copy(seq.begin(), seq.end(), ostream_iterator<int>(cout,"\t"));
	cout << '\n';

//	NextPermutation( seq );
}

int main(){
	vector<int> seq={4,3,2,1,5};
//1	3	2	4	5
	NextPermutation( seq );
	return 0;
}
