//Notation Converter Class for Project 2
//Holds methods for infix, prefix, postfix conversions
//Justin Scandale & Tsega Amanuel

#include "NotationConverter.hpp"
#include <cctype>
#include "deque.hpp"

class NotationConverter : public NotationConverterInterface
{
private:
    int precedence(char c) const
    {
        if (c == '+' || c == '-')
        {
            return 1;
        }
        else if (c == '*' || c == '/')
        {
            return 2;
        }
        return 0;
    }

public:
    //checks if character is variable (alphabetic letter) returns boolean
    bool isVariable(const char chr) const
    {
        return std::isalpha(static_cast<unsigned char>(chr));
    }

    //checks if character is whitespace (' ') returns boolean
    bool isWhiteSpace(const char chr) const
    {
        return std::isspace(static_cast<unsigned char>(chr));
    }

    //checks if character is operator (+,-,/,*) returns boolean
    bool isOperator(const char chr) const
    {
        return chr == '+' || chr == '-' || chr == '/' || chr == '*';
    }

    //method to convert postfix -> infix notation
    std::string postfixToInfix(std::string inStr) override
    {
        Deque<std::string> myDeque;

        //iterate through each character in inStr
        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
                // do nothing if whitespace
            } 
            else if (isVariable(c))
            {
                myDeque.pushFront(std::string(1, c)); // put varibale onto front of deque
            } 
            else if (isOperator(c))
            {
                //check if deque contains enough elements to perform operations on
                if (myDeque.getSize() < 2)
                {
                    return "invalid string"; //invalid operator
                } 

                //peform notation conversion
                else
                {   
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    //result = first two elements on deque with operator C between them
                    std::string result = '(' + variable2 + ' ' + c + ' ' + variable1 + ')';
                    //push result string back onto front of deque
                    myDeque.pushFront(result);
                }
            }
            //if character is invalid 
            else
            {
                return "invalid string";
            }
        }
        
        //check if deque has more than one element on it after all operations 
        if (myDeque.getSize() != 1)
        {
            return "invalid string"; // return if expression was invalid
        } 
        //return front of deque/ completed conversion
        return myDeque.front();
    }

    //method to convert postfix -> prefix notation
    std::string postfixToPrefix(std::string inStr) override
    {

        Deque<std::string> myDeque;

        //iterate through each character in inStr
        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
                // do nothing if whitespace
            } 
            else if (isVariable(c))
            {
                myDeque.pushFront(std::string(1, c)); // put varibale onto front of deque
            } 
            else if (isOperator(c))
            {
                //check if deque contains enough elements to perform operations on
                if (myDeque.getSize() < 2)
                {
                    return "invalid string"; // invalid operator
                } 

                //perform notation conversion
                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    //result = first two elements on deque with oeprator C between them
                    std::string result = std::string(1, c) + ' ' + variable2 + ' ' + variable1;
                    //push result string back onto front of deque
                    myDeque.pushFront(result);
                }
            }
            //if character is invalid
            else
            {
                return "invalid string";
            }
        }

        //check if deque has more than one element on it after all operations 
        if (myDeque.getSize() != 1)
        {
            return "invalid string"; // return if expression was invalid
        } 
        //return front of deque/ completed conversion
        return myDeque.front();
    }

    std::string infixToPostfix(std::string inStr) override
    {
        std::string postfixExpression = "";
        Deque<char> operators;

        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
                continue; // Skip whitespace
            }
            else if (isVariable(c))
            {
                if(postfixExpression.size()!=0)
                {postfixExpression += " ";} // Add operands directly to the output
                postfixExpression += c; // Add operands directly to the output
            }
            else if (c == '(')
            {
                operators.pushFront(c); // Push '(' onto the deque
            }
            else if (c == ')')
            {
                // Pop operators from the deque until '(' is encountered
                while (!operators.empty() && operators.front() != '(')
                {
                    postfixExpression += " ";
                    postfixExpression += operators.front();
                    operators.popFront();
                }
                if (!operators.empty() && operators.front() == '(')
                {
                    operators.popFront(); // Discard '('
                }
                else
                {
                    return "invalid string"; // Unmatched ')'
                }
            }
            else if (isOperator(c))
            {
                // Pop operators from the deque while they have higher or equal precedence
                while (!operators.empty() && precedence(operators.front()) >= precedence(c))
                {
                    postfixExpression += " ";
                    postfixExpression += operators.front();
                    operators.popFront();
                }
                operators.pushFront(c); // Push the current operator onto the deque
            }
            else
            {
                return "invalid string"; // Invalid character
            }
        }

        // Pop remaining operators from the deque and add them to the output
        while (!operators.empty())
        {
            if (operators.front() == '(')
            {
                return "invalid string"; // Unmatched '('
            }
            postfixExpression += " ";
            postfixExpression += operators.front();
            operators.popFront();
        }

        return postfixExpression;
    }

    std::string infixToPrefix(std::string inStr) override
    {
        std::string prefixExpression = "";
        Deque<char> operators;
        std::reverse(inStr.begin(), inStr.end()); // Reverse the input string to facilitate infix to prefix conversion

        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
                continue; // Skip whitespace
            }
            else if (isVariable(c))
            {
                prefixExpression += " ";
                prefixExpression += c; // Add operands directly to the output
            }
            else if (c == ')')
            {
                operators.pushFront(c); // Push ')' onto the deque
            }
            else if (c == '(')
            {
                // Pop operators from the deque until ')' is encountered
                while (!operators.empty() && operators.front() != ')')
                {
                    prefixExpression += " ";
                    prefixExpression += operators.front();
                    operators.popFront();
                }
                if (!operators.empty() && operators.front() == ')')
                {
                    operators.popFront(); // Discard ')'
                }
                else
                {
                    return "invalid string"; // Unmatched '('
                }
            }
            else if (isOperator(c))
            {
                // Pop operators from the deque while they have higher or equal precedence
                while (!operators.empty() && precedence(operators.front()) > precedence(c))
                {
                    prefixExpression += " ";
                    prefixExpression += operators.front();
                    operators.popFront();
                }
                operators.pushFront(c); // Push the current operator onto the deque
            }
            else
            {
                return "invalid string"; // Invalid character
            }
        }

        // Pop remaining operators from the deque and add them to the output
        while (!operators.empty())
        {
            if (operators.front() == ')')
            {
                return "invalid string"; // Unmatched ')'
            }
            prefixExpression += operators.front();
            operators.popFront();
        }

        // Reverse the prefix expression to get the correct order
        std::reverse(prefixExpression.begin(), prefixExpression.end());

        return prefixExpression;
    }

    //method to convert prefix-> infix
    std::string prefixToInfix(std::string inStr) override
    {

        Deque<std::string> myDeque;

        //iterate through each character in reverse order
        for (int i = inStr.size() - 1; i >= 0; i--)
        {
            if (isWhiteSpace(inStr[i]))
            {
                // do nothing if whitespace
            } 
            else if (isVariable(inStr[i]))
            {
                myDeque.pushFront(std::string(1, inStr[i])); // put varibale onto front of deque
            } 
            else if (isOperator(inStr[i]))
            {
                //check if deque contains enough elements to perform oeprations on
                if (myDeque.getSize() < 2)
                {
                    return "invalid string"; // invalid operator
                } 

                //perform notation conversion
                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();
                    
                    //result = first two variablaes on deque with current operator 
                    std::string result = '(' + variable1 + ' ' + inStr[i] + ' ' + variable2 + ')';
                    myDeque.pushFront(result);
                }
            }
            //if character is invalid 
            else
            {
                return "invalid string";
            }
        }

        //check if deque has more than one element on it after all operations
        if (myDeque.getSize() != 1)
        {
            return "invalid string"; // return if expression was invalid
        } 
        //return front of deque/ completed conversion
        return myDeque.front();
    }

    //method to convert prefix -> postfix 
    std::string prefixToPostfix(std::string inStr) override
    {

        Deque<std::string> myDeque;

        //iterate through each character in reverse order
        for (int i = inStr.size() - 1; i >= 0; i--)
        {
            if (isWhiteSpace(inStr[i]))
            {
                // do nothing if whitespace
            } 
            else if (isVariable(inStr[i]))
            {
                myDeque.pushFront(std::string(1, inStr[i])); // put varibale onto front of deque
            } 
            else if (isOperator(inStr[i]))
            {
                //check if deque contains enough elements to perform oeprations on
                if (myDeque.getSize() < 2)
                {
                    return "invalid string"; // invalid operator
                } 

                //perform notation conversion
                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    //result = first two variables on deque with current operator
                    std::string result = variable1 + ' ' + variable2 + ' ' + inStr[i];
                    myDeque.pushFront(result);
                }
            }
            //if character is invalid 
            else
            {
                return "invalid string";
            }
        }

        //check if deque has more than one element on it after all operations
        if (myDeque.getSize() != 1)
        {
            return "invalid string"; // return if expression was invalid
        } 
        //return front of deque/ completed conversion
        return myDeque.front();
    }
};
