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
