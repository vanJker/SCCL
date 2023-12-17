#include "grammer.h"

void Grammer::buildNullableSet() {
  this->nullableSet = {};

  bool isChanged = true;
  while (isChanged) {
    isChanged = false;
    auto beforeSize = this->nullableSet.size();

    for (auto p : this->productions) {
      auto X = p.first;

      for (auto Beta : p.second) {
        if (Beta == EMPTY) {
          this->nullableSet.insert(X);
        } else {
          bool temp = true;
          for (auto Y : Beta) {
            if (this->nullableSet.find(Y) == this->nullableSet.end()) {
              temp = false;
              break;
            }
          }
          if (temp == true) {
            this->nullableSet.insert(X);
          }
        }
      }
    }
    if (this->nullableSet.size() != beforeSize) {
      isChanged = true;
    }
  }
}

void Grammer::buildFirstSet() {
  for (auto n : this->nonterminals) {
    this->firstSet[n] = {};
  }

  bool isChanged = true;
  while (isChanged) {
    isChanged = false;

    for (auto p : this->productions) {
      auto N = p.first;
      auto beforeSize = this->firstSet[N].size();

      for (auto p2 : p.second) {
        if (p2 == EMPTY) continue;

        for (auto it = p2.begin(); it != p2.end(); it++) {
          auto Beta = *it;
          if (!isupper(Beta)) {
            // terminal
            auto a = Beta;
            this->firstSet[N].insert(a);
            break;
          } else {
            // nonterminal
            auto M = Beta;
            for (auto s : this->firstSet[M]) {
              this->firstSet[N].insert(s);
            }
            if (this->nullableSet.find(Beta) == this->nullableSet.end()) {
              break;
            }
          }
        }
      }

      if (this->firstSet[N].size() != beforeSize) {
        isChanged = true;
      }
    }
  }
}

void Grammer::buildFollowSet() {
  for (auto N : this->nonterminals) {
    this->followSet[N] = {};
  }

  bool isChanged = true;
  while (isChanged) {
    isChanged = false;

    for (auto p : this->productions) {
      auto N = p.first;

      for (auto p2 : p.second) {
        if (p2 == EMPTY) continue;

        auto temp = this->followSet[N];
        for (auto rit = p2.rbegin(); rit != p2.rend(); rit++) {
          auto Beta = *rit;
          if (!isupper(Beta)) {
            // terminal
            auto a = Beta;
            temp = {a};
          } else {
            // nonterminal
            auto M = Beta;
            auto beforeSize = this->followSet[M].size();

            for (auto s : temp) {
              this->followSet[M].insert(s);
            }
            if (this->nullableSet.find(M) == this->nullableSet.end()) {
              temp = this->firstSet[M];
            } else {
              for (auto s : this->firstSet[M]) {
                temp.insert(s);
              }
            }

            if (this->followSet[M].size() != beforeSize) {
              isChanged = true;
            }
          }
        }
      }
    }
  }
}

void Grammer::lr0Closure(LR0State& C) {
  bool isChanged = true;
  while (isChanged) {
    isChanged = false;
    auto beforeSize = C.items.size();

    for (auto i : C.items) {
      auto B = i.right[i.pos];
      if (!isupper(B)) continue;

      for (auto p : this->productions[B]) {
        C.items.insert(LR0StateItem{.left = B, .right = p, .pos = 0});
      }
    }

    if (C.items.size() != beforeSize) {
      isChanged = true;
    }
  }
}

LR0State Grammer::lr0Goto(LR0State C, char x) {
  LR0State temp = {.items = {}};
  for (auto i : C.items) {
    if (i.right[i.pos] != x) continue;

    temp.items.insert(
        LR0StateItem{.left = i.left, .right = i.right, .pos = i.pos + 1});
  }
  this->lr0Closure(temp);
  return temp;
}

bool LR0StateItem::operator<(const LR0StateItem& rhs) const {
  if (this->left < rhs.left) return true;
  if (this->left > rhs.left) return false;

  if (this->right < rhs.right) return true;
  if (this->right > rhs.right) return false;

  if (this->pos < rhs.pos) return true;
  if (this->pos > rhs.pos) return false;

  return false;
}

string LR0StateItem::toStr() {
  string str = "";
  str += this->left;
  str += " -> ";
  for (auto i = 0; i < this->right.length(); i++) {
    if (i == this->pos) str += ".";
    str += this->right[i];
  }
  if (this->pos == this->right.length()) str += ".";
  return str;
}

string LR0State::toStr() {
  string str = "";
  for (auto item : items) {
    str += item.toStr() + "\n";
  }
  return str;
}

