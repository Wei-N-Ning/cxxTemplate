//
// Created by wein on 5/6/18.
//

#include <iostream>

#define ALIGNMENT_MAX 16

template< int N, int C = 1 >
struct RoundUpPow2
{
    enum { value = RoundUpPow2< N/2, C*2 >::value };
};

template< int C >
struct RoundUpPow2< 0, C >
{
    enum { value = ( C > ALIGNMENT_MAX ) ? ALIGNMENT_MAX : C };
};

template< typename T, int W >
struct Align
{
    enum { value = RoundUpPow2< sizeof( T ) * W - 1 >::value };
};

template< typename T >
struct Align< T, 0 >
{
    enum { value = sizeof( T ) };
};

int main(int argc, char **argv) {
    struct Align<char, 7> unnamed;
    std::cout << unnamed.value << std::endl;
    // char, 15 -> 16
    // char, 7 -> 8
    // uint8_t, 3 -> 4
    // uint32_t, 3 -> 16

    // the resulting value is available at compile time
    char ignore[unnamed.value];
    return 0;
}