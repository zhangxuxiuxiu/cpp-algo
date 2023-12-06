#include <iostream>
#include <string>

using namespace std;

bool substr(string e, string s){
	auto i=0ul, n=s.size();
	for( auto c : e){
		while(i<n && s[i]!=c ) ++i;
		if(i==n){
			return false;
		}
	}
	return true;
}

int impl(string const& e, string const& s, int epos, int spos){
	if(epos==e.size()){
		return spos<=s.size()? 1 : 0;
	}

	auto cnt = 0;
	for(; s.size()-spos >= e.size()-epos && spos<s.size(); ++spos){
		while(s[spos]!=e[epos] && spos<s.size()) ++spos;
		cnt +=impl(e,s,epos+1, spos+1);
	}
	return cnt;
}

int substrs(string e, string s){
	return impl(e,s,0,0);
}

int main(){
	auto e ="abc", s ="aiajbdbc";
	cout << e << " -> " << s << '\n';
	cout << substr(e, s) << '\n';
	cout << substrs(e, s) << '\n';

	return 0;
}
