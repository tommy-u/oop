// Citing:
// https://stackoverflow.com/questions/15441633/number-of-arguments-in-operator-overload-in-c

#include <iostream>
// There are four ways to define a binary operator such as +.

// As a free function with access to only the public members of the class:
class ElementA {
public:
  ElementA(int value) : value(value) {}
  int getValue() const { return value; }

private:
  int value;
};

// Left operand is 'a'; right is 'b'.
ElementA operator+(const ElementA &a, const ElementA &b) {
  return ElementA(a.getValue() + b.getValue());
}

// As a member function, with access to all members of the class:
class ElementB {
public:
  ElementB(int value) : value(value) {}
  int getValue() const { return value; }
  // Left operand is 'this'; right is 'other'.
  ElementB operator+(const ElementB &other) const {
    return ElementB(value + other.value);
  }

private:
  int value;
};

// As a friend function, with access to all members of the class:
class ElementC {
public:
  ElementC(int v) : value(v){};
  // Left operand is 'a'; right is 'b'.
  friend ElementC operator+(const ElementC &a, const ElementC &b) {
    return a.value + b.value;
  }

private:
  int value;
};

// As a friend function defined outside the class body—identical in behaviour to
// above.

class ElementD {
public:
  ElementD(int v) : value(v){};
  friend ElementD operator+(const ElementD &, const ElementD &);

private:
  int value;
};

ElementD operator+(const ElementD &a, const ElementD &b) {
  return a.value + b.value;
}

int main() {
  std::cout << "There are many ways to implement operator+()\n";
  std::cout << "One note is that with member functions, and instance b1 & b2:";
  std::cout << "b1 + b2\n";
  std::cout << "b1 + 2\n";
  std::cout << "But not:\n";
  std::cout << "2 + b1\n";

  ElementB b1 = 1;
  std::cout << (b1 + 2).getValue() << "\n";
  // std::cout <<  (2 + b1).getValue() << "\n";

  ElementA a1 = 1;
  std::cout << (2 + a1).getValue() << "\n";
}
