#include <iostream>
#include <string.h>

using namespace std;

template <typename T>
auto& auto_deduct(T& t) {
	return t;
}


int main(){
	// auto lambda
	{
		auto identify = [](auto x){return x;}
		assert(strcmp(identify("yes"),"yes")==0);
	}

	// lambda capture initializers
	{
		auto p = make_unique<int>(7);	
		auto lam_fn = [&x = p, p=move(p), y = 9](){
			if( !x && p ){
				return y+1;
			} else {
				return y;
			}
		}
		assert(lam_fn()==10);
	}

	// return type deduction
	{
		// Returns a reference to a deduced type.
		auto g = [](auto& x) -> auto& { return auto_deduct(x); };
		int y = 123;
		assert(&g(y) == &y); // reference to `y`
	}

	// decltype(auto)
	{
		const int x = 0;
		auto x1 = x; // int
		decltype(auto) x2 = x; // const int
		int y = 0;
		int& y1 = y;
		auto y2 = y1; // int
		decltype(auto) y3 = y1; // int&
		int&& z = 0;
		auto z1 = std::move(z); // int
		decltype(auto) z2 = std::move(z); // int&&

		// Return type is `int`.
		auto f(const int& i) {
			return i;
		}

		// Return type is `const int&`.
		decltype(auto) g(const int& i) {
			return i;
		}

		int x = 123;
		static_assert(std::is_same<const int&, decltype(f(x))>::value == 0);
		static_assert(std::is_same<int, decltype(f(x))>::value == 1);
		static_assert(std::is_same<const int&, decltype(g(x))>::value == 1);
	}

	// constexpr loose constraint	
	// support if & multiple return
	// only one return is supported in cpp11
	{
		constexpr int factorial(int n) {
			if (n <= 1) {
				return 1;
			} else {
				return n * factorial(n - 1);
			}
		}
		factorial(5); // == 120
	}

	// variable template
	{
		template<class T>
		constexpr T pi = T(3.1415926535897932385);
	}


	return  0;
}
