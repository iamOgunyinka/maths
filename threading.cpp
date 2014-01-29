#include <thread>
#include <algorithm>
#include <iostream>

template<class Iter, class T>
struct accumulate_val{
	void operator ()(Iter begin, Iter end, T & result)
	{
		result = std::accumulate(begin, end, result);
	}
};

template<class Iter, class T>
T parallel_accumulate(Iter begin, Iter end, T init)
{
	const int length = std::distance(begin, end);
	if(length < 1) {
		return init;
	}
	const int min_threads = 25;
	const int max_threads = (length + min_threads - 1) / min_threads;
	const int hardware_threads = std::thread::hardware_concurrency();
	const int num_threads = std::min( hardware_threads != 0 ? hardware_threads: 2, max_threads );
	const int block_size = length / num_threads;
	
	std::vector<T> results(num_threads);
	std::vector<std::thread> t(num_threads -1);
	
	Iter block_start = begin;
	for(int i = 0; i != (num_threads - 1); ++i){
		Iter block_end = block_start;
		std::advance(block_end, block_size);
		t[i] = std::thread(accumulate_val<Iter, T>(), block_start, block_end, std::ref(results[i]));
		block_start = block_end;
	}
	accumulate_val<Iter, T>()(block_start, end, results[num_threads - 1]);
	std::for_each(t.begin(), t.end(), std::mem_fn(&std::thread::join));
	
	return std::accumulate(results.begin(), results.end(), init);
}

void foo(){
	return;
}

int main()
{
	std::vector<char> a(58);
	int i = 64; //ASCII value for 'A'
	auto autogen = [&]()->char { return ++i; };
	std::generate(a.begin(), a.end(), autogen); //A to z
	std::cout << parallel_accumulate(a.begin(), a.end(), std::string {});
	return 0;
}
