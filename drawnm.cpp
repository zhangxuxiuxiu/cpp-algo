#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


void draw(int n, int m){
	vector<vector<int>> grid(n, vector<int>(m,0));

	auto l =0, r =m-1, u=0, d=n-1, x=1;
	while(l<=r && u<=d){
		// one column
		if(l==r){
			for(auto i=u; i<=d; ++i){
				grid[i][l] = x++;
			}
			break;
		}

		// one row
		if(u==d){
			for(auto i=l; i<=r; ++i){
				grid[u][i] = x++;
			}
			break;
		}

		//upper, right, down, left 
		for(auto i=l; i<r; ++i){
			grid[u][i] = x++;
		}
		for(auto i=u; i<d; ++i){
			grid[i][r] = x++;
		}
		for(auto i=r; i>l; --i){
			grid[d][i] = x++;
		}
		for(auto i=d; i>u; --i){
			grid[i][l] = x++;
		}
		++l; --r; ++u; --d;
	}

	for(auto& row : grid){
		copy(row.cbegin(), row.cend(), ostream_iterator<int>(cout, "\t"));
		cout << '\n';
	}
}

int main(){
	draw(1,1);
	draw(3,4);
	draw(5,7);
	draw(2,4);
	draw(12,18);

	return 0;
}
