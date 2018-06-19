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

    // Fill Level combobox with enum values
    // enum value and order is not important since we work with itemData and not cmb index
    ui->cmbLevel->addItem(QVariant::fromValue(User::Viewer).value<QString>(), User::Viewer);
    ui->cmbLevel->addItem(QVariant::fromValue(User::StandardUser).value<QString>(), User::StandardUser);
    ui->cmbLevel->addItem(QVariant::fromValue(User::Admin).value<QString>(), User::Admin);
    ui->cmbLevel->addItem(QVariant::fromValue(User::SuperAdmin).value<QString>(), User::SuperAdmin);
//    ui->cmbLevel->setCurrentIndex(0);
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
    User user;
    user.setAddDate(QDateTime::currentDateTime());
    user.setModifyDate(QDateTime::currentDateTime());
    loadUserParameters(user);
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

#include <QDebug>

void UserEditor::loadUserParameters(const User &user)
{
    ui->lbID->setText(QString::number(user.ID()));
    ui->leFirstName->setText(user.firstName());
    ui->leLastName->setText(user.lastName());
    ui->lbAddDate->setText(user.addDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lbModifyDate->setText(user.modifyDate().toString("yyyy-MM-dd hh:mm:ss"));

//    ui->leLevel->setText(QVariant::fromValue(user.level()).value<QString>()); // Convert enum values to text
    int index = ui->cmbLevel->findData(user.level());
    if ( index != -1 ) // -1 for not found
       ui->cmbLevel->setCurrentIndex(index);
}

User* UserEditor::getUser(void)
{
    User *user = new User;
    user->setID(ui->lbID->text().toInt());
    user->setFirstName(ui->leFirstName->text());
    user->setLastName(ui->leLastName->text());
    user->setAddDate(QDateTime::fromString(ui->lbAddDate->text(),"yyyy-MM-dd hh:mm:ss"));
    user->setModifyDate(QDateTime::fromString(ui->lbModifyDate->text(),"yyyy-MM-dd hh:mm:ss"));
    user->setLevel((User::Level)ui->cmbLevel->itemData(ui->cmbLevel->currentIndex()).toInt());
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
