#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QLayout>
#include <QMainWindow>
#include<QPushButton>
#include<QGridLayout>
#include<QLabel>
#include<QFont>
#include<QVBoxLayout>
#include<QDebug>
#include<QPair>
#include<QVariant>
#include<QString>
#include<QIcon>
#include<QPalette>
#include <time.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <QTimer>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

struct node;

struct Dnode{
    int id;
    QListWidgetItem* item_ptr;
    Dnode *next,*prev;
    std::list<node>* polynome_ptr;
    ~Dnode() = default;
};

class DList{
 public:
    Dnode *Head, *Tail;
    DList():Head(NULL),Tail(NULL){};
    ~DList();
    void insert(QListWidgetItem* item_ptr, std::list<node>);
    int size();
    void poly_delete(Dnode* now);
    Dnode* GetDnode(QListWidgetItem* target);
    //friend std::ostream &operator<<(std::ostream, DList *main_list );
};

struct node : public std::pair<int,int> {
    node(int n, int a_n) : std::pair<int,int>(n, a_n) {}
    node() : std::pair<int,int>() {}
    int GetN() const {return first; }
    int GetA_N() const {return second; }
//    node *next = NULL;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool checker(QString &s);
    DList(main_list);
    std::list<node> to_List(QString &s);
    void mb (std::string &s, std::list<node> &ans);
    void Beautify (std::list<node> *ans);
    std::string to_str(std::list<node> *now);
   // friend std::ostream &operator<<(std::ostream, DList *main_list );
private slots:

    void on_insert_clicked();
    void on_delete_button_clicked();
    void on_DERIVATIVE_clicked();

    void on_find_the_value_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
};
/*
std::ostream &op
std::ostream &operator<<(std::ostream out, DList *main_list){
    for(auto iterator = main_list->Head;iterator!=main_list->Tail;++iterator){
        out << MainWindow::to_str(iterator->polynome_ptr)<<std::endl;
    }
    return out;
}
erator<<(std::ostream out, DList *main_list){
    for(auto iterator = main_list->Head;iterator!=main_list->Tail;++iterator){
        out << MainWindow::to_str(iterator->polynome_ptr)<<std::endl;
    }
    return out;
}
*/
#endif // MAINWINDOW_H
