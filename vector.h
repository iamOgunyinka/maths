
template<typename T>
class vector
{
public:
    vector<T>() = default;
    vector(const vector<T> &vec);
    vector(vector && vec);
    vector(const T &init);
    
    //accessors && operators
    T& operator[](size_t index);
    T* begin();
    T* end();
    
    T& back();
    void resize();
    void reserve();
    void push_back(const T &obj);

private:
    T data;
    void alloc_n_copy();
};
