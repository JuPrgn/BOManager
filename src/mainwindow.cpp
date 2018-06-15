#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include "editablesqlmodel.h"
#include "userview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new EditableSqlModel;
    initializeModel(mModel);
    mUserView = new UserView;
    mUserView->createView(mModel, QObject::tr("Editable Query Model"));

    setCentralWidget(mUserView);
}

MainWindow::~MainWindow()
{
    delete mModel;
    delete mUserView;
    delete ui;
}

void MainWindow::initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from person");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}
