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
    
	template<typename T>
	void cprint(const T &c, char sep = ' '){
		typename T::const_iterator begin = c.cbegin(), end = c.cend();
		for(typename T::const_iterator i = begin; i != end; ++i){
			std::cout << *i << sep;
		}
	}
	
	template<typename T>
	void cprint(const T &c, const std::string &sep){
		typename T::const_iterator begin = c.cbegin(), end = c.cend();
		for(typename T::const_iterator i = begin; i != end; ++i){
			std::cout << *i << sep;
		}
	}
	
	template<typename T>
	void print(T &&c, char sep = ' '){
		std::cout << c << sep;
	}
	
	//this part is implemented by Cameron DaCamara, NOT me!
	template<class T, class U, class ...X>
	struct is_all_same: std::integral_constant<bool, is_all_same<T, U>::value &
                                        is_all_same<U, X...>::value>
	{};

	template<class T, class U>
	struct is_all_same<T, U>: std::false_type {};
 
	template<class T>
	struct is_all_same<T, T>: std::true_type {};
	
	template<class T, class ...X>
	auto implement_array(X &&...args)-> std::array<T, sizeof...(args)>
	{
	return std::array<T, sizeof...(args)>{
			{ std::forward<X>(args)... } 
		};
	}

	template<class T, class ...U>
	auto make_array(T && a, U &&...args)-> typename std::enable_if<is_all_same<T,U...>::value,
                                        std::array<T, 1 + sizeof...(args)>>::type
	{
		return implement_array<T>(std::forward<T>(a), std::forward<U>(args)...);
	}

	template<class T>
	auto make_array(T &&arg) -> std::array<T, 1>{
		return implement_array<T> (std::forward<T>(arg));
	}
	
	template<class T>
	T add(T a){
		return a;
	}
	
	template<class T, typename ...U>
	T add(T a, U ...b){
		return (add(a) + add(b...));
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
		return first > second;
	}
	bool is_lesser(const int &first, const int &second)
	{
		return !(is_greater(first, second));
	}
	
	ivec generate_prime(const int &start, const int &end)
	{
		ivec vect_t {};
		int starter {};
		if(is_greater(start, end)){
			vect_t.resize(start);
			starter = end;
		} else {
			vect_t.resize(end);
			starter = start;
		}
		std::generate(vect_t.begin(), vect_t.end(), [&]() mutable {return starter++; });
		vect_t.erase(std::stable_partition(vect_t.begin(), vect_t.end(), is_prime), vect_t.end());
		return vect_t;
	}
	/* generate multiplication table
	svec generate_table(const std::initializer_list<int> &begin, const std::initializer_list<int> &end)
	{
		svec vect_t {};
		
		return vect_t;
	}
	*/
	
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
