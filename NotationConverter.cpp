// Notation Converter Class for Project 2
// Holds methods for infix, prefix, postfix conversions
// Justin Scandale & Tsega Amanuel

#include "NotationConverter.hpp"
#include <cctype>
#include "deque.hpp"

class NotationConverter : public NotationConverterInterface
{
private:
    // Determines which operation takes precedence and assigns a value so for example,
    // if the operator is a '+' or '-', it will return 1, if it is a '*' or '/', it will return 2
    // knowing this, we can determine which operator takes precedence
    int orderOfOperations(char c) const
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
        std::string postfix = "";
        Deque<char> operators;

        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
                // Skip whitespace
                continue;
            }
            else if (isVariable(c))
            {
                if (postfix.size() != 0)
                {
                    // Added space to output so it can appear the same as the test output cases
                    postfix += " ";
                }
                // Add operands directly to the output
                postfix += c;
            }
            else if (c == '(')
            {
                // Push '(' onto the deque
                operators.pushFront(c);
            }
            else if (c == ')')
            {
                // Pop operators from the deque until '(' is encountered
                while (!operators.empty() && operators.front() != '(')
                {
                    // Added space to output so it can appear the same as the test output cases
                    postfix += " ";
                    postfix += operators.front();
                    operators.popFront();
                }
                if (!operators.empty() && operators.front() == '(')
                {
                    operators.popFront();
                }
                else
                {
                    // Unmatched infix expression
                    return "invalid string";
                }
            }
            else if (isOperator(c))
            {
                // Pop operators from the deque while they have higher or equal precedence
                while (!operators.empty() && orderOfOperations(operators.front()) >= orderOfOperations(c))
                {
                    // Added space to output so it can appear the same as the test output cases
                    postfix += " ";
                    postfix += operators.front();
                    operators.popFront();
                }
                operators.pushFront(c);
            }
            else
            {
                return "invalid string";
            }
        }

        // Pop remaining operators from the deque and add them to the output
        while (!operators.empty())
        {
            if (operators.front() == '(')
            {
                return "invalid string";
            }
            // Added space to output so it can appear the same as the test output cases
            postfix += " ";
            postfix += operators.front();
            operators.popFront();
        }

        return postfix;
    }

    std::string infixToPrefix(std::string inStr) override
    {
        std::string prefix = "";
        Deque<char> operators;
        // Reverse the input string to make it easier to convert to prefix
        std::reverse(inStr.begin(), inStr.end());

        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
                continue; // Skip whitespace
            }
            else if (isVariable(c))
            {
                // Added space to output so it can appear the same as the test output cases
                prefix += " ";
                prefix += c;
            }
            else if (c == ')')
            {
                // Push ')' onto the deque
                operators.pushFront(c);
            }
            else if (c == '(')
            {
                // Pop operators from the deque until ')' is encountered
                while (!operators.empty() && operators.front() != ')')
                {
                    // Added space to output so it can appear the same as the test output cases
                    prefix += " ";
                    prefix += operators.front();
                    operators.popFront();
                }
                if (!operators.empty() && operators.front() == ')')
                {
                    // Pop the ')' from the deque
                    operators.popFront();
                }
                else
                {
                    return "invalid string";
                }
            }
            else if (isOperator(c))
            {
                // Pop operators from the deque while they have higher or equal precedence
                while (!operators.empty() && orderOfOperations(operators.front()) > orderOfOperations(c))
                {
                    // Added space to output so it can appear the same as the test output cases
                    prefix += " ";
                    prefix += operators.front();
                    operators.popFront();
                }
                // Push the current operator onto the deque
                operators.pushFront(c);
            }
            else
            {
                // Invalid character
                return "invalid string";
            }
        }

        // Pop remaining operators from the deque and add them to the output
        while (!operators.empty())
        {
            if (operators.front() == ')')
            {
                // Unmatched ')'
                return "invalid string";
            }
            prefix += operators.front();
            operators.popFront();
        }

        // Reverse the prefix expression to get the correct order
        std::reverse(prefix.begin(), prefix.end());

        return prefix;
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
