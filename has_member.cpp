#include <iostream>
#include <string>

struct User{
	std::string Say(){
		return "User Hello!";
	}
};

struct User2{};

template<class T, class R, class... Args>
struct HasSay{
	template<class U>
	static auto check(U*) -> decltype(std::is_same<R,decltype(std::declval<U>().Say(std::declval<Args>()...))>::value);
	static void check(...); 
	static const bool value = !std::is_void<decltype(check((T*)(nullptr)))>::value;
};

template<class T, class R, class... Args>
struct HasSay2{
	template<class U>
	static auto check(U*) -> std::integral_constant<bool,std::is_same<R,decltype(std::declval<U>().Say(std::declval<Args>()...))>::value>;
	static std::false_type check(...); 
	static const bool value = decltype(check((T*)(nullptr)))::value;
};


template<class T, class R, class... Args>
struct HasSay3{
	template<class U>
	static auto check(U*) -> typename std::enable_if<std::is_same<R,decltype(std::declval<U>().Say(std::declval<Args>()...))>::value, std::true_type>::type;
	static std::false_type check(...); 
	static const bool value = decltype(check((T*)(nullptr)))::value;
};

int main(){
	static_assert(HasSay<User,std::string>::value, "yes");
	static_assert(!HasSay<User2,std::string>::value, "no");

	static_assert(HasSay2<User,std::string>::value, "yes");
	static_assert(!HasSay2<User2,std::string>::value, "no");

	static_assert(HasSay3<User,std::string>::value, "yes");
	static_assert(!HasSay3<User2,std::string>::value, "no");
	return 0;
}
