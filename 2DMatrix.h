#include <iostream>

class TwoDMatrix
{
private:
    int **matrix;
    const long long row{}, column{};
public:
    TwoDMatrix(const long long &_row = 0, const long long &_column = 0) noexcept(false): matrix(nullptr), row(_row), column(_column){
        try{
            matrix = new int *[row];
        } catch (std::bad_alloc &e) {
            std::cout << e.what() << std::endl;
            throw;
        } catch(...) {
            throw;
        }
        for(int x = 0; x != row; ++x){
            matrix[x] = new int[column];
        }
    }
    
    TwoDMatrix(const TwoDMatrix &object) = delete;
    TwoDMatrix &operator=(const TwoDMatrix &) = delete;
    TwoDMatrix(TwoDMatrix &&object): matrix(std::move(object.matrix)), row(std::move(object.row)), column(std::move(object.column)) { }
    TwoDMatrix& operator=(TwoDMatrix &&object){
        std::swap(*this, object);
        return *this;
    }
    friend std::istream &operator>>(std::istream &is, TwoDMatrix &object){
        if(object.matrix == nullptr){
            return is;
        }
        for(int counter = 0; counter != object.row; ++counter){
            for(int counter_2 =0; counter_2 != object.column; ++counter_2){
                std::cin >> object.matrix[counter][counter_2];
            }
        }
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const TwoDMatrix &object){
        if(object.matrix == nullptr){
            return os;
        }
        for(int counter = 0; counter != object.row; ++counter){
            for(int counter_2 =0; counter_2 != object.column; ++counter_2){
                std::cout << object.matrix[counter][counter_2] << " ";
            }
            std::cout << std::endl;
        }
        return os;
    }
    ~TwoDMatrix(){
        if(matrix != nullptr){
            delete []matrix;
        }
    }
};
