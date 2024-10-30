#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include "authoris.h"
#include "main_menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_authorisation_clicked();
    void on_registration_clicked();

private:
    Ui::login *ui;
    authoris *window_aut;
    main_menu *window_menu;
    bool pr = false;
};
#endif // LOGIN_H
