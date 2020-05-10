#ifndef TESTENTRYWINDOW_H
#define TESTENTRYWINDOW_H

#include <QDialog>
#include <vector>
#include <list>

QT_BEGIN_NAMESPACE
namespace Ui {
class TestEntryWindow;
}
QT_END_NAMESPACE

class TestEntryWindow : public QDialog
{
    Q_OBJECT

    Ui::TestEntryWindow *ui;
     std::vector<bool>* compValues;

public:
    explicit TestEntryWindow(QWidget *parent = nullptr);
    TestEntryWindow(const std::vector<QString>& CompNames, std::vector<bool>& CompValues, QWidget *parent = nullptr);
    ~TestEntryWindow(); 
};

std::list<QString> vectolist(std::vector<QString> Vec);

#endif // TESTENTRYWINDOW_H
