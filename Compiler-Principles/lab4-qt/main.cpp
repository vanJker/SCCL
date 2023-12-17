#include "mainwindow.h"
#include "grammer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();


    cout << "hello" << endl;

    cout << "\n First & Follow \n" << endl;
    Grammer g;
    g.nonterminals = {'X', 'Y', 'Z'};
    g.terminals = {'a', 'c', 'd'};
    g.productions = {{'Z', {"d", "XYZ"}}, {'Y', {"c", EMPTY}}, {'X', {"Y", "a"}}};
    g.buildNullableSet();
    g.buildFirstSet();
    g.buildFollowSet();

    cout << "Nullable Set:" << endl;
    cout << "{ ";
    for (auto N : g.nullableSet) {
      cout << N << ", ";
    }
    cout << " }" << endl;

    cout << "First Set:" << endl;
    for (auto N : g.firstSet) {
      cout << N.first << ": { ";
      for (auto s : N.second) {
        cout << s << ", ";
      }
      cout << " }" << endl;
    }

    cout << "Follow Set:" << endl;
    for (auto N : g.followSet) {
      cout << N.first << ": { ";
      for (auto s : N.second) {
        cout << s << ", ";
      }
      cout << " }" << endl;
    }


    cout << "\n Closure & Goto \n" << endl;
    Grammer g2;
    g2.nonterminals = {'S', 'E', 'T', 'F'};
    g2.terminals = {'n'};
    g2.productions = {
          {'S', {"E"}}, {'E', {"E+T", "T"}}, {'T', {"T*F", "F"}}, {'F', {"n"}}};

    LR0StateItem item = LR0StateItem{.left = 'S', .right = "E", .pos = 0};
    LR0State S0 = {.items = {item}};

    cout << "Before Closure:" << endl;
    cout << S0.toStr() << endl;

    cout << "After Closure:" << endl;
    g2.lr0Closure(S0);
    cout << S0.toStr() << endl;

    char x = 'E';
    cout << "Goto " << x << ":" << endl;
    auto S1 = g2.lr0Goto(S0, x);
    cout << S1.toStr() << endl;

    cout << "\n LR0 \n" << endl;
    Grammer g3;
    g3.nonterminals = {'S', 'T'};
    g3.terminals = {'x', 'y'};
    g3.productions = {{'S', {"xxT"}}, {'T', {"y"}}};

    g3.startSymbol = 'S';
    g3.stateIdCount = 0;
    g3.buildLR0Table();

    for (auto s: g3.lr0StateSet) {
        cout << s.id << ":" << endl;
        cout << s.toStr() << endl;

        cout << "Action:" << endl;
        for (auto act: g3.actionTable[s.id]) {
            cout << "-" << act.first << "->" << act.second << endl;
        }
        cout << endl;

        cout << "Goto:" << endl;
        for (auto act: g3.gotoTable[s.id]) {
            cout << "-" << act.first << "->" << act.second << endl;
        }
        cout << endl;

    }

    cout << "\n SLR1 \n" << endl;
    Grammer g4;
    g4.nonterminals = {'S', 'T'};
    g4.terminals = {'x', 'y'};
    g4.productions = {{'S', {"xxT"}}, {'T', {"y"}}};

    g4.startSymbol = 'S';
    g4.stateIdCount = 0;

    g4.buildSLR1Table();

    cout << "First Set:" << endl;
    for (auto N : g4.firstSet) {
      cout << N.first << ": { ";
      for (auto s : N.second) {
        cout << s << ", ";
      }
      cout << " }" << endl;
    }

    cout << "Follow Set:" << endl;
    for (auto N : g4.followSet) {
      cout << N.first << ": { ";
      for (auto s : N.second) {
        cout << s << ", ";
      }
      cout << " }" << endl;
    }

    for (auto s: g4.lr0StateSet) {
        cout << s.id << ":" << endl;
        cout << s.toStr() << endl;

        cout << "Action:" << endl;
        for (auto act: g4.slr1ActionTable[s.id]) {
            cout << "-" << act.first << "-> " << ACTIONS[act.second] << " ";
            if (act.second == SHIFT) {
                cout << g4.actionTable[s.id][act.first] << endl;
            } else if (act.second == REDUCE) {
                auto p = *(g4.lr0StateTable[s.id].items.begin());
                cout << p.left << "->" << p.right << endl;
            } else {
                cout << endl;
            }
        }
        cout << endl;

        cout << "Goto:" << endl;
        for (auto act: g4.gotoTable[s.id]) {
            cout << "-" << act.first << "->" << act.second << endl;
        }
        cout << endl;

    }

    std::cout.flush();

    return 0;
}
