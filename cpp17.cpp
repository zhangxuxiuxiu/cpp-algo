#include <iostream>
#include <vector>

using namespace std;


int main(){
	// Class template argument deduction
	std::vector v{ 1, 2, 3 }; // deduces std::vector<int>


	// constexpr if
	{
		template <typename T>
			constexpr bool isIntegral() {
				if constexpr (std::is_integral<T>::value) {
					return true;
				} else {
					return false;
				}
			}
		static_assert(isIntegral<int>() == true);
	}
	
	//Selection statements with initializer
	{
		{
			std::lock_guard<std::mutex> lk(mx);
			if (v.empty()) v.push_back(val);
		}
		// vs.
		if (std::lock_guard<std::mutex> lk(mx); v.empty()) {
			v.push_back(val);
		}

		Foo gadget(args);
		switch (auto s = gadget.status()) {
			case OK: gadget.zip(); break;
			case Bad: throw BadFoo(s.message());
		}
		// vs.
		switch (Foo gadget(args); auto s = gadget.status()) {
			case OK: gadget.zip(); break;
			case Bad: throw BadFoo(s.message());
		}

	}


	return 0;
}

