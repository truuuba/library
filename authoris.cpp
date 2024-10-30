#include "authoris.h"
#include "ui_authoris.h"
#include <QRegularExpression>
#include <QMessageBox>
#include "bd_connect.h"
#include <QPushButton>

authoris::authoris(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authoris)
{
    ui->setupUi(this);
    ui->reg->setStyleSheet("background-color: rgb(255, 103, 0)");
}

authoris::~authoris()
{
    delete ui;
}

void authoris::on_reg_clicked()
{
    bdWork bd;
    bd.Connected_db();
    bool prov = 1;
    QString login = ui->log->text();
    QString password = ui->pas->text();
    QString mail = ui->email->text();
    QRegularExpression reg_l("^[a-zA-Z0-9_]{1,20}$"), reg_p("^[a-zA-Z0-9!@#$%^&*()_+]{1,20}$"), reg_m("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+.[a-zA-Z0-9-.]+$");
    QRegularExpressionMatch matchlog = reg_l.match(login);
    if (!matchlog.hasMatch()){
        prov = 0;
        QMessageBox::warning(0, "Ошибка!", "Введены неверные данные для логина");
    }
    QRegularExpressionMatch matchpass = reg_p.match(password);
    if (!matchpass.hasMatch()){
        prov = 0;
        QMessageBox::warning(0, "Ошибка!", "Введены неверные данные для пароля");
    }
    QRegularExpressionMatch matchmail = reg_m.match(mail);
    if (!matchmail.hasMatch()){
        prov = 0;
        QMessageBox::warning(0, "Ошибка!", "Введены неверные данные для электронной почты");
    }
    if (prov){
        bd.Add_user(login, password, mail);
        hide();
    }
}

