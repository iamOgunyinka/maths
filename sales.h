#include <iostream>
#include <algorithm>
#include <vector>

class Sales_data
{
public:
    //ctors && member functions for Sales_data objects
    Sales_data(): BookNo(""), units_sold(0), revenue(0.0) { }
    Sales_data(const std::string &s, unsigned int n, double p):
        BookNo(s), units_sold(n), revenue(n * p) { }
    explicit Sales_data(std::istream &is) { std::cin >> *this; }
    explicit Sales_data(const std::string &s): 
        BookNo(s), units_sold(0), revenue(0) { }
    std::string isbn() const { return this->BookNo; }
    Sales_data &combine(const Sales_data&);
    friend std::ostream &operator <<(std::ostream &, const Sales_data &);
    friend std::istream &operator >>(std::istream &, Sales_data &);
    friend Sales_data add(const Sales_data &, const Sales_data &);
    
private:

    std::string BookNo;
    unsigned int units_sold;
    double revenue;
    inline double avg_price() const { 
            return units_sold ? revenue/units_sold : 0.0; }
};

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data add(const Sales_data &first, const Sales_data &last)
{
    Sales_data _new = first;
    _new.units_sold += last.units_sold;
    _new.revenue +=last.revenue;
    return _new;
}

class Person
{
private:
    std::string name;
    std::string address;
public:    
    //ctors && member functions for Person
    Person(): name(""), address("") { }
    Person(const std::string &n, const std::string &a):
        name(n), address(a) { }
    Person(std::istream &is) { Pread(is, *this); }
    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }
    //friend declaration for non-member variables
    friend std::istream &Pread(std::istream &, Person &);
    friend std::ostream &Pprint(std::ostream &, const Person &);
};

std::ostream &operator <<(std::ostream &os, const Sales_data &item)
{
    os<<item.isbn()<<", "<<item.units_sold<<" units, at $"<<item.revenue
      <<", and average price is $"<<item.avg_price();
    return os;
}

std::istream &operator >>(std::istream &in, Sales_data &item)
{
    double price=0.0;
    in>>item.BookNo>>item.units_sold>>price;
    item.revenue = item.units_sold * price;
    return in;
}
std::istream &Pread(std::istream &is, Person &pers)
{
    is>>pers.name>>pers.address;
    return is;
}

std::ostream &Pprint(std::ostream &os, const Person &pers)
{
    os<<pers.getName()<<", "<<pers.getAddress();
    return os;
}

bool isbigger(const Sales_data &a, const Sales_data &b)
{
    return a.isbn() > b.isbn();
}

bool isequal(const Sales_data &a, const Sales_data &b)
{
    return a.isbn() == b.isbn();
}
