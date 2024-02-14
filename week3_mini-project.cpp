#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

//Defining a Stack Class
class Stack {
private:
    std::vector<char> elements;

public:
    void push(char element) {
        elements.push_back(element);
    }

    char pop() {
        if (isEmpty()) {
            throw std::runtime_error("Empty stack popped");
        }
        char top = elements.back();
        elements.pop_back();
        return top;
    }

    char peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Peek on empty stack");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }
};

//Defining the SymbolBalance Class
class SymbolBalance {
private:
    Stack stack;
    std::string input;

    // Utility function to check if a character is an operator
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // Utility function to check the precedence of operators
    int precedence(char c) {
        if(c == '+' || c == '-') return 1;
        else if(c == '*' || c == '/') return 2;
        return 0;
    }

public:
    void parseInput(const std::string& userInput) {
        input = userInput;
    }

    std::string checkSyntax() {
        for (char& c : input) {
            switch (c) {
                case '{':
                case '[':
                case '(':
                case '/': // For /* comments
                    stack.push(c);
                    break;
                case '}':
                    if (stack.isEmpty() || stack.pop() != '{') return "Error3: Symbol mismatch or Error2: Empty stack popped";
                    break;
                case ']':
                    if (stack.isEmpty() || stack.pop() != '[') return "Error3: Symbol mismatch or Error2: Empty stack popped";
                    break;
                case ')':
                    if (stack.isEmpty() || stack.pop() != '(') return "Error3: Symbol mismatch or Error2: Empty stack popped";
                    break;
                // Handle comment closure
                case '*': // Look ahead for '/'
                    if (input[input.find(c) + 1] == '/') {
                        if (stack.isEmpty() || stack.pop() != '/') return "Error3: Symbol mismatch or Error2: Empty stack popped";
                    }
                    break;
            }
        }
        return stack.isEmpty() ? "Symbol Balanced" : "Error1: Non-empty stack after passing";
    }

    std::string postfixExpression() {
        std::string result;
        for (char& c : input) {
            if (isalnum(c))
                result += c;
            else if (c == '(')
                stack.push(c);
            else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(')
                    result += stack.pop();
                if (!stack.isEmpty()) stack.pop(); // Remove '('
            } else if (isOperator(c)) {
                while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c))
                    result += stack.pop();
                stack.push(c);
            }
        }

        while (!stack.isEmpty())
            result += stack.pop();

        return result;
    }
};

// int main() {
//     SymbolBalance sb;
//     std::string input = "a+[b*c+(d*e+f)]*g"; // Example input
//     sb.parseInput(input);

//     std::string syntaxCheck = sb.checkSyntax();
//     std::cout << "Syntax check result: " << syntaxCheck << std::endl;

//     if (syntaxCheck == "Symbol Balanced") {
//         std::string postfix = sb.postfixExpression();
//         std::cout << "Postfix Expression: " << postfix << std::endl;
//     }

//     return 0;
// }

#include <iostream>

int main() {
    SymbolBalance sb;
    std::string input;

    std::cout << "Enter an equation: ";
    std::getline(std::cin, input); // Reads user input including spaces

    sb.parseInput(input);

    std::string syntaxCheck = sb.checkSyntax();
    std::cout << "Syntax check result: " << syntaxCheck << std::endl;

    if (syntaxCheck == "Symbol Balanced") {
        std::string postfix = sb.postfixExpression();
        std::cout << "Postfix Expression: " << postfix << std::endl;
    } else {
        std::cout << "Cannot convert to postfix due to syntax error." << std::endl;
    }

    return 0;
}
