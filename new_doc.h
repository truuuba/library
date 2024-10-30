#ifndef NEW_DOC_H
#define NEW_DOC_H
#include <QDialog>

namespace Ui {
class new_doc;
}

class new_doc : public QDialog
{
    Q_OBJECT

public:
    explicit new_doc(QWidget *parent = nullptr);
    ~new_doc();

private slots:
    void on_add_doc_clicked();
    void on_Type_file_activated(int index);

private:
    Ui::new_doc *ui;
    QString type_d;
};

#endif // NEW_DOC_H
