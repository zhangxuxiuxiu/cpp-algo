#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

bool validIp(string const& ip){
	switch(ip.size()){
		case 1:
			return "0"<=ip && ip<="9";
		case 2:
			return "10"<=ip && ip<="99";
		case 3:
			return "100"<=ip && ip<="255";
		default:
			return false;
	}
}

void merge(vector<string>*ips, string const& ipSeg, vector<string> const& ipSegs){	
	for(auto& seg : ipSegs){
		ips->push_back(ipSeg+(seg.empty()?"":"."+seg));
	}
}

vector<string> impl(string const& str, int start, int segCnt){
	if (segCnt <0 || str.size() <start || str.size()-start<segCnt){
		return {};
	}
	 
	if (segCnt ==0 && str.size()==start){
		return {""};
	}

	vector<string> ips;
	for(auto charCnt : {1,2,3}){
		if(start+charCnt<=str.size()){
			auto ipSeg = str.substr(start,charCnt);
			if (validIp(ipSeg)){
				merge(&ips, ipSeg, impl(str, start+charCnt, segCnt-1));	
			}
		}
	}

	return ips;
}

vector<string> split(string const& str){
	return impl(str, 0, 4);
}

vector<string> impl2(string const& str, int k){
	if(k<=0 ){
		if (str.empty()){
			return {""};
		} else {
			return	{};	
		}
	}

	vector<string> ips;
	for(auto i=0;i< min(3ul,str.size()); ++i){
		auto seg = str.substr(0,i+1);
		if(validIp(seg)){
			for(auto& rest : impl2(str.substr(i+1), k-1)){
				ips.push_back(rest.empty()?seg:seg+"."+rest);	
			}	
		}
	}
	return ips;	
}

vector<string> split2(string const& str){
	return impl2(str, 4);
}
 


int main(){
	auto ips = split("12345");
	for (auto& ip : ips){
		cout << ip << '\t';
	}
	cout << endl;

	auto ips2 = split2("12345");
	for (auto& ip : ips2){
		cout << ip << '\t';
	}
	cout << endl;
	return 0;
}
