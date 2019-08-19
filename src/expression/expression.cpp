#include "expression.h"
#include "lex.yy.h"
#include <iostream>
#include <cmath>
using namespace std;

double __xval;
double __yval;
double __value;

double avg(double x, double y)
{
  return ((x + y)/2);
}

double pcos(double x)
{
  return (cos(acos(-1)*x));
}

double psin(double x)
{
  return (sin(acos(-1)*x));
}

double mult (double x, double y)
{
  return (x * y);
}


Expression::Expression(string expressionString)
{
  Setup();
  node = 0;
  Inityylex();
  yy_scan_string(expressionString.c_str());
  
  syntaxOk = true;
  int scanningOk = false;
  while (1)
    {
      int result = yylex();
      scanningOk = (result != -1);
      if (result < 1)
	break;
    }
  
  if (! scanningOk)
    syntaxOk = false;
  else
    {
      Inityylex();
      yy_scan_string(expressionString.c_str());
      if (yyparse() != 0)
	syntaxOk = false;
      else
	node = __parseTree;
    }
}

bool Expression::SyntaxIsValid()
{
  return (syntaxOk);
}

double Expression::Evaluate(double x, double y)
{
  if (!syntaxOk)
    {
      cout << "Attempt to call Evaluate on invalid expression" << endl;
      exit(-1);
    }
  __xval = x;
  __yval = y;
  return (node->Evaluate());
}

void Expression::Show()
{
  node->Show();
}

Expression::~Expression()
{
  if (node)
    delete node;
}

void Expression::Setup()
{
  if (setupDone == false)
    {
      setupDone = true;
      ASTNode::RegisterFunction ("avg", avg);
      ASTNode::RegisterFunction ("mult", mult);
      ASTNode::RegisterFunction ("psin", psin);
      ASTNode::RegisterFunction ("pcos", pcos);
    }
}

Expression::Expression(const Expression& other)
{
    this->syntaxOk = other.syntaxOk;
    this->node = other.node->copy();
}



bool Expression::setupDone = false;
