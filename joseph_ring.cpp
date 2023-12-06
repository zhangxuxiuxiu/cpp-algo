#include <iostream>
#include <stack>

using namespace std;

// f(n, k) = (f(n-1,k) +  k)%n;
int joseph_ring(int n, int k){
	auto v = 0;
	for(auto i=1; i<=n; ++i){
		v = (v+k)%i;
	}
	return v;
}

int joseph_ring2(int n, int k){
	return n==1?0:((joseph_ring2(n-1,k)+k)%n);
}

// remove 1,3,5... then 8,4..., the last?
int left_right_interval(int n){
	return n==1?1:2*(n/2+1-left_right_interval(n/2));
}

// f(2) = 2(2/2+1-f(1)) 010  2(1+1-1)
// f(3) = 2(3/2+1-f(1))	011  2(1+1-1)
// f(4) = 2(4/2+1-f(2)) 100  2(2+1-f(2)) 2->4
// f(5) = 2(5/2+1-f(2)) 101  2(2+1-f(2)) 2->5
// f(6) = 2(6/2+1-f(3)) 110  2(3+1-f(3)) 1->3->6
// f(7) = 2(7/2+1-f(3)) 111  2(3+1-f(3)) 1->3->7
int left_right_interval2(int n){
	stack<bool> stk;
	while(n>1){
		stk.push(n%2==1);
		n/=2;
	}

	auto k = 1, base =1;
	while(!stk.empty()){
		k=2*(base+1-k);
		base+=base+stk.top();
		stk.pop();
	}
	return k;
}

int main(){
	std::cout << "joseph_ring(n=10, k=3)=" << joseph_ring(10,3) << '\n';
	std::cout << "joseph_ring2(n=10, k=3)=" << joseph_ring2(10,3) << '\n';

	for(auto i=3; i<10; ++i){
		cout << boolalpha <<  (left_right_interval(i)==left_right_interval2(i)) << '\t';
	}

	return 0;
}
