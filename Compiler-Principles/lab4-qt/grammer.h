#ifndef GRAMMER_H
#define GRAMMER_H

#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>


using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;

const string EMPTY = "@";

struct LR0StateItem {
  /* data */
  char left;
  string right;
  size_t pos;

  string toStr();
  bool operator<(const LR0StateItem &rhs) const;
};

struct LR0State {
  /* data */
  set<LR0StateItem> items;

  string toStr();
};

class Grammer {
  //  private:
 public:
  /* data */
  map<char, set<string>> productions;
  set<char> nonterminals;
  set<char> terminals;

  map<char, set<char>> firstSet;
  map<char, set<char>> followSet;
  set<char> nullableSet;

  void buildNullableSet();
  void buildFirstSet();
  void buildFollowSet();

  void lr0Closure(LR0State&);
  LR0State lr0Goto(LR0State, char);

 public:
  // Grammer(/* args */);
  // ~Grammer();
};

#endif // GRAMMER_H
