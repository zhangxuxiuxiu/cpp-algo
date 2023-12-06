#include <iostream>
#include <vector>

using namespace std;

void impl(int curPos, int leftDigits, int n, int base, std::vector<int>* arr){
	if (curPos >n+1 ){
		return; 
	}
	if (leftDigits == 0){
		arr->push_back(base);
		return;
	}
	impl(curPos+1,leftDigits-1,n, base*10+curPos, arr);
	impl(curPos+1,leftDigits,n, base, arr);
}

std::vector<int> populate(int n){
	std::vector<int> arr;
	for( auto i=0; i<n; ++i){
      		impl(1,i+1, n,0, &arr);
	}
	return arr;
}

// 3:  1,2,3,12,13,23,123

void add(std::vector<int> const& digits, int tmp, int index, int n, std::vector<int>*results){
	if (n <= 0){
		results->push_back(tmp);	
		return;
	}
	if(index >=digits.size()){
		return;
	}
	add(digits, tmp*10+digits[index], index+1, n-1, results);
	add(digits, tmp, index+1, n, results);
}

std::vector<int> populate2(int n){
	std::vector<int> digits(n);
	for(auto i=0; i<n; ++i){
		digits[i] = i+1;
	}

	std::vector<int> results;
	results.reserve(2^n-1);
	for(auto i=0; i<n; i++){
		add(digits, 0,0,i+1, &results);
	}
	return results;
}

void orderImpl(string &alpha, int pos, vector<string>& result){
	if(pos == alpha.size()){
		result.push_back(alpha);
	} else {
		auto n = alpha.size();
		for(auto x=pos;x<n; ++x){
			swap(alpha[pos], alpha[x]);
			orderImpl(alpha, pos+1, result);
			swap(alpha[x], alpha[pos]);
		}
	}
}

// abc acb bac bca cab cba
vector<string> order(int n){
	string alpha(n, '\0');
	for(auto i=0; i<n; ++i){
		alpha[i] = 'a'+i;
	}
	vector<string> result;
	orderImpl(alpha, 0, result);
	return result;
}


int main(int argc, char* argv[]){
	auto arr =  populate(3);
	for (auto x : arr){
		std::cout << x << '\t';
	} 
	std::cout << '\n';

	auto arr2 =  populate2(3);
	for (auto x : arr2){
		std::cout << x << '\t';
	} 
	std::cout << '\n';

	for (auto x : order(3)){
		std::cout << x << '\t';
	} 
	std::cout << '\n';



	return 0;
}
