#include <iostream>
#include <stack>
#include <utility>

using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
};

void preorder(TreeNode & tree){
	std::stack<TreeNode*> stk;	
	stk.push(&tree);
	TreeNode* p=nullptr;

	while(!stk.empty()){
		p = stk.top();
		stk.pop();
		std::cout << "val:" << p->val << '\n';
		if(p->right!=nullptr) stk.push(p->right);
		if(p->left!=nullptr) stk.push(p->left);
	}

}

enum Order{
	Pre,
	In,
	Post
};

void traverse(TreeNode & tree, Order order ){
	std::stack<pair<TreeNode*, bool>> stk;	
	stk.push({&tree,false});
	pair<TreeNode*,bool> p;

	while(!stk.empty()){
		p = stk.top();
		stk.pop();
		if(!p.second){
			if(order == Order::Post) stk.push({p.first, true});
			if(p.first->right!=nullptr) stk.push({p.first->right, false});
			if(order == Order::In) stk.push({p.first, true});
			if(p.first->left!=nullptr) stk.push({p.first->left,false});
			if(order == Order::Pre) stk.push({p.first, true});
		} else {
			std::cout << "val:" << p.first->val << '\n';
		}
	}
}

int main(){
	TreeNode left{1, nullptr, nullptr};
	TreeNode right{2, nullptr, nullptr};
	TreeNode root{0, &left, &right};
	
	traverse(root, Order::Pre);
	traverse(root, Order::In);
	traverse(root, Order::Post);

	return 0;
}
