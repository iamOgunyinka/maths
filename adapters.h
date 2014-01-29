#include <vector>
#include <stdexcept>

//Stack making use of standard library containers
template<class T, class C = std::vector<T>>
class Stack
{
	public:
	Stack(const C &a = C {}): container(a) { }
	Stack(C &&a): container(a) { }
	void pop();
	void push(const T &obj){
		container.push_back(obj);
	}
	void push(T &&obj){
		container.push_back(obj);
	}
	T top(){
		return container.top();
	}
	
	typedef typename C::size_type size_type;
	size_type size(){
		return container.size();
	}
	
	template<class U>
	friend bool operator<(const Stack<U> &, const Stack<U> &);
	template<class B>
	friend bool operator>(const Stack<B> &, const Stack<B> &);
	template<class A>
	friend bool operator==(const Stack<A> &, const Stack<A> &);
	template<class D>
	friend bool operator!=(const Stack<D> &, const Stack<D> &);
	
private:
    C container;
};

template<class T>
bool operator<(const Stack<T> &a, const Stack<T> &b){
	return a.container < b.container;
}

template<class T>
bool operator>(const Stack<T> &a, const Stack<T> &b){
	return !(a < b);
}

template<class T>
bool operator==(const Stack<T> &a, const Stack<T> &b){
	return a.container == b.container;
}

template<class T>
bool operator!=(const Stack<T> &a, const Stack<T> &b){
	return !(a.container == b.container);
}

//Raw stack. No std library containers whatsoever
template<class T, int S = 100>
class rstack
{
public:
    rstack(): container(new T[S]), size(S), tracker(0) { }
	rstack(const int &_size): container(new T[_size]), size(_size), tracker(0) { }
	explicit rstack(rstack &&);
	rstack(const rstack &);
	~rstack(){
		delete []container;
	}
	
	typedef int size_type;
	
	void push(const T &obj);
	void push(T &&obj);
	void pop();
	T top();
	size_type elements(){
		return tracker;
	}
	
	size_type max_elements(){
		return size;
	}
	
private:
    T * container;
    int size, tracker;
    void check(int s, const char *msg);
	void add(const T &);
};

template<class T, int S>
void rstack<T, S>::check(int s, const char *msg){
	if(s >= size){
		throw std::logic_error(msg);
	}
}
template<class T, int S>
rstack<T, S>::rstack(rstack &&obj): container(obj.container), size(obj.size), tracker(obj.tracker){
	obj.container = nullptr;
	obj.size = 0;
}

template<class T, int S>
rstack<T, S>::rstack(const rstack<T, S> &obj): container(new T[obj.size]), size(obj.size), tracker(obj.tracker){
	for(int i = 0; i < tracker; ++i){
		container[i] = obj.container[i];
	}
}

template<class T, int S>
void rstack<T, S>::add(const T & obj){
	check(tracker, "Full stack. Cannot push new element into stack");
	container[tracker] = obj;
	++tracker;
}

template<class T, int S>
void rstack<T, S>::push(const T &obj){
	add(obj);
}

template<class T, int S>
void rstack<T, S>::push(T &&obj){
	add(obj);
}

template<class T, int S>
void rstack<T, S>::pop(){
	--tracker;
	if(tracker < 0) throw std::logic_error("Unable to pop");
	container[tracker] = T {};
}

template<class T, int S>
T rstack<T, S>::top(){
	return container[tracker - 1];
}
