
// source:
// more exception item 4 P19
//
// what is trait
// a class that encapsulates a set of types and functions necessary
// for template class/function to manipulate objects of types for 
// which they are instantiated

// P20
// the idea is that a trait class is an instance of template, and is 
// used to carry extra information.
// the nice thing is that the trait class T<C> lets us record such 
// extra information about a class C, without requiring any change 
// to C

// (an example)...with user defined type, you provide suitable 
// specialization of std::char_traits<T>
//

void test_has_function_trait() {
}

int main() {
    
    return 0;
}
