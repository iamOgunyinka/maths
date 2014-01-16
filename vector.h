#include <iostream>
#include <memory>

template<class T>
class vector
{
public:
    vector<T>(): __begin(nullptr), first_free(nullptr), __end(nullptr) {}
    vector<T>(const vector<T> &);
    vector<T>& operator =(const vector<T> &);
    vector<T>(const unsigned int &n): vector<T>(){
		reserve(n);
	}
	vector<T>(const unsigned int &, const T &);
	~vector<T>(){
		free();
	}
    // Operator performed on vec
    void push_back(const T &);
    size_t size() const { return first_free - __begin; }
    size_t capacity() const { return __end - __begin; }
    void reallocate();
    
    T *begin() const { return __begin; }
    T *end() const { return first_free; }
    T *operator++() { return __begin++; }
    
    void resize(const unsigned int &n);
    void reserve(const unsigned int &n);

private:
    void free();
    void check_n_alloc(){
		if (size() == capacity()) reallocate();
	}

    T * __begin;
    T *first_free;
    T * __end;
    
    std::allocator<T> alloc;
    std::pair<T *, T *> alloc_n_copy(const T *, const T *);
};

template<class T>
void vector<T>::resize(const unsigned int &n)
{
    if( n > size()){
    reserve(n);
    return;
    }
    if(__begin){
            auto new_free = __begin + n;
            for(auto i = first_free; i != new_free;)
                alloc.destroy(--i);
            first_free = new_free;
        }
}

template<class T>
void vector<T>::push_back(const T &s)
{
    check_n_alloc();
    alloc.construct(first_free++, s);
}

template<class T>
vector<T>::vector(const unsigned int &n, const T &s): vector(n)
{
    for(unsigned int i=0; i < n; ++i)
        push_back(s);
}

template<class T>
std::pair<T *, T *> vector<T>::alloc_n_copy(const T *a, const T *b)
{
    auto data = alloc.allocate(b - a);

    return { data, std::uninitialized_copy(a, b, data)};
}

template<class T>
void vector<T>::free()
{
    if(__begin){
        for(auto i = first_free; i != __begin;)
        alloc.destroy(--i);
    alloc.deallocate(__begin, __end - first_free);
    }
}

template<class T>
vector<T>::vector(const vector<T> &s){
    auto newdata = alloc_n_copy(s.begin(), s.end());
    __begin = newdata.first;
    first_free = __end = newdata.second;
}

template<class T>
vector<T>& vector<T>::operator =(const vector<T> &rhs){
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    __begin = data.first;
    __end = first_free = data.second;
    return *this;
}

template<class T>
void vector<T>::reallocate(){
    auto new_capacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(new_capacity);

    auto dest = newdata;
    auto elem = __begin;
    for(unsigned int i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();

    __begin = newdata;
    first_free = dest;
    __end = __begin + new_capacity;
}

template<class T>
void vector<T>::reserve(const unsigned int &n){
    if(n <= capacity())
        return;
    auto new_capacity = n - capacity();
    auto newdata = alloc.allocate(new_capacity);
    if(!__begin){
        __begin = first_free = newdata;
        __end = __begin + new_capacity;
    } else {
        __end += new_capacity;
    }
}
