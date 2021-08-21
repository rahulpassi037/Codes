#include <bits/stdc++.h>

using namespace std;

// This function defines priority of operators
int getPriority(char c)
{
    if(c=='-' || c=='+') return 1;
    else if(c=='*' || c=='/') return 2;
    else if(c=='^') return 3;
    return 0;
}

// This checks if a character is an operator
bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

// This function performs operation on two operands
int applyOp(int a, int b, char op)
{
    switch(op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    
    return -1;
}

// This function calculates value of an infix expression
int infixEvaluate(string infix) 
{
    // Maintain two stacks for values and operators
    stack <int> values;
    stack <char> ops;

    // Traverse over infix string
    for(int i = 0; i < infix.length(); i++)
    {
        // Skip if character is space
        if(infix[i] == ' ') continue;
        
        // Push opening brackets to operator stack
        else if(infix[i] == '(') ops.push(infix[i]);
        
        // Get value of numbers and push them to operand stack
        else if(isdigit(infix[i]))
        {
            int val = 0;

            while(i < infix.length() && isdigit(infix[i]))
            {
                val = (val*10) + (infix[i]-'0');
                i++;
            }

            values.push(val);
            i--;
        }
        
        // When closing braces are encountered
        // Calculate the expression within the braces
        else if(infix[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.empty()?0:values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            if(!ops.empty()) ops.pop();
        }
        
        // If an operator is encountered
        // Evaluate all higher precedence operators lying on operator stack
        // Then push this operator to stack
        else
        {
            while(!ops.empty() && getPriority(ops.top()) >= getPriority(infix[i]))
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.empty()?0:values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(infix[i]);
        }
    }
    
    // Evaluate all remaining operators on operator stack
    while(!ops.empty())
    {
        int val2 = values.top();
        values.pop();

        int val1 = values.empty()?0:values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // The topmost value on stack is the ans
    return values.top();
}

// This function converts infix expression to prefix expression
string infixToPrefix(string infix)
{
    // Maintain 2 stacks, for operator and operand
    stack<char> operators;
    stack<string> operands;
 
    // Traverse the infix string
    for(int i=0; i<infix.size(); i++)
    {
        // Skip if there is space
        if(infix[i]==' ') continue;

        // Push opening braces to operator stack
        if(infix[i]=='(') operators.push(infix[i]);

        // For closing braces find the corresponding opening braces
        // Evaluate the expression between it
        else if(infix[i]==')')
        {
            while(!operators.empty() && operators.top()!='(')
            {
                string op1 = operands.top();
                operands.pop();
                string op2 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string tmp = op + op2 + op1;
                operands.push(tmp);
            }
            operators.pop();
        }
        
        // If the token is an operand
        // Get the full value of operand and push to stack
        else if(!isOperator(infix[i]))
        {
            string tmp;
            while(i<infix.size() && (isdigit(infix[i]) || isalpha(infix[i])))
            {
                tmp.push_back(infix[i]);
                i++;
            }
            operands.push(tmp);
            i--;
        }
        
        // When we get operator we process all operators of higher priority
        // lying on stack
        else
        {
            while(!operators.empty() && getPriority(infix[i])<=getPriority(operators.top()))
            {
                string op1 = operands.top();
                operands.pop();
                string op2 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string tmp = op + op2 + op1;
                operands.push(tmp);
            }
            operators.push(infix[i]);
        }
    }
    
    // While there are some operators left process them
    while(!operators.empty())
    {
        string op1 = operands.top();
        operands.pop();
        string op2 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        string tmp = op + op2 + op1;
        operands.push(tmp);
    }

    return operands.top();
}

// This function calculates postfix from infix expression
string infixToPostfix(string infix)
{
    // Maintain 2 stacks, for operator and operand
    stack<char> operators;
    stack<string> operands;

    // Traverse the infix string
    for(int i=0; i<infix.size(); i++)
    {
        // Skip if there is space
        if(infix[i]==' ') continue;

        // Push opening braces to operator stack
        if(infix[i]=='(') operators.push(infix[i]);

        // For closing braces find the corresponding opening braces
        // Evaluate the expression between it
        else if(infix[i]==')')
        {
            while(!operators.empty() && operators.top()!='(')
            {
                string op1 = operands.top();
                operands.pop();
                string op2 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string tmp = op2 + op1 + op;
                operands.push(tmp);
            }
            operators.pop();
        }

        // If the token is an operand
        // Get the full value of operand and push to stack
        else if(!isOperator(infix[i]))
        {
            string tmp;
            while(i<infix.size() && (isdigit(infix[i]) || isalpha(infix[i])))
            {
                tmp.push_back(infix[i]);
                i++;
            }
            operands.push(tmp);
            i--;
        }

        // When we get operator we process all operators of higher priority
        // lying on stack
        else
        {
            while(!operators.empty() && getPriority(infix[i])<=getPriority(operators.top()))
            {
                string op1 = operands.top();
                operands.pop();
                string op2 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string tmp = op2 + op1 + op;
                operands.push(tmp);
            }
            operators.push(infix[i]);
        }
    }

    // While there are some operators left process them
    while(!operators.empty())
    {
        string op1 = operands.top();
        operands.pop();
        string op2 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        string tmp = op2 + op1 + op;
        operands.push(tmp);
    }

    return operands.top();
}

// This function evaluates a postfix expression
// This works for single digit numbers only as of now
int postfixEvaluate(string postfix)
{
    stack<int> operands;

    for(int i=0; i<postfix.size(); i++)
    {
        if(isdigit(postfix[i])) operands.push(postfix[i]-'0');
        else
        {
            int op1 = operands.top();
            operands.pop();
            int op2 = operands.top();
            operands.pop();
            operands.push(applyOp(op2, op1, postfix[i]));
        }
    }

    return operands.top();
}

// This function converts postfix to infix
// This works for single digit numbers only as of now
string postfixToInfix(string postfix)
{
    stack<string> operands;

    for(int i=0; i<postfix.size(); i++)
    {
        if(isdigit(postfix[i])) operands.push(to_string(postfix[i]-'0'));
        else
        {
            string op1 = operands.top();
            operands.pop();
            string op2 = operands.top();
            operands.pop();
            operands.push("(" + op2 + postfix[i] + op1 + ")");
        }
    }

    return operands.top();
}

// This function converts postfix to prefix
// This works for single digit numbers only as of now
string postfixToPrefix(string postfix)
{
    stack<string> operands;

    for(int i=0; i<postfix.size(); i++)
    {
        if(isdigit(postfix[i])) operands.push(to_string(postfix[i]-'0'));
        else
        {
            string op1 = operands.top();
            operands.pop();
            string op2 = operands.top();
            operands.pop();
            operands.push(postfix[i] + op2 + op1);
        }
    }

    return operands.top();
}

// This function evaluates a prefix expression
// This works for single digit numbers only as of now
int prefixEvaluate(string prefix)
{
    stack<int> operands;

    for(int i=prefix.size()-1; i>=0; i--)
    {
        if(isdigit(prefix[i])) operands.push(prefix[i]-'0');
        else
        {
            int op1 = operands.top();
            operands.pop();
            int op2 = operands.top();
            operands.pop();
            operands.push(applyOp(op1, op2, prefix[i]));
        }
    }

    return operands.top();
}

// This function converst prefix expression to Postfix
// This works for single digit numbers only as of now
string prefixtoPostfix(string prefix)
{
    stack<string> operands;

    for(int i=prefix.size()-1; i>=0; i--)
    {
        if(isdigit(prefix[i])) operands.push(to_string(prefix[i]-'0'));
        else
        {
            string op1 = operands.top();
            operands.pop();
            string op2 = operands.top();
            operands.pop();
            operands.push(op1 + op2 + prefix[i]);
        }
    }

    return operands.top();
}

// This function converst prefix expression to Infix
// This works for single digit numbers only as of now
string prefixtoInfix(string prefix)
{
    stack<string> operands;

    for(int i=prefix.size()-1; i>=0; i--)
    {
        if(isdigit(prefix[i])) operands.push(to_string(prefix[i]-'0'));
        else
        {
            string op1 = operands.top();
            operands.pop();
            string op2 = operands.top();
            operands.pop();
            operands.push("(" + op1 + prefix[i] + op2 + ")");
        }
    }

    return operands.top();
}

int main()
{
    string alphaexpression = "(val1-val2/C)*(A/K-L)";
    string numexpression = " 3+5 / 2 +2*2";

    cout<<endl<<"Infix Expression : "<<numexpression<<endl;
    cout<<"Infix Evaluate : "<<infixEvaluate(numexpression)<<endl;
    cout<<"Infix to Prefix : "<<infixToPrefix(numexpression)<<endl;
    cout<<"Infix to Postfix : "<<infixToPostfix(numexpression)<<endl<<endl;

    cout<<"Postfix Expression : "<<infixToPostfix(numexpression)<<endl;
    cout<<"Postfix Evaluation : "<<postfixEvaluate(infixToPostfix(numexpression))<<endl;
    cout<<"Postfix to Infix : "<<postfixToInfix(infixToPostfix(numexpression))<<endl;
    cout<<"Postfix to Prefix : "<<postfixToPrefix(infixToPostfix(numexpression))<<endl<<endl;
    
    cout<<"Prefix Expression : "<<infixToPrefix(numexpression)<<endl;
    cout<<"Prefix Evaluate : "<<prefixEvaluate(infixToPrefix(numexpression))<<endl;
    cout<<"Prefix to Postfix : "<<prefixtoPostfix(infixToPrefix(numexpression))<<endl;
    cout<<"Prefix to Infix : "<<prefixtoInfix(infixToPrefix(numexpression))<<endl<<endl;
    
    return 0;
}