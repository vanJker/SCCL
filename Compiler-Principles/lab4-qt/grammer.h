#ifndef GRAMMER_H
#define GRAMMER_H

#include <cctype>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>


using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::set;
using std::string;

const string EMPTY = "@";
const char EOF_ = '$';

struct LR0StateItem {
  /* data */
  char left;
  string right;
  size_t pos;

  string toStr();
  bool operator<(const LR0StateItem &rhs) const;
  bool operator==(const LR0StateItem &rhs) const;
};

struct LR0State {
  /* data */
  size_t id;
  set<LR0StateItem> items;

  string toStr();
  bool operator<(const LR0State &rhs) const;
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

  char startSymbol;
  size_t stateIdCount;
  map<size_t, LR0State> lr0StateTable;
  set<LR0State> lr0StateSet;
  map<size_t, map<char, size_t>> actionTable;
  map<size_t, map<char, size_t>> gotoTable;

  void buildNullableSet();
  void buildFirstSet();
  void buildFollowSet();

  void lr0Closure(LR0State&);
  LR0State lr0Goto(LR0State, char);
  bool processLR0State(LR0State &);
  void lr0Analysis();

 public:
  // Grammer(/* args */);
  // ~Grammer();
};

#endif // GRAMMER_H
