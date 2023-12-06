#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void topk(vector<int> const& slice, int k){
	vector<int> ctn;
	ctn.reserve(k);
	priority_queue<int, vector<int>, greater<int>> q(greater<int>(), move(ctn));	

	for(auto v : slice){
		if(q.size() < k){
			q.push(v);
		} else if(q.top() < v){
			q.pop();	
			q.push(v);
		}	
	}

	while(!q.empty()){
		cout << q.top() << '\t';
		q.pop();
	}
	cout << '\n';
}

int main(){
	topk({4,5,6,632,4,6,9},3);
	return 0;
}
