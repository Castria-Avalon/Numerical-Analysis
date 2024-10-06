#ifndef SCICAL_HPP
#define SCICAL_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <functional>
#include <cctype>
#include <map>
#include <vector>
#include <stack>

// Math function class Function
class Function
{
public:
    Function(const std::string &s)
    {
        expression = s;
    }

    double derivative(double x, double h = 1e-5)
    {
        return (eval(x + h) - eval(x - h)) / (2 * h);
    }

    double operator()(double x)
    {
        return eval(x);
    }

private:
    std::string expression;

    std::string replaceX(double x)
    {
        std::ostringstream oss;
        size_t i = 0;
        while (i < expression.size())
        {
            if (expression.substr(i, 3) == "exp")
            {
                oss << "exp";
                i += 3;
            }
            else if (expression[i] == 'x')
            {
                oss << x;
                i++;
            }
            else
            {
                oss << expression[i];
                i++;
            }
        }
        return oss.str();
    }

    // Tokenizer
    std::vector<std::string> tokenize(const std::string &expr)
    {
        std::vector<std::string> tokens;
        std::string current;
        for (size_t i = 0; i < expr.size(); ++i)
        {
            char ch = expr[i];
            if (std::isspace(ch))
            {
                continue;
            }
            else if (std::isalpha(ch))
            {
                current += ch;
            }
            else if (std::isdigit(ch) || ch == '.')
            {
                current += ch;
            }
            else if (ch == '(' || ch == ')' || ch == ',' || ch == '+' || ch == '*' || ch == '/')
            {
                if (!current.empty())
                {
                    tokens.push_back(current);
                    current.clear();
                }
                tokens.push_back(std::string(1, ch));
            }
            else if (ch == '-')
            {
                // check if the '-' is a unary operator
                if (current.empty() && (tokens.empty() || tokens.back() == "(" || tokens.back() == "," || tokens.back() == "+" || tokens.back() == "-" || tokens.back() == "*" || tokens.back() == "/"))
                {
                    current += ch;
                }
                else
                {
                    if (!current.empty())
                    {
                        tokens.push_back(current);
                        current.clear();
                    }
                    tokens.push_back(std::string(1, ch));
                }
            }
        }
        if (!current.empty())
        {
            tokens.push_back(current);
        }
        return tokens;
    }

    double applyFunc(double val, const std::string &func)
    {
        if (func == "sin")
            return sin(val);
        if (func == "cos")
            return cos(val);
        if (func == "tan")
            return tan(val);
        if (func == "asin")
            return asin(val);
        if (func == "acos")
            return acos(val);
        if (func == "atan")
            return atan(val);
        if (func == "exp")
            return exp(val);
        return val;
    }

    double applyOp(double a, double b, const std::string &op)
    {
        if (op == "+")
            return a + b;
        if (op == "-")
            return a - b;
        if (op == "*")
            return a * b;
        if (op == "/")
            return a / b;
        if (op == "pow")
            return pow(a, b);
        return 0;
    }

    int getPrecedence(const std::string &op)
    {
        if (op == "+" || op == "-")
            return 1;
        if (op == "*" || op == "/")
            return 2;
        if (op == "sin" || op == "cos" || op == "tan" ||
            op == "asin" || op == "acos" || op == "atan" ||
            op == "exp" || op == "pow")
            return 3;
        return 0;
    }

    // Transform infix to postfix
    std::vector<std::string> toPostfix(const std::vector<std::string> &tokens)
    {
        std::vector<std::string> output;
        std::stack<std::string> ops;

        for (const std::string &token : tokens)
        {
            if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1])))
            {
                output.push_back(token);
            }
            else if (token == "(")
            {
                ops.push(token);
            }
            else if (token == ")")
            {
                while (!ops.empty() && ops.top() != "(")
                {
                    output.push_back(ops.top());
                    ops.pop();
                }
                if (!ops.empty())
                    ops.pop(); // pop "("
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/" ||
                     token == "sin" || token == "cos" || token == "tan" ||
                     token == "asin" || token == "acos" || token == "atan" ||
                     token == "exp" || token == "pow")
            {
                while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(token))
                {
                    output.push_back(ops.top());
                    ops.pop();
                }
                ops.push(token);
            }
        }
        while (!ops.empty())
        {
            output.push_back(ops.top());
            ops.pop();
        }

        return output;
    }

    double evalPostfix(const std::vector<std::string> &postfix)
    {
        std::stack<double> values;

        for (const std::string &token : postfix)
        {
            if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1])))
            {
                values.push(std::stod(token));
            }
            else if (token == "sin" || token == "cos" || token == "tan" ||
                     token == "asin" || token == "acos" || token == "atan" ||
                     token == "exp")
            {
                double val = values.top();
                values.pop();
                values.push(applyFunc(val, token));
            }
            else
            {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                values.push(applyOp(val1, val2, token));
            }
        }

        return values.top();
    }

    double eval(double x)
    {
        std::string s = replaceX(x);
        std::vector<std::string> tokens = tokenize(s);
        std::vector<std::string> postfix = toPostfix(tokens);
        return evalPostfix(postfix);
    }
};
#endif // SCICAL_HPP