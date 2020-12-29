#!/usr/bin/env bash

set -euo pipefail

: <<"REFERENCE"
---------- compiler is g++-10, flag is -std=c++98 ----------
The magic template :       19982003
Bjarne Stroustrup's macro: 199711
---------- compiler is g++-10, flag is -std=c++03 ----------
The magic template :       19982003
Bjarne Stroustrup's macro: 199711
---------- compiler is g++-10, flag is -std=c++11 ----------
The magic template :       2011
Bjarne Stroustrup's macro: 201103
---------- compiler is g++-10, flag is -std=c++14 ----------
The magic template :       2014
Bjarne Stroustrup's macro: 201402
---------- compiler is g++-10, flag is -std=c++17 ----------
The magic template :       2017
Bjarne Stroustrup's macro: 201703
---------- compiler is g++-10, flag is -std=c++20 ----------
The magic template :       2020
Bjarne Stroustrup's macro: 201709
---------- compiler is clang++-10, flag is -std=c++98 ----------
The magic template :       19982003
Bjarne Stroustrup's macro: 199711
---------- compiler is clang++-10, flag is -std=c++03 ----------
The magic template :       19982003
Bjarne Stroustrup's macro: 199711
---------- compiler is clang++-10, flag is -std=c++11 ----------
The magic template :       2011
Bjarne Stroustrup's macro: 201103
---------- compiler is clang++-10, flag is -std=c++14 ----------
The magic template :       2014
Bjarne Stroustrup's macro: 201402
---------- compiler is clang++-10, flag is -std=c++17 ----------
The magic template :       2017
Bjarne Stroustrup's macro: 201703
---------- compiler is clang++-10, flag is -std=c++20 ----------
The magic template :       2020
Bjarne Stroustrup's macro: 202002
REFERENCE

doCompile() {
  local compiler="${1:?missing compiler name}"
  local output="/tmp/check_cxx_standard_version.exe"
  for ver in "c++98" "c++03" "c++11" "c++14" "c++17" "c++20"; do
    echo "---------- compiler is ${compiler}, flag is -std=${ver} ----------"
    ${compiler} -std="${ver}" ./check_cxx_standard_version.cpp -o "${output}"
    ${output}
  done
}

doCompile "g++-10"
doCompile "clang++-10"
