#ifndef DBPARSER_H
#define DBPARSER_H

#include <QObject>
#include <QSqlQueryModel>
#include "user.h"
#include "component.h"

class DBParser : public QObject
{
    Q_OBJECT
public:
    explicit DBParser(QObject *parent = nullptr);

signals:

public slots:
    bool getUser(User*);
    bool addUser(User*);
    bool updateUser(User*);

    bool getComponent(Component*);
    bool addComponent(Component*);
    bool updateComponent(Component*);

    QStringList parse(QString SQL);
};

#endif // DBPARSER_H
