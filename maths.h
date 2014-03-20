#include <array>
#include "sales.h"
#include "vector.h"

namespace maths
{
	template <class T>
	using vector = vector<T>;
	
	template<class T>
    using container = typename std::vector<T>;
    using svec = container<std::string>;
    using ivec = container<int>;
    using dvec = container<double>;
    using pair_is = typename std::pair<int, std::string>; 
    using vec_pairs = container<pair_is>;
    
    struct Less
    {
		template<class T>
		bool operator()(T &&a, T &&b)
		{
			return std::tie(a) < std::tie(b);
		}
		template<typename T, typename U>
		bool operator()(T &&a, U &&b)
		{
			return a < b;
		}
	};
	template<class T, class U = std::less<T>>
	int compare(const T &a, const T &b, U func){
	    return func(a, b);
	}	
	template<class T, class U = std::less<T>>
	int compare(const T &a, const T &b){
	    return U()(a, b);
	}
	template<typename T>
	void cprint(const T &c, char sep = ' '){
		typename T::const_iterator begin = c.cbegin(), end = c.cend();
		for(typename T::const_iterator i = begin; i != end; ++i){
			std::cout << *i << sep;
		}
	}
	template<typename Tuple, size_t N>
	struct TuplePrinter
	{
		void print(const Tuple &arg){
			TuplePrinter<Tuple, N-1>::print(arg);
			std::cout << std::get<N-1>(arg) << " ";
		}
	};
	template<typename Tuple>
	struct TuplePrinter<Tuple, 1>
	{
		void print(const Tuple &arg){
			std::cout << std::get<0>(arg) << " " ;
		}
	};
	template<typename ...T>
	void tuple_print(const std::tuple<T...> &arg)
	{
		TuplePrinter<decltype(arg), sizeof...(T)>::print(arg);
	}
	template<typename T>
	void cprint(const T &c, const std::string &sep){
		typename T::const_iterator begin = c.cbegin(), end = c.cend();
		for(typename T::const_iterator i = begin; i != end; ++i){
			std::cout << *i << sep;
		}
	}
	template<typename T, typename U>
	void cprint(const std::vector<std::pair<T, U>> &vecsi, char sep = ' ')
	{
		for(const auto &i: vecsi){
			std::cout << i.first << ' ' << i.second << sep;
		}
	}
	template<typename T>
	void print(T &&c, char sep = ' '){
		std::cout << c << sep;
	}
	template<class T, class U, class ...X>
	struct is_all_same: std::integral_constant<bool, is_all_same<T, U>::value & is_all_same<U, X...>::value> {};

	template<class T, class U>	struct is_all_same<T, U>: std::false_type {};
 
	template<class T> struct is_all_same<T, T>: std::true_type {};
	
	template<class T, class ...X>
	auto implement_array(X &&...args)-> std::array<T, sizeof...(args)>
	{
	return std::array<T, sizeof...(args)>{
			{ std::forward<X>(args)... } 
		};
	}

	template<class T, class ...U>
	auto make_array(T && a, U &&...args)-> typename std::enable_if<is_all_same<T,U...>::value, std::array<T, 1 + sizeof...(args)>>::type
	{
		return implement_array<T>(std::forward<T>(a), std::forward<U>(args)...);
	}

	template<class T>
	auto make_array(T &&arg) -> std::array<T, 1>{
		return implement_array<T> (std::forward<T>(arg));
	}
	
	template<class T> T add(T a){ return a; }
	
	template<class T, typename ...U>
	T add(T a, U ...b){
		return (a + add(b...));
	}
	
	template<typename T>
	typename std::remove_reference<T>::type &&move(T &&arg)
	{
		return static_cast<typename std::remove_reference<T>::type &&>(arg);
	}
	template<typename ...U>
	std::tuple<U...> make_tuple(U &&...args)
	{
		return std::tuple<U...>(std::forward<U>(args)...);
	}
	template<typename T, typename...U>
    std::shared_ptr<T> make_shared(U && ...args)
    {
        return std::shared_ptr<T>(new T (std::forward<U>(args)...));
    }
    
	
	constexpr double PI = 3.141;
	std::string to_roman(int number)
	{
		std::string roman {};
		pair_is roman_pair [] {
			{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
			{90, "XC"}, {50, "L",},  {40, "XL"}, {10, "X"}, {9, "IX"},
			{5, "V"}, {4, "IV"},  {1, "I"}
		};
	    const size_t s = sizeof (roman_pair) / sizeof (roman_pair[0]);
	    
	    for(unsigned int i = 0; i < s; ++i){
			while(number >= roman_pair[i].first){
				roman += roman_pair[i].second;
			    number -= roman_pair[i].first;
		    }
	    }
	    return roman;
    }

    svec generate_roman(const unsigned &start = 1, const unsigned &end = 50, const unsigned &step = 1)
    {
	    svec vector_of_romans {};
	    for(unsigned int i = start; i != end; i += step)
	    {
		    vector_of_romans.push_back(to_roman(i));
		    if((i+step) > end) break;
	    }
	    return vector_of_romans;
    }

    vec_pairs generate_roman_pairs(const unsigned &start = 1, const unsigned &end = 50, const unsigned &step = 1)
    {
	    vec_pairs vec_pairs_of_romans {};
	    svec vector_of_romans(generate_roman(start, end, step));
    	auto _begin = start;
	    for(const auto &i: vector_of_romans){
		    vec_pairs_of_romans.push_back(std::make_pair(_begin, i));
		    _begin += step;
	    }
	    return vec_pairs_of_romans;
    }
    
    std::size_t square(const int &n){
		return n * n;
	}
	
	auto square_root(const double &n) -> decltype(std::sqrt(n)){
		return std::sqrt(n);
	}
	
    bool is_prime(const int &number)
    {
		if(number < 2){
			return false;
		}
		auto sq_root = square_root(number);
		for(unsigned int i = 2; i <= sq_root; ++i){
			if(number%i == 0){
				return false;
			}
		}
		return true;
	}
	
	bool is_greater(const int &first, const int &second)
	{
		return !Less()(first, second);
	}
	bool is_lesser(const int &first, const int &second)
	{
		return Less()(first, second);
	}
	
	ivec generate_prime(const int &start, const int &end)
	{
		ivec vect_t {};
		if(is_greater(start, end)) return vect_t;
		for(int i = start; i != end; ++i){
			if(is_prime(i)){
				vect_t.push_back(i);
			}
		}
		return vect_t;
	}
	//generate multiplication table
	std::vector<std::pair<std::string, int>> generate_table(const int &start, const int &column, const int &row)
	{
		std::string os { };
		std::vector<std::pair<std::string, int>> vect_t {};
		for(int x = start; x <= row; ++x){
			for(int y = 1; y <= column; ++y){
				os = std::to_string(x) + std::string(" x ") + std::to_string(y) + std::string(" = ");
				vect_t.push_back(std::make_pair(os, x * y));
			}
		}
		return vect_t;
	}
	
	template<class T, class ...U>
	auto apply(T && a, U &&...b) -> decltype(a(b...)){
		return a(b...);
	}
	
	double dcos(int n){
		return (PI / 6) * (180/PI);
	}
	double dsin(int n){
		return std::sin((double)n) * PI;
	}
};
