#include <iostream>
#include <vector>

using namespace std;

struct Node{
	int 	v;
	Node* 	next;

	~Node(){
		delete next;
	}
};

bool palindrome_list(Node* root){
	

}

int main(){
	Node root{1, new Node(2, new Node(1,nullptr))};
	cout << boolalpha << palindrome_list(&root) << endl;
	
	return 0;
}
