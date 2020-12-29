//
// Created by weining on 29/12/20.
//

#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <iterator>

template < std::size_t N >
struct array
{
    char array[ N ];
    enum
    {
        size = N
    };
};

template < int I >
struct value_of
{
};

template <>
struct value_of< 1 >
{
    enum
    {
        value = true
    };
};

template <>
struct value_of< 2 >
{
    enum
    {
        value = false
    };
};

void* erase( ... );

struct is_cpp20
{
    static array< 1 > deduce_type( std::vector< int >::size_type );
    static array< 2 > deduce_type( ... );
    static std::vector< int > v;
    static int i;
    enum
    {
        value = value_of< sizeof( deduce_type( erase( v, i ) ) ) >::value
    };
};

struct is_cpp17
{
    static array< 1 > deduce_type( char* );
    static array< 2 > deduce_type( const char* );
    static std::string s;
    enum
    {
        value = value_of< sizeof( deduce_type( s.data() ) ) >::value
    };
};

int cbegin( ... );

struct is_cpp14
{
    static array< 1 > deduce_type( std::string::const_iterator );
    static array< 2 > deduce_type( int );
    enum
    {
        value = value_of< sizeof( deduce_type( cbegin( std::string() ) ) ) >::value
    };
};

int move( ... );

struct is_cpp11
{
    template < typename T >
    static array< 1 > deduce_type( T );
    static array< 2 > deduce_type( int );
    static std::string s;
    enum
    {
        value = value_of< sizeof( deduce_type( move( s ) ) ) >::value
    };
};

enum
{
    cpp_year = is_cpp20::value   ? 2020
               : is_cpp17::value ? 2017
               : is_cpp14::value ? 2014
               : is_cpp11::value ? 2011
                                 : 19982003
};

// Bjarne Stroustrup's macro, source:
// https://stackoverflow.com/questions/2324658/how-to-determine-the-version-of-the-c-standard-used-by-the-compiler
//
// C++ pre-C++98: __cplusplus is 1.
// C++98: __cplusplus is 199711L.
// C++98 + TR1: This reads as C++98 and there is no way to check that I know of.
// C++11: __cplusplus is 201103L.
// C++14: __cplusplus is 201402L.
// C++17: __cplusplus is 201703L.

int main()
{
    std::cout << "The magic template :       " << cpp_year << '\n';
    std::cout << "Bjarne Stroustrup's macro: " << __cplusplus << '\n';
    return 0;
}