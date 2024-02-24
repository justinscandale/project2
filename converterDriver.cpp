#include "NotationConverter.hpp"
#include "NotationConverter.cpp"

using namespace std;

int main()

{
  const std::string infix1 = "(A + B) ";
  const std::string infix2 = "((X + B) * (Y - D))";
  const std::string infix3 = "(((A + B) / (X + Y)) - R)";

  const std::string prefix1 = "+ / * x y g h";
  const std::string prefix2 = "-    /  x  y  g"; // Multiple Spaces Between Letters and Operators
  const std::string prefix3 = "- / x y * a b";

  const std::string postfix1 = "X Y + A B + *";
  const std::string postfix2 = "V C +";
  const std::string postfix3 = "H W * R Q - /";

  NotationConverter nc;

  nc.infixToPrefix(infix1) ; // should print "+ A B"
  nc.infixToPrefix(infix2) ; // should print "* + X B - Y D"
  nc.infixToPrefix(infix3) ; // should print "- / + A B +   nc.infixToPostfix(infixl; // should print "A B +"
  nc.infixToPostfix(infix2) ; // should print "X B + Y D - *"
  nc.infixToPostfix(infix3) ; // should print "A B + X Y + / R -"

  nc.prefixToPostfix(prefix1); // should print "x y * g / h +"
  nc.prefixToPostfix(prefix2); // should print "x y / g -"
  nc.prefixToPostfix(prefix3); // should print "x y / a b * -"

  nc.prefixToInfix(prefix1); // should print "(((x * y) / g) + h)"
  nc.prefixToInfix(prefix2); // should print "((x / y) - g)"
  nc.prefixToInfix(prefix3); // should print "((x / y) - (a * b))"

  nc.postfixToInfix(postfix1); // should print "((X + Y) * (A + B))"
  nc.postfixToInfix(postfix2); // should print "(V + C)"
  nc.postfixToInfix(postfix3); // should print "((H * W) / (R - Q))"

  nc.postfixToPrefix(postfix1); // should print "* + X Y + A B"
  nc.postfixToPrefix(postfix2); // should print "+ V C"
  nc.postfixToPrefix(postfix3); // should print "/ * H W - R Q"

  return 0;
}