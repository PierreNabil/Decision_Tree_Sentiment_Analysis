#include "testentrywindow.h"
#include "ui_testentrywindow.h"

TestEntryWindow::TestEntryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestEntryWindow),
    compValues(nullptr)
{
    ui->setupUi(this);
}

TestEntryWindow::TestEntryWindow(const std::vector<QString>& CompNames, std::vector<bool>& CompValues, QWidget *parent) :TestEntryWindow(parent)
{
    compValues = &CompValues;

    ui->DataTable->setColumnCount(CompNames.size());
    ui->DataTable->setHorizontalHeaderLabels(QStringList::fromStdList(vectolist(CompNames)));

    for (unsigned int i=0; i<CompNames.size(); i++)
        ui->DataTable->setItem(0, i, new QTableWidgetItem(QString().setNum(0)));

}

TestEntryWindow::~TestEntryWindow()
{
    for(int i =0; i<ui->DataTable->columnCount(); i++)
        compValues->push_back((bool)ui->DataTable->itemAt(i,0)->text().toInt());

    delete ui;
}

std::list<QString> vectolist(std::vector<QString> Vec)
{
    std::list<QString> List;
    for(size_t i=0; i<Vec.size(); i++)
        List.push_front(Vec[i]);
    return List;
}
