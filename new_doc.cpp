#include "new_doc.h"
#include "ui_new_doc.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QComboBox>
#include "bd_connect.h"

new_doc::new_doc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_doc)
{
    ui->setupUi(this);
    on_Type_file_activated(ui->Type_file->currentIndex());
    ui->add_doc->setStyleSheet("background-color: rgb(255, 103, 0)");
}

new_doc::~new_doc()
{
    delete ui;
}

void new_doc::on_add_doc_clicked()
{
    bdWork bd;
    bd.Connected_db();
    bool prov = 1;
    QString art = ui->articul->text();
    QString name_ = ui->name_doc->text();
    QString way = ui->way_doc->text();
    QString teg1 = ui->teg1->text();
    QString teg2 = ui->teg2->text();
    QString teg3 = ui->teg3->text();
    QRegularExpression reg_art("^[A-Z0-9]{12}$"), reg_nazv("^[a-zA-Zа-яА-Я_]{1,30}$"), reg_teg("^[a-zA-Zа-яА-Я_]{0,45}$");
    QRegularExpressionMatch matchArt = reg_art.match(art);
    if (!matchArt.hasMatch()){
        prov = 0;
        QMessageBox::warning(0, "Ошибка!", "Введены неверные данные для артикула! Введите 12 символов - только заглавные буквы латинского алфавита и цифры");
    }
    QRegularExpressionMatch matchNazv = reg_nazv.match(name_);
    if (!matchNazv.hasMatch()){
        prov = 0;
        QMessageBox::warning(0, "Ошибка!", "Введены неверные данные для названия! Введите до 30 символов - только буквы и цифры");
    }
    QRegularExpressionMatch mT1 = reg_teg.match(teg1), mT2 = reg_teg.match(teg2), mT3 = reg_teg.match(teg3);
    if((!mT1.hasMatch()) or (!mT2.hasMatch()) or (!mT3.hasMatch())){
        prov = 0;
        QMessageBox::warning(0, "Ошибка!", "Введены неверные данные для тегов! Введите всего одно слово на русском или английском языке");
    }
    if (prov)
        bd.Add_doc(art, name_, type_d, way, teg1, teg2, teg3);
}


void new_doc::on_Type_file_activated(int ind)
{
    if (ind == 0)
        type_d = "Документ";
    else if (ind == 1)
        type_d = "Книга";
    else
        type_d = "Справочные материалы";
}

