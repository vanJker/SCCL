#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_save_clicked();

    void on_scan_clicked();

    void on_parse_clicked();


private:
    Ui::MainWindow *ui;

    std::string temp_file();
};
#endif // MAINWINDOW_H
