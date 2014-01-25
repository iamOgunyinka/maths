
#ifndef MEMORY_H
#define MEMORY_H

template<typename T>
class Unique_ptr
{
public:
  Unique_ptr<T>(const Unique_ptr<T> &) = delete;
	Unique_ptr<T>& operator=(const Unique_ptr &) = delete;
	Unique_ptr<T>(T *p = nullptr): data(p) { }
	~Unique_ptr(){
		free();
	}
	
	T *release(){
		T *copy = data;
		data = nullptr;
		return copy;
	}
	
	void reset(T *p = nullptr){
		free(p);
	}
	
	T& operator*(){
		return *data;
	}
	
private:
    void free(T *p = nullptr){
		if(data){
		  delete data;
		}
		data = p;
		}
		
    T * data;
};

#endif
