#include <iostream>
#include <string>
#include <vector>

using namespace std;
// ".", "*", a-z
// aaab  b*a*b 
bool match(string const& s, string const& p){
	return false;	
}

vector<int> build(string const& p){
	auto n = p.size();
	vector<int> lps(n);
	auto len = 0, i = 1;
	while(i<n){
		if(p[i]== p[len]){
			lps[i++] = ++len; 
		} else if(len!=0){
			len = lps[len-1];	
		} else{
			++i;
		}
	}

	return move(lps);
}

bool kmp(string const& s, string const& p){
	auto back = build(p);
	auto spos =0ul, ppos = 0ul, sn=s.size(), pn=p.size();

	while(spos<sn && ppos < pn){
		if(s[spos]==p[ppos]){
			++spos; ++ppos;
			if(ppos==pn){
				ppos = back[ppos-1];
				return true;
			}
		} else if(ppos==0){
			++spos;
		} else {
			ppos = back[ppos];
		}
	}
	return false;
}

int main(){
	for(auto lps : {build("AABAACAABAA"),build("AAACAAAAAC")}){
		copy(lps.begin(), lps.end(), ostream_iterator<int>(cout, "\t"));
		cout << endl;
	}

	cout << boolalpha << kmp("ABABDABACDABABCABAB","ABABCABAB") << '\n';
	
	return 0;
}
