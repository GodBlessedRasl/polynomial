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
    std::list<node>* polynome_ptr;
    ~Dnode() = default;
};

class Container{
 public:
    std::list<Dnode*> polys_container;
    void insert(QListWidgetItem* item_ptr, std::list<node>);
    void poly_delete(Dnode* now);
    Dnode* GetDnode(QListWidgetItem* target);
    int size() const { return polys_container.size(); }
    ~Container() = default;
private:
    void update_ids();
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
    Container(main_list);
    std::list<node> to_List(QString &s);
    void mb (std::string &s, std::list<node> &ans);
    void Beautify (std::list<node> *ans);
    std::string to_str(std::list<node> *now);
    QListWidgetItem* pre_current_item = NULL;
    QListWidgetItem* current_item = NULL;
    void SetColorsDefault();
   // friend std::ostream &operator<<(std::ostream, DList *main_list );
private slots:
    void on_insert_clicked();
    void on_delete_button_clicked();
    void on_DERIVATIVE_clicked();

    void on_find_the_value_clicked();

    void on_save_clicked();

    void on_SUM_clicked();

    void on_Base_itemPressed(QListWidgetItem *item);

    void on_multiply_clicked();

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
