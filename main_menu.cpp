#include "main_menu.h"
#include "ui_main_menu.h"
#include <QUrl>
#include <QDesktopServices>
#include "bd_connect.h"

main_menu::main_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_menu)
{
    ui->setupUi(this);
    ui->add_doc->setStyleSheet("background-color: rgb(255, 103, 0)");
    ui->find_doc->setStyleSheet("background-color: rgb(255, 103, 0)");
    ui->view_all_doc->setStyleSheet("background-color: rgb(255, 103, 0)");
}

main_menu::~main_menu()
{
    delete ui;
}

void main_menu::on_add_doc_clicked()
{
    window_new = new new_doc(this);
    window_new->show();
}


void main_menu::on_view_all_doc_clicked()
{
    elements.clear();
    ui->tableWidget->clear();
    bdWork bd;
    bd.Connected_db();
    elements = bd.Take_doc();
    ui->tableWidget->setRowCount(elements.size());
    ui->tableWidget->setColumnCount(2);
    for (int i = 0; i < elements.size(); i++){
        QTableWidgetItem *nazv = new QTableWidgetItem(elements[i].nazv);
        QTableWidgetItem *artic = new QTableWidgetItem(elements[i].artic);
        ui->tableWidget->setItem(i, 0, nazv);
        ui->tableWidget->setItem(i, 1, artic);
    }
}

void main_menu::on_tableWidget_cellClicked(int row, int column)
{
   QString w = elements[row].way;
   QDesktopServices::openUrl(QUrl::fromLocalFile(w));
}

void main_menu::on_find_doc_clicked()
{
    elements.clear();
    ui->tableWidget->clear();
    bdWork bd;
    bd.Connected_db();
    bool prov = 0;
    QString param = ui->parametr->text();
    elements = bd.Take_doc();
    QVector<document> result_found;
    for(int i = 0; i < elements.size(); i++){
        if ((param == elements[i].artic) or (param == elements[i].nazv) or (param == elements[i].t1) or (param == elements[i].t2) or (param == elements[i].tp)){
            result_found.push_back(elements[i]);
            prov = 1;
        }
    }
    if(prov){
        ui->tableWidget->setRowCount(result_found.size());
        ui->tableWidget->setColumnCount(2);
        for (int i = 0; i < result_found.size(); i++){
            QTableWidgetItem *nazv = new QTableWidgetItem(result_found[i].nazv);
            QTableWidgetItem *artic = new QTableWidgetItem(result_found[i].artic);
            ui->tableWidget->setItem(i, 0, nazv);
            ui->tableWidget->setItem(i, 1, artic);
        }
        elements = result_found;
    }
    else
        QMessageBox::warning(0, "Ошибка", "Файлов по параметру не найдено");
}

