#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1->a, 2>b, ... 26->z ==> 111->(aaa,ka,ak)

int compose( std::string literal){
	if (literal.empty()){
		return 0;
	}
	vector<int> composes(literal.size()+1,0);
	composes[0] = 1;
	composes[1] = 1;
	for(int i=1; i<literal.size();++i){
		auto cur = composes[i];
		if (literal[i-1] == '1' || (literal[i-1] == '2' && literal[i]<='6')){
			cur += composes[i-1];
		}
		composes[i+1] = cur;
	}
//	copy(composes.begin(), composes.end(), ostream_iterator<int>(cout,"\t"));
//	cout << '\n';
	return composes[literal.size()];
}

int compose2( std::string literal){
	if (literal.empty()){
		return 0;
	}
	int a  = 1, b  = 1;
	for(int i=1; i<literal.size();++i){
		if (literal[i-1] == '1' || (literal[i-1] == '2' && literal[i]<='6')){
			int c = a+b;
			a = b;
			b = c;
		} else {
			a = b;
		}
	}
	return b;
}

int main(){
	cout << compose("111") << '\n';
	cout << compose("111126111") << '\n';
	cout << compose2("111") << '\n';
	cout << compose2("111126111") << '\n';
	return 0;
}
