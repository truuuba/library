#include "login.h"
#include "ui_login.h"
#include "bd_connect.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->authorisation->setStyleSheet("background-color: rgb(255, 103, 0)");
    ui->registration->setStyleSheet("background-color: rgb(255, 103, 0)");
}

login::~login()
{
    delete ui;
}


void login::on_authorisation_clicked()
{
    bdWork bd;
    bd.Connected_db();
    QString log = ui->login_->text();
    QString pas = ui->pass_->text();
    bool prov = bd.Auth_user(log, pas);
    if (prov){
        window_menu = new main_menu(this);
        window_menu->show();
    }
    else
        QMessageBox::warning(0, "Ошибка", "Неправильно введены данные");
}

void login::on_registration_clicked()
{
    window_aut = new authoris(this);
    window_aut->show();
}

