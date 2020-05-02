// source
// more exception item 5
// P33
//
// the name T::A is a dependent name because it depends on the template 
// parameter T
// A name used in a template declaration or definition and that is 
// dependent on a template parameter is assumed not to name a type 
// unless the applicable name lookup finds a type name or the name is 
// qualified by the keyword typename

// compiler must see the definition of T before instantiating the 
// template
template<typename T>
void f() {
    typename T::A().run();
}

class SUT {
public:
    struct A {
        void run() {
        }
    };
};

int main() {
    f<SUT>();
    return 0;
}
