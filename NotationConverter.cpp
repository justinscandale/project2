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
    bool isVariable(const char chr) const
    {
        return std::isalpha(static_cast<unsigned char>(chr));
    }

    bool isWhiteSpace(const char chr) const
    {
        return std::isspace(static_cast<unsigned char>(chr));
    }

    bool isOperator(const char chr) const
    {
        return chr == '+' || chr == '-' || chr == '/' || chr == '*';
    }

    std::string postfixToInfix(std::string inStr) override
    {
        Deque<std::string> myDeque;

        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
            } // do nothing if whitespace
            else if (isVariable(c))
            {
                myDeque.pushFront(std::string(1, c));
            } // put varibale onto front of deque
            else if (isOperator(c))
            {
                if (myDeque.getSize() < 2)
                {
                    return "invalid string";
                } // invalid operator

                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = '(' + variable2 + ' ' + c + ' ' + variable1 + ')';
                    myDeque.pushFront(result);
                }
            }
            // invalid character
            else
            {
                return "invalid string";
            }
        }

        if (myDeque.getSize() != 1)
        {
            return "invalid string";
        } // return if expression was invalid
        return myDeque.front();
    }

    std::string postfixToPrefix(std::string inStr) override
    {

        Deque<std::string> myDeque;

        for (char c : inStr)
        {
            if (isWhiteSpace(c))
            {
            } // do nothing if whitespace
            else if (isVariable(c))
            {
                myDeque.pushFront(std::string(1, c));
            } // put varibale onto front of deque
            else if (isOperator(c))
            {
                if (myDeque.getSize() < 2)
                {
                    return "invalid string";
                } // invalid operator

                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = std::string(1, c) + ' ' + variable2 + ' ' + variable1;
                    myDeque.pushFront(result);
                }
            }
            // invalid character
            else
            {
                return "invalid string";
            }
        }

        if (myDeque.getSize() != 1)
        {
            return "invalid string";
        } // return if expression was invalid
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

    std::string prefixToInfix(std::string inStr) override
    {

        Deque<std::string> myDeque;

        for (int i = inStr.size() - 1; i >= 0; i--)
        {
            if (isWhiteSpace(inStr[i]))
            {
            } // do nothing if whitespace
            else if (isVariable(inStr[i]))
            {
                myDeque.pushFront(std::string(1, inStr[i]));
            } // put varibale onto front of deque
            else if (isOperator(inStr[i]))
            {
                if (myDeque.getSize() < 2)
                {
                    return "invalid string";
                } // invalid operator

                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = '(' + variable1 + ' ' + inStr[i] + ' ' + variable2 + ')';
                    myDeque.pushFront(result);
                }
            }
            // invalid character
            else
            {
                return "invalid string";
            }
        }
        if (myDeque.getSize() != 1)
        {
            return "invalid string";
        } // return if expression was invalid
        return myDeque.front();
    }

    std::string prefixToPostfix(std::string inStr) override
    {

        Deque<std::string> myDeque;

        for (int i = inStr.size() - 1; i >= 0; i--)
        {
            if (isWhiteSpace(inStr[i]))
            {
            } // do nothing if whitespace
            else if (isVariable(inStr[i]))
            {
                myDeque.pushFront(std::string(1, inStr[i]));
            } // put varibale onto front of deque
            else if (isOperator(inStr[i]))
            {
                if (myDeque.getSize() < 2)
                {
                    return "invalid string";
                } // invalid operator

                else
                {
                    std::string variable1 = myDeque.front();
                    myDeque.popFront();
                    std::string variable2 = myDeque.front();
                    myDeque.popFront();

                    std::string result = variable1 + ' ' + variable2 + ' ' + inStr[i];
                    myDeque.pushFront(result);
                }
            }
            // invalid character
            else
            {
                return "invalid string";
            }
        }
        if (myDeque.getSize() != 1)
        {
            return "invalid string";
        } // return if expression was invalid
        return myDeque.front();
    }
};
