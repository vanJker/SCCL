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

    std::cout.flush();

    return 0;
}
