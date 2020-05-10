#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Test_Single_Btn->setEnabled(false);
    ui->Test_File_Btn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

DecisionTree MainWindow::Tree;

//Done
void MainWindow::on_Train_File_Btn_clicked()
{
    QString TrainingFileName = QFileDialog::getOpenFileName(this, "Choose the Training Data:", "C:/Users/owner/Desktop");
    std::ifstream file(TrainingFileName.toStdString());
    if(file.fail())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please Select a valid file !");
        messageBox.setFixedSize(500,200);

        return;
    }

    ui->Show_Label->setText("Training...");
    QCoreApplication::processEvents();


    Tree.train(file);
    float TrainingError = Tree.Error();

    file.close();
    ui->Test_Single_Btn->setEnabled(true);
    ui->Test_File_Btn->setEnabled(true);
    ui->Show_Label->setText("Done training! \nTraining Accuracy = " + QString::fromStdString(std::to_string(100 - TrainingError*100)) + "%");
}

//Needs Debugging
void MainWindow::on_Test_Single_Btn_clicked()
{
    const std::vector<QString>& CompNames = Tree.getCompNames();
    std::vector<bool> CompValues;

    TEWindow = new TestEntryWindow(CompNames, CompValues);
    TEWindow->setModal(true);
    TEWindow->exec();
    delete TEWindow;

    bool Ans = Tree.traverse(CompValues);

    QMessageBox messageBox;
    messageBox.setFixedSize(500,200);

    if(Ans)
        messageBox.information(0,"Answer","Positive");
    else
        messageBox.information(0,"Answer","Negative");

    ui->Show_Label->setText("Done! \nChoose another test type...");
}

//Done
void MainWindow::on_Test_File_Btn_clicked()
{
    QString TestFileName = QFileDialog::getOpenFileName(this, "Choose the Test Data:", "C:/Users/owner/Desktop");
    std::ifstream Tfile(TestFileName.toStdString());
    if(Tfile.fail())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please Select a valid file !");
        messageBox.setFixedSize(500,200);

        return;
    }
    QString ResultFileName = QFileDialog::getOpenFileName(this, "Choose the Output File:", "C:/Users/owner/Desktop");
    std::ofstream Rfile(ResultFileName.toStdString());
    if(Rfile.fail())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please Select a valid file !");
        messageBox.setFixedSize(500,200);

        return;
    }

    std::string DataLine;
    bool Ans;

    getline(Tfile, DataLine);

    while(!Tfile.eof())
    {
        getline(Tfile, DataLine);
        Ans = Tree.traverse(QString::fromStdString(DataLine));

        if(Ans)
            Rfile << "Positive" << std::endl;
        else
            Rfile << "Negative" << std::endl;
    }

    Tfile.close();
    Rfile.close();
    ui->Show_Label->setText("Done! \nChoose another test type...");
}
