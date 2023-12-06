#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool impl(vector<pair<int16_t,int16_t>> const& words,int left, int pos){	
	if(pos == words.size()){
		return true;
	}

	while(pos<words.size() && words[pos].first<left){ ++pos; }
	while(pos<words.size() && words[pos].first==left){
		if(impl(words, words[pos].second, pos+1)){
			return true;
		}
		++pos;
	}
	return false;
}

// recursive: Depth First Search
// dynamic programming: 
bool wordBreak(string const& sentence, vector<string> const& dict){
	vector<pair<int16_t,int16_t>> words;	
	for(auto& w : dict){
		auto pos = sentence.find(w);
		while(pos!= string::npos){
			words.emplace_back(pos, pos+w.size());
			pos = sentence.find(w, pos+1);
		}
	}
	sort(words.begin(), words.end());
	for(auto& w : words){
		cout << '[' << w.first << ',' << w.second << "]\t";
	}
	cout << '\n';

	return impl(words, 0, 0);	
}

int main(){
	cout << boolalpha << wordBreak("leetcode",{"leet", "code"}) << '\n';
	cout << boolalpha << wordBreak("abababababa",{"aba", "bab", "ab", "ba"}) << '\n';

	return 0;
}
