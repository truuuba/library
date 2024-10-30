#ifndef AUTHORIS_H
#define AUTHORIS_H
#include <QDialog>

namespace Ui {
class authoris;
}

class authoris : public QDialog
{
    Q_OBJECT

public:
    explicit authoris(QWidget *parent = nullptr);
    ~authoris();

private slots:
    void on_reg_clicked();

private:
    Ui::authoris *ui;
};

#endif // AUTHORIS_H
