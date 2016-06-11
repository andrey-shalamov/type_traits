//g++ --version -> g++ (Ubuntu 5.3.1-14ubuntu2.1) 5.3.1 20160413
//g++ --std=c++0x type_traits.cpp
//g++ --std=c++11 type_traits.cpp
//g++ --std=c++14 type_traits.cpp
//g++ --std=c++17 type_traits.cpp

#include <type_traits>

template<typename...>
using void_t = void;

template<typename, typename = void_t<>>
struct has_mytag : std::false_type {};

template<typename T>
struct has_mytag<T, void_t<typename T::mytag>> : std::true_type {};

template<typename, typename = void_t<>>
struct has_mymember : std::false_type {};

template<typename T>
struct has_mymember<T, void_t<decltype(std::declval<T>().mymember)>> : std::true_type {};

template<typename, typename = void_t<>>
struct has_mymember_function : std::false_type {};

template<typename T>
using mymember_function_type = decltype(std::declval<T>().mymember_function(std::declval<int>(), std::declval<float>()));

template<typename T>
struct has_mymember_function<T, void_t<mymember_function_type<T>>> : std::true_type {};

struct a
{
	using mytag = std::true_type;

	int mymember = 0;
};

struct b
{
	int mymember_function(int, float) {}
};

int main()
{
	static_assert(has_mytag<a>::value, "");
	static_assert(not has_mytag<b>::value, "");

	static_assert(has_mymember<a>::value, "");
	static_assert(not has_mymember<b>::value, "");

	static_assert(not has_mymember_function<a>::value, "");
	static_assert(has_mymember_function<b>::value, "");

	return 0;
}
