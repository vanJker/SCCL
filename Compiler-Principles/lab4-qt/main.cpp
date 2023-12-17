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

    std::cout.flush();

    return 0;
}
