#include "ExpressionManager.h"
#include <sstream>
#include <cctype>


// The set of opening parentheses.
const string OPEN = "([{";
// The corresponding set of closing parentheses.
const string CLOSE = ")]}";
bool is_open(char ch) {
  return OPEN.find(ch) != string::npos;
}
bool is_close(char ch) {
  return CLOSE.find(ch) != string::npos;
}

bool ExpressionManager::isBalanced(string expression){
	cout << "isBalanced: " << expression << endl;

	stack<char> s; //Create an empty stack of characters.
    bool balanced = true; //Assume that the expression is balanced (balanced is true).
    for (string::const_iterator iter = expression.begin(); //Set index to 0.
     balanced && (iter != expression.end()); //while balanced is true and index < the expression’s length
     iter++) {
        char next_ch = *iter; //Get the next character in the data string.
        if (is_open(next_ch)) { //if the next character is an opening parenthesis
            s.push(next_ch); //Push it onto the stack.
        } else if (is_close(next_ch)) { //else if the next character is a closing parenthesis
            if (s.empty()) { //if stack is empty
                balanced = false; //set balanced to false
            } else {
                char top_ch = s.top();
                s.pop(); //pop the top of the stack
                balanced = //set balanced to false
                 OPEN.find(top_ch) == CLOSE.find(next_ch); //if the top is not an open parenthesis that matches the closing parenthesis
            }
        }
    }
    return balanced && s.empty();
}

const std::string ExpressionManager::OPERATORS = "+-*/%";
/** Evaluates the current operator.
    This function pops the two operands off the operand
    stack and applies the operator.
    @param op A character representing the operator
    @throws Syntax_Error if top is attempted on an empty stack
*/
int ExpressionManager::eval_op(char op) {
	if (operand_stack.empty()) 
    	throw 1;
	int rhs = operand_stack.top();
	operand_stack.pop();
	if (operand_stack.empty())
    	throw 2;
	int lhs = operand_stack.top();
	operand_stack.pop();
	int result = 0;
	  switch(op) {
	  case '+' : result = lhs + rhs;
	             break;
	  case '-' : result = lhs - rhs;
	             break;
	  case '*' : result = lhs * rhs;
	             break;
	  case '/' : result = lhs / rhs;
	             break;
	  case '%' : result = lhs % rhs;
	             break;
	  }
return result;
}


string ExpressionManager::postfixEvaluate(string postfixExpression){
	cout << "postfixEvaluate: " << postfixExpression << endl;
	//Create an empty operand stack **done in h file
	// Be sure the stack is empty
	while (!operand_stack.empty())
		operand_stack.pop();
	
	  // Process each token
	istringstream tokens(postfixExpression); //Split the postfix expression into a vector<string> of tokens
	char next_char;//For this lab, there will be a space (' ') character between each token
	while (tokens >> next_char) { //For each token in the list of tokens get the next token
		if (isdigit(next_char)) { //if the first character of the token is a digit
	    	tokens.putback(next_char);
	    	int value;
	    	tokens >> value;//convert the token into an int 
	    	operand_stack.push(value); //push the token int on the operand stack
	    } else if (is_operator(next_char)) { //else if the token is an operator
	    	int result = eval_op(next_char); //pop the right operand off the stack  pop the left operand off the stack evaluate the operation ***done in eval_op
	    	operand_stack.push(result); //push the result onto the stack
	    } else { //else indicate an error 
	    	try {
        		int result = eval_op(next_char);
    		}
    		catch(int which) {
        	return "invalid";
	    	}
	     
	  }
	if (!operand_stack.empty()) { //pop the stack, convert it to a string, and return the result
		int answer = operand_stack.top();
	    operand_stack.pop(); 
	    if (operand_stack.empty()) {
	      return to_string(answer);
	    } else {
	    	try {
        		int result = eval_op(next_char);
    		}
    		catch(int which) {
        	return "invalid";
	    	}
	    }
	  } else {
	    	try {
        		int result = eval_op(next_char);
    		}
    		catch(int which) {
        	return "invalid";
	    	}
		}
	  
	}
}

vector<string> ExpressionManager::parseTokens(string postfixExpression)
{
  stringstream ss(postfixExpression);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}



string ExpressionManager::postfixToInfix(string postfixExpression){
	cout << "postfixToInfix: " << postfixExpression << endl;
	std::stack<string> expression_stack;//Create an empty expression stack
	while (!expression_stack.empty())
		expression_stack.pop();
	istringstream tokens(postfixExpression); //Split the postfixExpression into tokens
	char next_char;
	while (tokens >> next_char) { //Foreach token in postfix expression//Get the next token
		if (isdigit(next_char)) { //If the token is a digit (operand)
			tokens.putback(next_char);
	    	int value;
	    	tokens >> value;//convert the token into an int 
	    	expression_stack.push(to_string(value)); //push token onto stack
	    } else if (is_operator(next_char)) { //else if the token is an operator
	    	string rhs = expression_stack.top(); //Pop the right expression off the stack
			expression_stack.pop();
			string lhs = expression_stack.top(); //Pop the left expression off the stack
			expression_stack.pop();
			expression_stack.push("( " + lhs + " " + next_char + " " + rhs + " )"); //Form a string with the expressions and the operator token. Put spaces between everything. Put parentheses around the string. //Example:
	    }
	}
	if(expression_stack.size() == 1) { //If there is only one value in the stack
		return expression_stack.top();//That value in the stack is the desired infix string. Return the top of the expression stack.
	} else {
		return "error";
	}
}



bool process_operator(stack<string> &opStack, string &postfix, string &op){
	if (opStack.empty() || opStack.top() == "(" || op == "(") {
		cout << op << endl;
 		opStack.push(op);
 		return 1;
	}
	else if(op == ")") {
		while(opStack.top() != "(") {
			postfix.append(opStack.top() + " ");
			opStack.pop();
			if(!opStack.empty() || opStack.top() == "(" || opStack.top() == ")") {
			return 0;
			}
		}
		opStack.pop();
		return 1;
	}
	else {
		while( op <= opStack.top()){
			postfix.append(opStack.top() + " ");
			opStack.pop();
		}
		opStack.push(op);
		return 1;
	}
	
}

string ExpressionManager::infixToPostfix(string infixExpression) {
	cout << "infixToPostfix: " << infixExpression << endl;
	std::stack<string> op_stack;
	string postfix = ""; //Initialize postfix to an empty string
	istringstream tokens(infixExpression);//Split the postfix expression into a vector<string> of tokens
	char next_char;
	while (tokens >> next_char) { //Foreach token in postfix expression//Get the next token
			cout << "1st while line 195" << endl;
		if (isdigit(next_char)) { //if the next token is an operand (if it is a digit)
			cout << "ifisdigit 197" << next_char << endl;
			tokens.putback(next_char);
	    	string value;
	    	tokens >> value;//convert the token into an int
	    		cout << "token to int " << value << endl;
	    	postfix.append(value + " "); //append with a space after
	    
	    } else if (is_operator(next_char)) { 
	    		cout << "elseif isop line 204" << next_char << endl;
	    	tokens.putback(next_char);
	    	string value;
	    	tokens >> value;//else if the next token is an operator
	    	if(process_operator(op_stack, postfix, value) == false) {//Call process_operator() to process the operator//Use pass by reference so that process_operator can modify the opStack and the postfix string
	    		cout << "if process_operator line 209" << value << endl;
	    		return "invalid";//If process_operator returns false, then indicate a syntax error
	    	}
	    } else { //else Indicate a syntax error
	    	cout << "line 213" << endl;
	    	return "invalid";
	    }
	}
	while(!op_stack.empty()) {
		cout << "in while 218" << endl;
	postfix.append(op_stack.top() + " "); //Pop remaining operators off the operator stack and append them to postfix (with a space following each except for the last)
	op_stack.pop();
	}
	if(postfixEvaluate(postfix) != "invalid") { //To test if the resulting postfix is valid, you can call your postfixEvaluate function to see if you get a valid result
		cout << "line 223" << endl;
		return postfix;	//If the result is valid, return postfix
	} else {
		cout << "line 226" << endl;
		return "invalid";//Else, indicate a syntax error
	}
}