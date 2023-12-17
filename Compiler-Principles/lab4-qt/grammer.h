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

 public:
  // Grammer(/* args */);
  // ~Grammer();
};

#endif // GRAMMER_H
