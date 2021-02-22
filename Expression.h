#ifndef INC_236_PROJ5_EXPRESSION_H
#define INC_236_PROJ5_EXPRESSION_H
#include "Token.h"
#include "Parameter.h"
#include <vector>

class Expression {
private:
  // Private Variables
  Parameter rightParam;
  Parameter expressionOperator;
  Parameter leftParam;
public:
  // Public Functions
  void setRight(Parameter right) {
    rightParam = right;
  }
  void setOperator(Parameter tOper) {
    expressionOperator = tOper;
  }
  void setLeft(Parameter left) {
    leftParam = left;
  }
  string GetExpression() {
    string expression;
    expression = rightParam.toString() + expressionOperator.toString() + leftParam.toString();
    return expression;
  }
  string toString() {
    cout << "Expression to String" << endl;
    string str = "(" + rightParam.toString() + expressionOperator.toString() + leftParam.toString() + ")";
    return str;
  }
};


#endif //INC_236_PROJ5_EXPRESSION_H
