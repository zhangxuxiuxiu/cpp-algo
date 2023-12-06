#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


class Queue{
	private:
		vector<int> holder;

	public:
		void Push(int v){
			holder.push_back(v);
			push_heap(holder.begin(), holder.end());
		}

		void Pop(){
			pop(holder.begin(), holder.end());
			holder.pop_back();
		}

		int Top() const{
			return holder[0];
		}	

		bool Empty() const{
			return holder.empty();
		}
};


int main(){
	Queue q;

}

