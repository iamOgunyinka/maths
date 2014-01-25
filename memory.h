#ifndef MEMORY_H
#define MEMORY_H

template<typename T>
class Unique_ptr
{
public:
    Unique_ptr<T>(const Unique_ptr<T> &) = delete;
	Unique_ptr<T>& operator=(const Unique_ptr &) = delete;
	Unique_ptr<T>(T *);
	~Unique_ptr();
	
	T* release();
	void reset(T *);
	T& operator*();
	
private:
  void free(T *);
  T * data;
};

#endif
