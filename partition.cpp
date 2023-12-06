#include <iostream>


void print(int* arr, int low, int high){
	while(low<high){
		std::cout << arr[low++] << '\t';
	}
	std::cout << '\n';
}

template<int N>
void print(int (&arr)[N]){
	return print(arr,0,N);
}

// arr:[low,high]
int partition(int* arr, int low, int high){
//	if(low>=high){
//		return low;
//	}
	auto pivot = arr[low];	
	while(low<high){
		while(low<high && arr[low]<pivot){++low;} // find first bigger 
		while(low<high && arr[high]>=pivot){--high;} // find first smaller 
		if (low<high){ // bigger&smaller found
			std::swap(arr[low], arr[high]);
		}
		//1) bigger&smaller not found
		//2) bigger found & smaller not found
		//3) $low is smallest, $high as biggest
	}
	return low;
}

int minK(int* arr, int low, int high, int k){
	auto l=low;
	auto h=high;
	print(arr,low,high+1);
	while(k!=1 && high-low+1!=k){
		auto idx = partition(arr, low, high);
		if (idx-low >= k){
			high = idx-1;
		} else {
		  	low = idx; 
			k -= idx-low;
		} 
		std::cout << "mink idx=" << idx << ",low=" << low << ",high=" << high << '\n';
		print(arr,l,h+1);
	}	
	return k==1 ? low : high;
}

int main(){
	int arr[]={44,2,3,43,534,53,45,8};
	{
		int pidx = partition(arr,0,sizeof(arr)/sizeof(int)-1);	
		std::cout << "partition index:" << pidx << '\n';
		print(arr);
	}

	{
		auto k = 4;
		int kidx = minK(arr,0,sizeof(arr)/sizeof(int)-1,k);	
		std::cout << "mink index:" << kidx  << " with k:" << k << '\n';
		print(arr);
	}

	return 0;
}

