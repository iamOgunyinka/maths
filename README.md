Summary
=======

Beginners often face challenges finding projects to work on, speaking from experience. This mathematical project tries to
fill that void. Although meant to be useful for beginner programmers to have something tangible to work on, non-beginners can also contibute to the library design.

Design
======

The math library (for now) has a namespace called 'maths,' within this name there are useable mathematical functions. As
at the time of this writing, we have 18 functions in 'maths'. The other functions are meant to be added by the library
contibutors.

Usage
======

To use this library, download the zipped master file, unzip it, copy the files named maths.h into the working directory and start using. It is that simple.

Example:
    
    auto roman = maths::generate_roman(1, 1500, 1); //first arg is the start, followed by end, and lastly the steps = 1
    maths::cprint(roman, " = "); //cprint prints all elements in roman, with " = " as separator
    bool prime = maths::is_prime(6); //returns false. 6 is not a prime number
    maths::vector<int> vint(10, 7); //same as std::vector of 10 ints, all initialized to 7
    return 0;

Disclaimer
==========

This library as stated above is NO WAY a replacement for the std:: library functions or containers. It meant to be
educational and that's all it is.
