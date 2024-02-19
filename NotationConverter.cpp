#include "NotationConverter.hpp"
#include <cctype>
#include "deque.hpp"

class NotationConverter : public NotationConverterInterface {
public:

    bool isVariable(const char chr) const {
        return std::isalpha(static_cast<unsigned char>(chr)); 
    }

    bool isWhiteSpace(const char chr) const{
        return std::isspace(static_cast<unsigned char>(chr));
    }

    bool isOperator(const char chr) const {
        return chr == '+' || chr == '-' || chr=='/' || chr=='*';
    }

    std::string postfixToInfix(std::string inStr) override {
        
        Deque<std::string> myDeque;

        for(char c : inStr)
        {   
            if(isWhiteSpace(c)) {} //do nothing if whitespace
            else if(isVariable(c)) {myDeque.pushFront(std::string(1,c));} //put varibale onto front of deque
            else if (isOperator(c)) {
                if(myDeque.getSize()<2) {return "invalid string";} //invalid operator

                else{
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = '(' + variable2 + ' ' + c + ' ' + variable1 + ')';
                    myDeque.pushFront(result);
                }
            }
            //invalid character
            else
            {return "invalid string";}
        }

        if(myDeque.getSize()!=1) {return "invalid string";} //return if expression was invalid
        return myDeque.front();
    }

    std::string postfixToPrefix(std::string inStr) override {
        
        Deque<std::string> myDeque;

        for(char c : inStr)
        {   
            if(isWhiteSpace(c)) {} //do nothing if whitespace
            else if(isVariable(c)) {myDeque.pushFront(std::string(1,c));} //put varibale onto front of deque
            else if (isOperator(c)) {
                if(myDeque.getSize()<2) {return "invalid string";} //invalid operator

                else{
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = std::string(1,c) + ' ' + variable2 +  ' ' + variable1 ;
                    myDeque.pushFront(result);
                }
            }
            //invalid character
            else
            {return "invalid string";}
        }

        if(myDeque.getSize()!=1) {return "invalid string";} //return if expression was invalid
        return myDeque.front();
    }

    std::string infixToPostfix(std::string inStr) override {
                return "null";

    }

    std::string infixToPrefix(std::string inStr) override {
                return "null";

       
    }

    std::string prefixToInfix(std::string inStr) override {        

        Deque<std::string> myDeque;

        for(int i = inStr.size()-1; i>=0;i--)
        {   
            if(isWhiteSpace(inStr[i])) {} //do nothing if whitespace
            else if(isVariable(inStr[i])) {myDeque.pushFront(std::string(1,inStr[i]));} //put varibale onto front of deque
            else if (isOperator(inStr[i])) {
                if(myDeque.getSize()<2) {return "invalid string";} //invalid operator

                else{
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = '(' + variable1 + ' ' + inStr[i] + ' ' +variable2 + ')';
                    myDeque.pushFront(result);
                }
            }
            //invalid character
            else
            {return "invalid string";}
        }
        if(myDeque.getSize()!=1) {return "invalid string";} //return if expression was invalid
        return myDeque.front();
   
    }

    std::string prefixToPostfix(std::string inStr) override {

        Deque<std::string> myDeque;

        for(int i = inStr.size()-1; i>=0;i--)
        {   
            if(isWhiteSpace(inStr[i])) {} //do nothing if whitespace
            else if(isVariable(inStr[i])) {myDeque.pushFront(std::string(1,inStr[i]));} //put varibale onto front of deque
            else if (isOperator(inStr[i])) {
                if(myDeque.getSize()<2) {return "invalid string";} //invalid operator

                else{
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = variable1 + ' ' + variable2 + ' ' + inStr[i];
                    myDeque.pushFront(result);
                }
            }
            //invalid character
            else
            {return "invalid string";}
        }
        if(myDeque.getSize()!=1) {return "invalid string";} //return if expression was invalid
        return myDeque.front();

        
    }


};
