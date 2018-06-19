#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include "editablesqlmodel.h"
#include "userview.h"
#include "usereditor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new EditableSqlModel;
    initializeModel(mModel); // Equal to refresh() but private method

    mUserView = new UserView;
    mUserView->createView(mModel, QObject::tr("Editable Query Model"));
    setCentralWidget(mUserView);

    mUserEditor = new UserEditor;

    // Test add User
//    mUserEditor->add();

    // Test modify User
    User *user = new User;
    user->setID(2);
    user->setFirstName("Julien");
    user->setLastName("PEYREGNE");
    user->setAddDate(QDateTime::currentDateTime());
    user->setModifyDate(QDateTime::currentDateTime());
    user->setLevel(User::Admin);
    mUserEditor->modify(*user);

    QObject::connect(mUserEditor, &UserEditor::signalEditUser,
                     mModel, &EditableSqlModel::addUser);
}

MainWindow::~MainWindow()
{
    if(mModel != nullptr) delete mModel;
    if(mUserView != nullptr) delete mUserView;
    if(mUserEditor != nullptr) delete mUserEditor;
    delete ui;
}

void MainWindow::initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from user");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Add date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Modify date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Level"));
}
