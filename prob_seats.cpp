#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// n seats, n people, first take a seat randomly, ith person take ith seat if available, take randomly otherwise
// the probability of ith person take jth seat
double prob_take_seat( int i, int j, int n){
	if(i==1){ 		// i({1}) 
		return 1.0/n;
	} else if (j>1 && j<i){ // i(1,n], j(1,i)  
		return 0; 
	} else if( i == j ){ 	// i(1,n], j({i})
		return (n-i+1)/(n-i+2);
	} else {		// i(1,n], j((i,n]U{1})
		return 1.0/(n-i+2)/(n-i+1);
	}

//	if(i==n){ // 0.5: i{n}&j{1,n}; 0: i{n}&j(1,n) 
//		return j==1 || j==n ? 0.5 : 0;
//	}
}

//for all people, ith person takes ith seat 
double all_valid_seat(int n){
	switch(n){
		case 1:
			return 1.0;
		case 2:
			return 0.5;
		default:
			return 1.0/n/n;
	}	
}
