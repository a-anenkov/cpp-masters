//-----------------------------------------------------------------------------
//
// Source code for MIPT masters course on C++
// Slides: https://sourceforge.net/projects/cpp-lects-rus
// Licensed after GNU GPL v3
//
//------------------------------------------------------------------------------
//
// Node.hpp -- concrete node types
//
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

#include "INode.hpp"

namespace Node {

// Integer value
class Value final : public INode {
  int Val_;

  // INode interface
public:
  int calc() override { return Val_; }
  void dump() const override {
    std::cout << "Node Value: " << Val_ << std::endl;
  }

public:
  Value(int V) : Val_(V) {}
};

// Declaration
class Decl final : public INode {
  int Val_;
  std::string Varname_;

  // INode interface
public:
  Decl(const std::string &Name) : Varname_(Name) {}
  int calc() override { return Val_; }
  void dump() const override {
    std::cout << "Node Decl: " << Val_ << std::endl;
  }

public:
  Decl() = default;
  void SetValue(int Val) { Val_ = Val; }
};

// Scope
class Scope final : public IScope {
  std::vector<INode *> Branches_;
  IScope *PrevScope_;

  // INode interface
public:
  int calc() override {
    for (auto *B : Branches_)
      B->calc();
    return 0;
  }

  void dump() const override {
    std::cout << "Node Scope: " << std::endl;
    for (const auto *X : Branches_)
      X->dump();
  }

  // IScope interface
public:
  IScope *push() override { return new Scope(this); }
  IScope *resetScope() const override { return PrevScope_; }
  void addBranch(INode *Branch) override { Branches_.push_back(Branch); }
  INode *access(const std::string &VarName) override;
  INode *visible(const std::string &VarName) const override;

public:
  Scope(Scope *PrevScope) : PrevScope_(PrevScope) {}
  ~Scope();
};

// Operand
class Operand final : public INode {
  INode *Left_;
  INode *Right_;
  Operation Op_;

  // INode interface
public:
  int calc() override;
  void dump() const override;

public:
  Operand(INode *Left, Operation Op, INode *Right)
      : Left_(Left), Right_(Right), Op_(Op) {}
  ~Operand();
};

// While loop node
class While final : public INode {
  INode *Op_ = nullptr;
  INode *Scope_ = nullptr;

  // INode interface
public:
  int calc() override {
    while (Op_->calc())
      Scope_->calc();
    return 0;
  }
  void dump() const override {
    std::cout << "Node While " << std::endl;
    Scope_->dump();
  }

public:
  While(INode *Op, INode *Scope) : Op_(Op), Scope_(Scope) {}
  ~While() {
    // we can not delete decl here
    if (Op_ && typeid(Decl) != typeid(*Op_))
      delete Op_;
    delete Scope_;
  }
};

// If node
class If final : public INode {
  INode *Op_;
  INode *Scope_;

  // INode interface
public:
  int calc() override {
    if (Op_->calc())
      Scope_->calc();
    return 0;
  }
  void dump() const override {
    std::cout << "Node If " << std::endl;
    Scope_->dump();
  }

public:
  If(INode *Op, INode *Scope) : Op_(Op), Scope_(Scope) {}
  ~If() {
    if (Op_ && typeid(Decl) != typeid(*Op_))
      delete Op_;
    delete Scope_;
  }
};

} // namespace Node