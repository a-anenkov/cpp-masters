//-----------------------------------------------------------------------------
//
// Source code for MIPT masters course on C++
// Slides: https://sourceforge.net/projects/cpp-lects-rus
// Licensed after GNU GPL v3
//
//------------------------------------------------------------------------------
//
// parser.hpp -- bison related extern defines and retval struct
//
//------------------------------------------------------------------------------

#pragma once

import node;

import<string>;

#define YYERROR_VERBOSE 1

// function to run after parse
void wholeProgramAction();

struct yyRet {
  std::string name;
  int value;
  int linePos;
  int inLinePos;
  Node::INode *treeNode;
  Node::Operation op;
};

#define YYSTYPE yyRet

#include "compiler.cpp.h"

extern FILE *yyin;

int yylex();
int yyerror(char const *);
void PrintError(char const *s);
void BeginToken(char *, int *);

// line number diagnostics
extern int yylineno;

// for string position diagnostics
static int yyinlinePos;
