#include "deque.hpp"
#include <iostream>
#include <string>

//Deque new_deque = new Deque();

int main(){

Deque<std::string> myDeque;
myDeque.pushFront("hello1");
myDeque.pushFront("hello2");

std::cout << myDeque.back();
return 0;

}

