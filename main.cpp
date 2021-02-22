#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

int main (int argc, char* args[]) {
  Scanner lx(args[1]);
  lx.tokenize();
  Parser parse;
  Interpreter interpreter;
  if (parse.initTokenParse(lx.getList()) == false) {
    interpreter.setDatalogProgram(parse.getProgram());
  }
  return 0;
}