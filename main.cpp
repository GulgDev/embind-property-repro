#include <emscripten/bind.h>

using namespace emscripten;

class Thing {
public:
    int value;

    Thing() : value(0) {}
};

class MyClass {
public:
    Thing *thing;

    Thing* getThing() const {
        return thing;
    }

    void setThing(Thing* thing) {
        this->thing = thing;
    }
};

EMSCRIPTEN_BINDINGS(Example) {
    class_<Thing>("Thing")
        .constructor()
        .property("value", &Thing::value);

    class_<MyClass>("MyClass")
        .property("thing", // error: Implicitly binding raw pointers is illegal.
                  &MyClass::getThing,
                  &MyClass::setThing,
                  allow_raw_pointers(),
                  return_value_policy::reference());
}