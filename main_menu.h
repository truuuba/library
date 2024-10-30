#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <QDialog>
#include "new_doc.h"
#include "bd_connect.h"

namespace Ui {
class main_menu;
}

class main_menu : public QDialog
{
    Q_OBJECT

public:
    explicit main_menu(QWidget *parent = nullptr);
    ~main_menu();
    QVector<document> elements;

private slots:
    void on_add_doc_clicked();
    void on_view_all_doc_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_find_doc_clicked();

private:
    Ui::main_menu *ui;
    new_doc *window_new;
};

#endif // MAIN_MENU_H
