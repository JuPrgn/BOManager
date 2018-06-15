#ifndef USERVIEW_H
#define USERVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTableView;
class QSqlQueryModel;
QT_END_NAMESPACE

class UserView : public QWidget
{
    Q_OBJECT
public:
    explicit UserView(QWidget *parent = nullptr);
    QTableView* createView(QSqlQueryModel *model, const QString &title);

signals:

public slots:

private:
    QTableView *view;
};

#endif // USERVIEW_H
