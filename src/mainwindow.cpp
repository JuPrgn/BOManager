#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include "editablesqlmodel.h"
#include "userview.h"
#include "usereditor.h"
#include "componenteditor.h"

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

    mComponentEditor = new ComponentEditor;

    // Test add User
//    mUserEditor->add();

    // Test modify User
    Component *component = new Component;
    component->setID(2);
    component->setCategory("Résistance");
    component->setSubCategory("Résistance CMS");
    component->setSpecification("1/8W");
    component->setValue("0");
    component->setDescription("Résistance CMS R0805 1/8W");
    component->setManuf("PANASONIC");
    component->setManufRef("ERJ6GEY0R00V");
    component->setDistribList("FARNELL");
    component->setDistribRef("2057661");
//    component->setDistribQuantityList();
    component->setDevicePackage("R-EU_R0805");
    component->setPackageCode("R0805");
    component->setComment("");
    component->setStandard("");
//    component->setAccessoryIDList();
//    component->setSimilarIDList();
//    component->setAlternativeIDList();
    component->setComponentStatus("Active");
    component->setAddDate(QDateTime::currentDateTime());
    component->setModifyDate(QDateTime::currentDateTime());
    component->setAutorID(1);
    component->setModifierID(1);

    mComponentEditor->modify(*component);
    QObject::connect(mComponentEditor, &ComponentEditor::signalEditComponent,
                     mModel, &EditableSqlModel::addComponent);
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
