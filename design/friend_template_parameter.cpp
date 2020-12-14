//
// Created by weining on 2/5/20.
//

// complete guide L7847
// C++11 also added syntax to make a template parameter a friend

template<typename T>
class SUT {
    friend T;
};
