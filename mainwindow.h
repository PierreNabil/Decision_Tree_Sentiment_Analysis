#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include "decisiontree.h"
#include "testentrywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static DecisionTree Tree;

private slots:
    void on_Train_File_Btn_clicked();

    void on_Test_Single_Btn_clicked();

    void on_Test_File_Btn_clicked();

private:
    Ui::MainWindow *ui;
    TestEntryWindow* TEWindow;
};
#endif // MAINWINDOW_H
