//
// Created by weining on 4/5/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <unordered_map>
#include <string>

// ran into some issues while reading c++ stl cookbook P/221
// why the map type can not be std::unordered_map (i.e. the faster hash map)?
// it also reminds me how wt's atlas organizes its node hierarchy - it uses shared_ptr for the store type instead of
// std::map<T, std::map> (as shown in the book)
// I will come back to this later

TEST_CASE ("") {
    ;
}