/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtSql>
#include <QDebug>

#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

//! [0]
Qt::ItemFlags EditableSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 1 || index.column() == 2 || index.column() == 5)
        flags |= Qt::ItemIsEditable;
    return flags;
}
//! [0]

//! [1]
bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    // Protect ID and addDate which are not editable
    if (index.column() < 1 || index.column() == 3)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();

    clear();

    bool ok = false;
//    qDebug() << "index.column() : " << index.column();
    switch(index.column())
    {
        case 1: ok = setFirstName(id, value.toString()); break;
        case 2: ok = setLastName(id, value.toString()); break;
        case 3: ok = setAddDate(id, value.toString()); break;
        case 4: ok = setModifyDate(id, value.toString()); break;
        case 5: ok = setLevel(id, value.toInt()); break;
    }
    refresh();
    return ok;
}
//! [1]

void EditableSqlModel::refresh()
{
    setQuery("select * from user");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("Add date"));
    setHeaderData(4, Qt::Horizontal, QObject::tr("Modify date"));
    setHeaderData(5, Qt::Horizontal, QObject::tr("Level"));
}

bool EditableSqlModel::addUser(User *user)
{
    bool ok;
    QSqlQuery query;

    // If user exist UPDATE
    ok = query.prepare("UPDATE user SET firstname=?, lastname=?, adddate=?, modifydate=?, level=? WHERE id=?");
    query.addBindValue(user->firstName());
    query.addBindValue(user->lastName());
    query.addBindValue(user->addDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(user->modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(static_cast<int>(user->level()));
    query.addBindValue(user->ID());
    ok = query.exec();
    // Else INSERT
    if (query.numRowsAffected() == 0)
    {
        ok = query.exec("SELECT MAX(id) FROM user");
        query.next();
        user->setID(query.value(0).toInt()+1);
//        qDebug()<< "INSERT" << user->ID();

        ok = query.prepare("INSERT into user VALUES(?, ?, ?, ?, ?, ?)");
//        qDebug() << "ok1 " << ok;
        query.addBindValue(user->ID());
        query.addBindValue(user->firstName());
        query.addBindValue(user->lastName());
        query.addBindValue(user->addDate().toString("yyyy-MM-dd hh:mm:ss"));
        query.addBindValue(user->modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
        query.addBindValue(static_cast<int>(user->level()));
        ok = query.exec();
//        qDebug() << "ok2 " << ok;
    }

    return ok;
    // Emit signal error if return false
}

bool EditableSqlModel::addComponent(Component *component)
{
    bool ok;
    QSqlQuery query;

    // If component exist UPDATE
    ok = query.prepare("UPDATE component SET category=?, subcategory=?, specification=?, value=?, description=?, "
                       "manuf=?, manufref=?, distriblist=?, distribref=?, distribquantitylist=?, "
                       "devicepackage=?, packagecode=?, comment=?, standard=?, accessoryidlist=?, "
                       "similaridlist=?, alternativeidlist=?, componentstatus=?, adddate=?, "
                       "modifydate=?, autorid=?, modifierid=? WHERE id=?");
    query.addBindValue(component->category());
    query.addBindValue(component->subCategory());
    query.addBindValue(component->specification());
    query.addBindValue(component->value());
    query.addBindValue(component->description());
    query.addBindValue(component->manuf());
    query.addBindValue(component->manufRef());
    query.addBindValue(component->distribList());
    query.addBindValue(component->distribRef());
    query.addBindValue(component->distribQuantityList());
    query.addBindValue(component->devicePackage());
    query.addBindValue(component->packageCode());
    query.addBindValue(component->comment());
    query.addBindValue(component->standard());
    query.addBindValue(component->accessoryIDList());
    query.addBindValue(component->similarIDList());
    query.addBindValue(component->alternativeIDList());
    query.addBindValue(component->componentStatus());
    query.addBindValue(component->addDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(component->modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(component->autorID());
    query.addBindValue(component->modifierID());
    query.addBindValue(component->ID());
    ok = query.exec();
    // Else INSERT
    if (query.numRowsAffected() == 0)
    {
        ok = query.exec("SELECT MAX(id) FROM component");
        query.next();
        component->setID(query.value(0).toInt()+1);

        ok = query.prepare("INSERT into component VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                                                        "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                                                        "?, ?, ?)");
        query.addBindValue(component->ID());
        query.addBindValue(component->category());
        query.addBindValue(component->subCategory());
        query.addBindValue(component->specification());
        query.addBindValue(component->value());
        query.addBindValue(component->description());
        query.addBindValue(component->manuf());
        query.addBindValue(component->manufRef());
        query.addBindValue(component->distribList());
        query.addBindValue(component->distribRef());
        query.addBindValue(component->distribQuantityList());
        query.addBindValue(component->devicePackage());
        query.addBindValue(component->packageCode());
        query.addBindValue(component->comment());
        query.addBindValue(component->standard());
        query.addBindValue(component->accessoryIDList());
        query.addBindValue(component->similarIDList());
        query.addBindValue(component->alternativeIDList());
        query.addBindValue(component->componentStatus());
        query.addBindValue(component->addDate().toString("yyyy-MM-dd hh:mm:ss"));
        query.addBindValue(component->modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
        query.addBindValue(component->autorID());
        query.addBindValue(component->modifierID());
        ok = query.exec();
//        qDebug() << "ok2 " << ok;
    }

    return ok;
    // Emit signal error if return false
}

bool EditableSqlModel::setFirstName(int userId, const QString &firstName)
{
    QSqlQuery query;
    query.prepare("update user set firstname = ? where id = ?");
    query.addBindValue(firstName);
    query.addBindValue(userId);
    return query.exec();
}

bool EditableSqlModel::setLastName(int userId, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("update user set lastname = ? where id = ?");
    query.addBindValue(lastName);
    query.addBindValue(userId);
    return query.exec();
}

bool EditableSqlModel::setAddDate(int userId, const QString &addDate)
{
    QSqlQuery query;
    query.prepare("update user set adddate = ? where id = ?");
    query.addBindValue(addDate);
    query.addBindValue(userId);
    return query.exec();
}

bool EditableSqlModel::setModifyDate(int userId, const QString &modifyDate)
{
    QSqlQuery query;
    query.prepare("update user set modifydate = ? where id = ?");
    query.addBindValue(modifyDate);
    query.addBindValue(userId);
    return query.exec();
}
bool EditableSqlModel::setLevel(int userId, const int &level)
{
    QSqlQuery query;
    query.prepare("update user set level = ? where id = ?");
    query.addBindValue(level);
    query.addBindValue(userId);
    return query.exec();
}

