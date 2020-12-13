//
// Created by weining on 13/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>
#include <type_traits>
#include <variant>

// FP in c++ P/228
// decltype() is quite useful;
// it enables me to probe the type of an expression - recall that in Scala's
// everything is an expression

// this has a serious limitation: decltype(Element()) will return the wrong
// result for variant<T, Q> - see the right answer below
template <typename Collection> bool canBeFoldedIfEmpty(const Collection &xs) {
  using Element = std::remove_cv<decltype(*xs.begin())>;
  if constexpr (std::is_same_v<decltype(Element()), Element>) {
    return true;
  } else {
    return false;
  }
}

// FP in c++ P/229
// decltype vs std::declval()
// declval<T>() takes a type T and pretends to create an instance of that type
// so you can use it in metafunctions when you need values instead of types -
// which is often the case when you use decltype

using Result = std::variant<std::string, std::vector<int>>;

// FP in c++ P/230
// a helper type-level function that works for both default-constructable
// types and those that are not.
template <typename Collection>
using contained_type_t = std::remove_cv_t<
    std::remove_reference_t<decltype(*std::begin(std::declval<Collection>()))>>;

TEST_CASE("probe container element type") {
  std::vector<int> xs;
  CHECK(canBeFoldedIfEmpty(xs));

  std::vector<Result> rs;
  constexpr bool canBeDefaultConstructed =
      std::is_same_v<decltype(std::declval<std::vector<Result>>()),
                     std::vector<Result>>;
  static_assert(!canBeDefaultConstructed, ".");

  static_assert(std::is_same_v<contained_type_t<std::vector<Result>>, Result>,
                ".");
}