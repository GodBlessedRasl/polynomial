#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QVector>
#include <QString>
#include <QCharRef>
#include <assert.h>
#include <QMessageBox>
#include <math.h>
#include <fstream>
#include <QDebug>
using std::logic_error;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::checker(QString &str){
    bool b = 1;
    int wr = 0;
    std ::vector<std ::string> anses = {"Ошибка: веден некорректный символ: ",//0
                                       "Ошибка : введен некорректный член: ",//1
                                       "Введен корректный многочлен",//2
                                       "Ошибка: строка соддержит пробел",//3
                                       "Ошибка: используется больше одной буквы",//4
                                       "Ошибка: константа не должна начинаться с 0",//5
                                       "Ошибка: степень не должна начинаться с 0"};//6
    int n = str.size();
    char bukva = 'A';
    std::string s = str.toStdString();
    for(int i = 0;i<n;++i){
        char chared = s[i];
        int cur = chared - '0';
        if(!((cur>=0 && cur<=9) || (cur>=49 && cur<=74)
             || s[i]=='+' || s[i]=='-' || s[i]=='^' || s[i]=='\n' || s[i]=='*')){
            if(s[i]==' '){
                wr=i;
                throw logic_error(anses[3]/*+" индекс :"+ std::to_string(wr)*/);
            }
            wr=i;
            throw logic_error(anses[0] + s[i]/*+" индекс :"+ std::to_string(wr)*/);
        }
        if(cur>=49 && cur<=74 && bukva == 'A'){
           bukva = s[i];
        } else if(cur>=49 && cur<=74 && bukva != 'A' && s[i]!=bukva){
            wr=i;
             throw logic_error(anses[4]/*+" индекс :"+ std::to_string(wr)*/);
        }
        if((s[i]=='*' && ((i+1!=n && !(s[i+1]-'0'>=49 && s[i+1]-'0'<=74)) || i == n-1 || i == 0))
                ||(s[i]=='*' && i>0 && !(s[i-1]-'0'>=0 && s[i-1]-'0'<=9))){
            wr=i;
            throw logic_error("error"/*+" индекс :"+ std::to_string(wr)*/);
        }
    }
    std ::string now = "";
    int pos = 0;
    if(s[0]=='+' || (s[0]=='-' && n==1)){
        wr=0;
        throw logic_error("error"/*+" индекс :"+ std::to_string(wr)*/);
    }
    for(int i = 0;i < n; ++i){
        if (s[i]=='*') {
            continue;
        }
        int num = s[i]-'0';
        if(s[i]=='+' || s[i]=='-'){
            if(i>0 && s[i-1]=='^'){
                wr=i;
                throw logic_error("error"/*+" индекс :"+ std::to_string(wr)*/);
            }
            if(pos==0 && now.size()>1 && now[0]=='0'){
                wr=i;
                throw logic_error(anses[5]/*+" индекс :"+ std::to_string(wr)*/);
            }
            if(now.size()>1 && now[0]=='0'){
                wr=i+1-now.size();
                throw logic_error(anses[5]/*+" индекс :"+ std::to_string(wr)*/);
            }
            pos = 0;
            now="";
            if(i>0 && (s[i-1]=='+' || s[i-1]=='-')){
                wr=i;
                throw logic_error("error: 2 знака подряд"/*+" индекс :"+ std::to_string(wr)*/);
            }
        } else{
            if(pos == 0){
                if(num>=0 && num<=9){
                    now+=s[i];
                } else if(num>=49 && num<=74){
                    if(now[0]=='0'){
                        wr=i+1-now.size();
                        throw logic_error(anses[5]/*+" индекс :"+ std::to_string(wr)*/);
                    }
                    pos = 1;
                    now+=s[i];
                } else {
                    wr=i;
                    throw logic_error("error"/*+" индекс :"+ std::to_string(wr)*/);
                }
            } else if(pos == 1){
                if(s[i]=='^'){
                    pos=2;
                    now+=s[i];
                }else {
                    wr=i;
                    throw logic_error("error" /*+" индекс :"+ std::to_string(wr)*/);
                }
            } else if(pos==2){
                if(s[i-1]=='^' && s[i]=='0' && !(i+1==n || (s[i+1]>=0 && s[i+1]<=9))){
                    wr=i;
                    throw logic_error(anses[6]/*+" индекс :"+ std::to_string(wr)*/);
                }
                if(!(num>=0 && num<=9)){
                    wr=i;
                    throw logic_error("error(ошибка в показателе степени члена)"/*+" индекс :"+ std::to_string(wr)*/);
                } else {
                    now+=s[i];
                }
            }
        }
    }
    if(s[n-1]=='^' || s[n-1]=='+'||s[n-1]=='-'){
        wr=n-1;
        throw logic_error("error"/*+" индекс :"+ std::to_string(wr)*/);
    }
    if(pos==0 && now.size()>1 && now[0]=='0'){
        wr=n-now.size();
        throw logic_error("error"/*+" индекс :"+ std::to_string(wr)*/);
    }
    return b;
}
void MainWindow::on_insert_clicked()
{
    const std::string incorrect = "U r trying to insert an incorrect polynomial !!!";
    const std::string empty_line = "U r trying to insert an empty line !!!";
    try {
        QString cur_s = ui->insert_line->text();
        if(cur_s.size() == 0){
            throw std::logic_error(empty_line);
        }
        checker(cur_s);
        std::list<node> now = to_List(cur_s);
        Beautify(&now);


        std::string to_stred = to_str(&now);
//        to_stred += std::to_string()
        cur_s = QString(to_stred.c_str());
        ui->Base->addItem(cur_s);
        auto this_item_ptr = ui->Base->item(ui->Base->count() - 1);
        main_list.insert(this_item_ptr, now);
    } catch(std::logic_error& error) {
        const char* what = static_cast<const char*> (error.what());
        if (error.what() == empty_line) {
            QMessageBox::warning(this, "Insertion", QString(what));
        } else {
            std::string str = incorrect + ": " + error.what();
            QMessageBox::warning(this, "Insertion",
                                 QString(str.c_str()));
        }
    }
    ui->insert_line->setText(QString());
}


void Container::update_ids() {
    int cur_id = 0;
    auto iterator = polys_container.begin();
    for (; iterator != polys_container.end(); ++iterator) {
        (*iterator)->id = cur_id++;
    }
}

void Container::insert(QListWidgetItem *item_ptr, std::list<node> now){
    Dnode *cur = new Dnode;
    cur->polynome_ptr = new std::list<node>(now);
    cur->item_ptr = item_ptr;
    polys_container.push_back(cur);
    update_ids();
}

void Container::poly_delete(Dnode* search){
    Dnode* it;
    auto iterator = polys_container.begin();
    for (; iterator != polys_container.end() &&
         (*iterator) != search; ++iterator) { }
    if (iterator == polys_container.end()) {
        throw std::runtime_error("smth's wrong with deleting polynome");
    }
    polys_container.remove(*(iterator));
    update_ids();
}

Dnode* Container::GetDnode(QListWidgetItem *target) {
    auto iterator = polys_container.begin();
    while ((*iterator)->item_ptr != target) {
        ++iterator;
    }
    return *iterator;
}

void MainWindow::on_delete_button_clicked()
{
    auto current_item_widget_ptr = ui->Base->currentItem();
    auto current_item_dnode_ptr = main_list.GetDnode(current_item_widget_ptr);
    main_list.poly_delete(current_item_dnode_ptr);
    int sz = main_list.size();
    ui->Base->takeItem(ui->Base->row(current_item_widget_ptr));
    int just_for_kicks = sz;
}
void MainWindow::mb(std::string &s, std::list<node>& ans){
    if(s.size()==0){
        return;
    }
    std ::string coeff = "", step = "";
    int pos =0;
    for(int i=0;i<s.size();++i){
        int cur = s[i] - '0';
        if(s[i]=='*'||(cur>=49 && cur<=74)|| s[i]=='^'){
            pos=1;
        }
        if(pos==0){
            if(s[i]!='+'){
                coeff.push_back(s[i]);
            }
        }else{
            if(cur<=9 && cur>=0){
                step+=s[i];
            }
        }
    }
    int n,a_n;
    if(coeff.size()==0){
        a_n=1;
    }else if(coeff.size()==1 && coeff[0]=='-'){
        a_n = -1;
    }else{
        a_n = std::stoi(coeff);
    }
    if(step.size()==0){
        if(pos == 0){
            n = 0;
        }else{
            n=1;
        }
    } else {
        n = std::stoi(step);
    }
    ans.push_back(node(n, a_n));
}

std::list<node> MainWindow::to_List(QString &str){
    std::list<node> ans;
    std::string s = str.toStdString();
    std::string cur = "";
    for (int i = 0; i < s.size(); ++i) {
        if(s[i]=='+' || s[i]=='-'){
            mb(cur, ans);
            if(s[i]=='-'){
                cur="-";
            }else{
                cur="";
            }
        }else{
            cur+=s[i];
        }
    }
    mb(cur, ans);
    return ans;
}

void MainWindow::Beautify(std::list<node> *ans){
    ans->sort();
    node* now = &*(ans->begin());
    for (auto iterator = ans->begin(); iterator != ans->end();
         ) {
        auto* cur = &*iterator;
        auto* next = &*(++iterator);
        while (iterator != ans->end() && next->first == cur->first) {
            cur->second += next->second;
            next->first = -1;
            next = &*(++iterator);
        }
        cur = next;
    }
    ans->sort();
    while((*ans->begin()).first==-1){
        ans->pop_front();
    }
    ans->reverse();
}


std::string MainWindow::to_str(std::list<node> *now) {
    std::string answer;
    std::string token;
    for (auto iterator = now->begin(); iterator != now->end();
        ++iterator, answer += token) {
        token = std::string();
        auto cur = *iterator;
        int a_n = cur.GetA_N();
        int n = cur.GetN();
        if (a_n == 0) {
            continue;
        }
        std::string prefix = "";
        if (a_n > 0 && !answer.empty()) {
            prefix = "+";
        }
        token += prefix;
        if (a_n != 1 && a_n != -1) {
            token += std::to_string(a_n);
        }
        if (n == 0) {
            if (a_n == 1 || a_n == -1) {
                token += std::to_string(a_n);
            }
            continue;
        }
        if (a_n == -1) {
            token += "-";
        }
        token += 'x';
        if (n == 1) {
            continue;
        }
        token += '^' + std::to_string(n);

    }
    return (answer.empty() ? "0" : answer);
}


void MainWindow::SetColorsDefault() {
    if (pre_current_item != NULL) {
        pre_current_item->setBackgroundColor(Qt::white);
        pre_current_item->setForeground(Qt::black);
    }
    if (current_item != NULL) {
        current_item->setBackgroundColor(Qt::white);
        current_item->setForeground(Qt::black);
    }
}

void MainWindow::on_DERIVATIVE_clicked()
{
    SetColorsDefault();
    auto current_item_widget_ptr = ui->Base->currentItem();
    auto current_item_dnode_ptr = main_list.GetDnode(current_item_widget_ptr);
    std::list<node>* poly_tpr = (current_item_dnode_ptr->polynome_ptr);
    std::list<node> proisv_list;
    for(auto iterator = poly_tpr->begin();
        iterator!=poly_tpr->end();++iterator){
        int n = (*iterator).GetN();
        if(n == 0){
            proisv_list.push_back(node(0,0));
        } else{
            proisv_list.push_back(node((*iterator).first - 1,
                                  (*iterator).second * n));
        }
    }
    std ::string ans = to_str(&proisv_list);
    QString res = QString(ans.c_str());
    ui->insert_line->setText(res);
}

void MainWindow::on_find_the_value_clicked()
{
    SetColorsDefault();
    QString str = ui->insert_point->text();
    double point = str.toDouble();
    double ans = 0;
    auto current_item_widget_ptr = ui->Base->currentItem();
    auto current_item_dnode_ptr = main_list.GetDnode(current_item_widget_ptr);
    std::list<node>* poly_ptr = (current_item_dnode_ptr->polynome_ptr);
    for(auto iterator = poly_ptr->begin();
        iterator!=poly_ptr->end();++iterator){
        ans+=(*iterator).GetA_N() * std ::pow(point, (*iterator).GetN());
    }
    std ::string tmp = std::to_string(ans);
    QString res = QString(tmp.c_str());
    ui->insert_point->setText(res);
}



void MainWindow::on_save_clicked()
{
    SetColorsDefault();
    QString tmp  = ui->save_path->text();
    std::string path = tmp.toStdString();
    std::fstream out(path, out.out);
    bool b=0,b1=0;
    if(!out.is_open()){
      b=1;
    }
    for(auto iterator = main_list.polys_container.begin();
        iterator!=main_list.polys_container.end(); ++iterator){
        auto i = *((*iterator)->polynome_ptr);
        out << MainWindow::to_str((*iterator)->polynome_ptr)<<std::endl;
    }

}

void MainWindow::on_SUM_clicked()
{
    SetColorsDefault();
    if (!(current_item != pre_current_item && pre_current_item != NULL)) {
        return;
    }
    auto arg1 = main_list.GetDnode(pre_current_item)->polynome_ptr;
    auto arg2 = main_list.GetDnode(current_item)->polynome_ptr;
    auto* polynome = new std::list<node>();
    auto iterator1 = arg1->begin();
    auto iterator2 = arg2->begin();
    while (iterator1 != arg1->end() && iterator2 != arg2->end()) {
        if ((*iterator1).first > (*iterator2).first) {
            polynome->push_back(node((*iterator1).first, (*iterator1).second));
            ++iterator1;
        } else if ((*iterator1).first < (*iterator2).first) {
            polynome->push_back(node((*iterator2).first, (*iterator2).second));
            ++iterator2;
        } else {
            polynome->push_back(node((*iterator2).first,
                                     (*iterator2).second + (*iterator1).second));
            ++iterator1;SetColorsDefault();
            ++iterator2;
        }
    }
    while (iterator1 != arg1->end()) {
        polynome->push_back(node((*iterator1).first, (*iterator1).second));
                ++iterator1;
    }
    while (iterator2 != arg2->end()) {
        polynome->push_back(node((*iterator2).first, (*iterator2).second));
                ++iterator2;
    }
    QString result = QString(to_str(polynome).c_str());
    ui->insert_line->setText(result);
}

void MainWindow::on_Base_itemPressed(QListWidgetItem *item)
{
    if (pre_current_item != NULL) {
        pre_current_item->setBackgroundColor(Qt::white);
        pre_current_item->setForeground(Qt::black);
    }

    pre_current_item = current_item;
    if (pre_current_item != NULL) {
        pre_current_item->setBackgroundColor(Qt::yellow);
        pre_current_item->setForeground(Qt::red);
    }


    current_item = item;
    current_item->setBackgroundColor(Qt::blue);
    current_item->setForeground(Qt::red);
}

void MainWindow::on_multiply_clicked() {
    SetColorsDefault();
    if(current_item == NULL || pre_current_item == NULL){
        return;
    }
    auto arg1 = main_list.GetDnode(pre_current_item)->polynome_ptr;
    auto arg2 = main_list.GetDnode(current_item)->polynome_ptr;
    auto* polynome = new std::list<node>();
    for(auto iterator1 = arg1->begin();iterator1!=arg1->end();++iterator1){
        for(auto iterator2 = arg2->begin();iterator2!=arg2->end();++iterator2){
            polynome->push_back(node((*iterator1).first + (*iterator2).first,
                                     (*iterator1).second * (*iterator2).second));
        }
    }
    Beautify(polynome);
    QString result = QString(to_str(polynome).c_str());
    ui->insert_line->setText(result);
}
