#include <iostream>
#include <vector>

using namespace std;

struct Node{
	int 	v;
	Node* 	next;

	Node(int v1, Node* n) : v(v1), next(n){}

	~Node(){
		delete next;
	}
};

Node* revert(Node* ptr){
	Node* head = nullptr;
	while(ptr!=nullptr){
		auto next = ptr->next;
		ptr->next = head;
		head = ptr;
		ptr = next;
	}
	return head;
}

Node* add(Node* left, Node* right){
	bool more = false;	
	Node* sum=nullptr;
	while(left!=nullptr || right!=nullptr || more){
		int cur = more?1:0;
		if(left!=nullptr){
			cur += left->v;
			left = left ->next;
		}
		if(right!=nullptr){
			cur += right->v;
			right = right ->next;
		}
		more = (cur>9);
		cur %=10;
		sum = new Node(cur, sum);
	}
	return sum==nullptr?new Node(0,nullptr) : revert(sum);
}


void print(Node* ptr){
	while(ptr!=nullptr){
		cout << ptr->v << '\t';
		ptr = ptr->next;
	}
	cout << '\n';
}

int main(){
	auto left = make_unique<Node>(1, new Node(2,nullptr));
	auto right = make_unique<Node>(9, new Node(7,nullptr));
	unique_ptr<Node> sum(add(left.get(), right.get()));
	print(sum.get());
	
	return 0;
}
