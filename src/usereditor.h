#ifndef USEREDITOR_H
#define USEREDITOR_H

#include <QDialog>
#include "user.h"

namespace Ui {
class UserEditor;
}

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class UserEditor : public QDialog
{
    Q_OBJECT

public:
    explicit UserEditor(QWidget *parent = 0);
    ~UserEditor();

public slots:
    void add();
    void modify(const User &);

private slots:
    void loadUserParameters(const User &user);
    User* getUser(void);
    void on_tbBack_clicked();
    void on_tbNext_clicked();
    void on_tbCancel_clicked();
    void on_tbFinish_clicked();

private:
    Ui::UserEditor *ui;

signals:
    void signalEditUser(User*);
};

#endif // USEREDITOR_H
