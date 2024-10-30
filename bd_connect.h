#ifndef BD_CONNECT_H
#define BD_CONNECT_H
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <QVector>
#include <QDebug>

struct document{
    QString nazv;
    QString artic;
    QString tp;
    QString t1;
    QString t2;
    //QString t3;
    QString way;
};
class bdWork{
public:
    QSqlDatabase db;

    void Connected_db(){
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setDatabaseName("documents_manager");
        db.setUserName("");
        db.setPassword("");
        db.open();
    }

    int CountUser(){
        int n = 0;
        db.open();
        if (db.isOpen()){
            QSqlQuery querySelect(db);
            querySelect.exec("SELECT COUNT(ID) FROM client;");
            querySelect.first();
            n = querySelect.value(0).toInt();
            //qDebug() << n;
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        return n;
    }

    int CountDoc(){
        int n = 0;
        //this->db.open();
        if (db.isOpen()){
            QSqlQuery querySelect(db);
            querySelect.exec("SELECT COUNT(ID) FROM doc;");
            querySelect.first();
            n = querySelect.value(0).toInt();
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        return n;
    }

    bool Get_login(QString l){
        QVector <QString> loginList;
        bool prov = false;
        //this->db.open();
        if (db.isOpen()){
            QSqlQuery querySelect(db);
            querySelect.exec("SELECT login FROM client;");
            while(querySelect.next())
                loginList.push_back(querySelect.value(0).toString());
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        for (int i = 0; i < loginList.size(); i++){
            QString el = loginList[i];
            erase(el, ' ');
            //qDebug() << el;
            if (l == el){
                prov = true;
                break;
            }
        }
        //qDebug() << prov;
        return prov;
    }

    bool Get_email(QString e){
        QVector <QString> emailList;
        bool prov = false;
        //this->db.open();
        if (db.isOpen()){
            QSqlQuery querySelect(db);
            querySelect.exec("SELECT email FROM client;");
            while(querySelect.next())
                emailList.push_back(querySelect.value(0).toString());
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        for (int i = 0; i < emailList.size(); i++){
            QString el = emailList[i];
            erase(el, ' ');
            if (e == el){
                prov = true;
                break;
            }
        }
        return prov;
    }

    bool Get_articul(QString articul){
        QVector<QString> artList;
        bool prov = false;
        //this->db.open();
        if(db.isOpen()){
            QSqlQuery querySelect(db);
            querySelect.exec("SELECT articul FROM doc;");
            while(querySelect.next())
                artList.push_back(querySelect.value(0).toString());
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        for (int i = 0; i < artList.size(); i++){
            QString el = artList[i];
            erase(el, ' ');
            if (articul == el){
                prov = true;
                break;
            }
        }
        return prov;
    }

    void Add_user(QString log, QString pass, QString email){
        int cnt = CountUser() + 1;
        bool prov = Get_login(log), prov2 = Get_email(email);
        if (prov)
            QMessageBox::warning(0, "Ошибка", "Логин уже занят");
        else if(prov2)
            QMessageBox::warning(0, "Ошибка", "Почта уже занята");
        else {
            if (db.isOpen()){
                QSqlQuery query(db);
                query.prepare("INSERT INTO client(ID, pass, login, email) "
                                "VALUES (:id, :pas, :log, :email)");
                query.bindValue(":id", cnt);
                query.bindValue(":pas", pass);
                query.bindValue(":log", log);
                query.bindValue(":email", email);
                query.exec();
                QMessageBox::information(0, "Успешно!", "Вы зарегестрировались в системе");
            }
            else
                QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        }
    }

    bool Auth_user(QString l, QString p){
        QVector <QString> logList;
        QVector <QString> passList;
        bool prov = false;
        if (db.isOpen()){
            QSqlQuery queryLog(db);
            queryLog.exec("SELECT login FROM client;");
            while(queryLog.next()){
                QString el = queryLog.value(0).toString();
                erase(el, ' ');
                logList.push_back(el);
            }
            QSqlQuery queryPass(db);
            queryPass.exec("SELECT pass FROM client;");
            while(queryPass.next()){
                QString el = queryPass.value(0).toString();
                erase(el, ' ');
                passList.push_back(el);
            }
            for(int i = 0; i < logList.size(); i++){
               if ((logList[i] == l) and (passList[i] == p))
                    prov = true;
            }
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        return prov;
    }

    void Add_doc(QString art, QString nazv, QString type_, QString way, QString teg1, QString teg2, QString teg3){
        int cnt = CountDoc() + 1;
        bool prov = Get_articul(art);
        if (prov)
            QMessageBox::warning(0, "Ошибка", "Артикул уже занят");
        else{
            if(db.isOpen()){
                QSqlQuery query(db);
                query.prepare("INSERT INTO doc(ID, articul, title, type_, teg1, teg2, teg3, way) "
                            "VALUES (:id, :art, :tit, :tp, :t1, :t2, :t3, way);");
                query.bindValue(":id", cnt);
                qDebug() << cnt;
                query.bindValue(":art", art);
                qDebug() << art;
                query.bindValue(":tit", nazv);
                qDebug() << nazv;
                query.bindValue(":tp", type_);
                qDebug() << type_;
                query.bindValue(":t1", teg1);
                qDebug() << teg1;
                query.bindValue(":t2", teg2);
                qDebug() << teg2;
                query.bindValue(":t3", teg3);
                qDebug() << teg3;
                query.bindValue(":way", way);
                qDebug() << way;
                query.exec();
                qDebug() << query.lastError().text();
                QMessageBox::information(0, "Успешно!", "Вы добавили файл в систему");
                query.prepare("SELECT * FROM doc;");
                qDebug() << query.next();
                    /*while(query.next()){
                                      QString el = query.value(0).toString();
                                      erase(el, ' ');
                                      qDebug() << el;
                                  } */
            }
            else
                QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        }
    }

    QVector<document> Take_doc(){
        QVector<document> docs;
        document per;
        db.open();
        if (db.isOpen()){
            QSqlQuery query(db);
            query.exec("SELECT articul, title, way, type_, teg1, teg2, teg3 FROM doc;");
            while(query.next()){
                per.artic = query.value(0).toString();
                erase(per.artic, ' ');
                per.nazv = query.value(1).toString();
                erase(per.nazv, ' ');
                per.way = query.value(2).toString();
                erase(per.way, ' ');
                per.tp = query.value(3).toString();
                erase(per.tp, ' ');
                per.t1 = query.value(4).toString();
                erase(per.t1, ' ');
                per.t2 = query.value(5).toString();
                erase(per.t2, ' ');
                //per.t3 = query.value(6).toString();
                //erase(per.t3, ' ');

                docs.push_back(per);
            }
        }
        else
            QMessageBox::warning(0, "Ошибка", "База данных недоступна");
        return docs;
    }
};
#endif // BD_CONNECT_H
