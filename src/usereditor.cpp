#include "usereditor.h"
#include "ui_usereditor.h"
//#include "user.h"

UserEditor::UserEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserEditor)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    setModal(true);
}

UserEditor::~UserEditor()
{
    delete ui;
}

void UserEditor::add()
{
    QString str("Add User");
    setWindowTitle(str);
    ui->lbTitle->setText(str);

    loadUserParameters(User());

    show();
}

void UserEditor::modify(const User &user)
{
    QString str("Modify User");
    setWindowTitle(str);
    ui->lbTitle->setText(str);

    loadUserParameters(user);

    show();
}

void UserEditor::loadUserParameters(const User &user)
{
    ui->lbID->setText(QString::number(user.ID()));
    ui->leFirstName->setText(user.firstName());
    ui->leLastName->setText(user.lastName());
    ui->lbAddDate->setText(user.addDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lbModifyDate->setText(user.modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->leLevel->setText(QVariant::fromValue(user.level()).value<QString>());
}

User* UserEditor::getUser(void)
{
    User *user = new User;
    user->setID(ui->lbID->text().toInt());
    user->setFirstName(ui->leFirstName->text());
    user->setLastName(ui->leLastName->text());
    user->setAddDate(QDateTime::fromString(ui->lbAddDate->text(),"yyyy-MM-dd hh:mm:ss"));
    user->setModifyDate(QDateTime::fromString(ui->lbModifyDate->text(),"yyyy-MM-dd hh:mm:ss"));
    user->setLevel((User::Level)ui->leLevel->text().toInt());
    return user;
}

void UserEditor::on_tbBack_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
}

void UserEditor::on_tbNext_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
}

void UserEditor::on_tbCancel_clicked()
{
    this->close();
}

void UserEditor::on_tbFinish_clicked()
{
    emit signalEditUser(getUser());
    this->close();
}
