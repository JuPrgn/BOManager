#include "userview.h"

#include "connection.h"
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QGridLayout>

UserView::UserView(QWidget *parent) : QWidget(parent)
{
    view = nullptr;
}

QTableView* UserView::createView(QSqlQueryModel *model, const QString &title = "")
{
    view = new QTableView;
    view->setModel(model);
    static int offset = 0;

    view->setWindowTitle(title);
    view->move(100 + offset, 100 + offset);
    offset += 20;
//    view->show();

    QVBoxLayout* tableLay = new QVBoxLayout(this);
    tableLay->addWidget(view);

    return view;
}
