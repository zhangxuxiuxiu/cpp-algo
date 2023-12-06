#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void impl(vector<string>& results,string& state,int pos, int lefts, int rights){
	if((lefts | rights) == 0){
		results.push_back(state);
		return;
	}
	if(lefts>0){
		state[pos] = '(';
		impl(results, state, pos+1, lefts-1, rights);
	}
	if(lefts<rights){
		state[pos] = ')';
		impl(results, state, pos+1, lefts, rights-1);
	}
}

// vp = (vp)vp || ""
vector<string> genParentheses(int n){
	string state(n*2,' ');
	auto lefts =n, rights = n;
	vector<string> results;
	impl(results, state, 0, lefts, rights);
	return results;
}

string maxValidParenthese(string s){
	auto n = s.size();
	vector<vector<bool>> grid(n, vector<bool>(n));
	auto l=0, len =0;
	for(int i=n-1; i>=0; --i){
		if(s[i] != '('){
			for(auto j=i; j<n; ++j){
				grid[i][j] = false;
			}
			continue;
		} 

		for(int j=i+1; j<n; ++j){
			if((j-i)%2!=1 || s[j]!=')'){
				grid[i][j] = false;
				continue;
			}

			// ($vp)
			if(j==i+1 || grid[i+1][j-1]){
				grid[i][j] = true;
				if(2>len){
					len = 2; 
					l = i;	
				}
				continue;
			}
			// $vp$vp
			for(auto k=i+1; k<j; k+=2){
				if(grid[i][k] && grid[k+1][j]){
					grid[i][j] = true;
					if(j-i+1>len){
						len = j-i+1;
						l = i;	
					}
					break;
				}
			}
		}
	}
	return s.substr(l,len);
}

// time(n), space(n)
int maxValidParenthese2(string s){
	auto n= s.size(), len =0ul;
	vector<int16_t> dp(n,-1);
	stack<int16_t> stk;
	for(auto i=0; i<n; ++i){
		if(s[i]=='('){
			stk.push(i);
		} else { // ')'
			if(!stk.empty()){
				auto start = stk.top();
				stk.pop();
				if(start>0 && dp[start-1]!=-1){
					start = dp[start-1];
				}
				dp[i] = start;
				len = max(int(len), i-start+1);	
			} 
		} 
	}
	return len;
}

// time(n), 0.1*space(n)
int maxValidParenthese3(string s){
	auto n= s.size(), len =0ul;
	stack<int16_t> stk;
	vector<pair<int16_t,int16_t>> range; // ->72% momery(7.1M), 70->100%(4ms->0ms)
	for(auto i=0; i<n; ++i){
		if(s[i]=='('){
			stk.push(i);
		} else { // ')'
			if(stk.empty()){
				range.clear(); //less than 14->51% memory(7.2->7.1M)
				continue;
			}
			auto start = stk.top();
			stk.pop();
			while(true){
				if(range.empty()){
					range.emplace_back(start,i);
				} else {
					auto& last = range.back();//[range.size()-1];
					if(start < last.first){ //bigger parentheses
						range.pop_back();
						continue;
					} else if(start-1 > last.second){ // 
						range.emplace_back(start,i);
					} else { // merge disjoint parentheses
						start = last.first;
						last.second = i;
					}
				}
				break;
			}

			len = max(int(len), i-start+1);	
		} 
	}
	return len;
}

int main(){
	auto s = "()()(()((())(())((";
	cout << "max valid parenthese of " << s << " is " << maxValidParenthese(s) << '\n';
	cout << "max valid parenthese2 of " << s << " is " << maxValidParenthese2(s) << '\n';
	auto s2 = "(())()(()((()(";
	cout << "max valid parenthese of " << s2 << " is " << maxValidParenthese(s2) << '\n';
	cout << "max valid parenthese2 of " << s2 << " is " << maxValidParenthese2(s2) << '\n';
	cout << "max valid parenthese3 of " << s2 << " is " << maxValidParenthese3(s2) << '\n';

	auto s3 ="()(())";
	cout << "max valid parenthese3 of " << s3 << " is " << maxValidParenthese3(s3) << '\n';

	auto gens = genParentheses(4);
	copy(gens.begin(), gens.end(), ostream_iterator<string>(cout, "\t"));
	cout << '\t';
	return  0;
}
