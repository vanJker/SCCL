#include "mainwindow.h"

#include <QApplication>

#include <iostream>

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE

int lineno;
FILE* source;
FILE* listing;

int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main(int argc, char *argv[])
{
    EchoSource = FALSE;
    TraceScan = FALSE;
    TraceParse = TRUE;
    TraceAnalyze = FALSE;
    TraceCode = FALSE;
    Error = FALSE;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
