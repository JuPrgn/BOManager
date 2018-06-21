#include <QtSql>
#include "dbparser.h"

DBParser::DBParser(QObject *parent) : QObject(parent)
{

}

/*!
 * \brief DBParser::getUser
 * Search User by ID : field ID in user should be set
 * Search User by name : both fields firstName and lastName should be set
 * \param user
 * \return
 */
bool DBParser::getUser(User *user)
{
    bool ok = false;
    QSqlQuery query;

    if(user->ID()!=0) // Find by ID
    {
        ok = query.prepare("SELECT * FROM user WHERE id=?");
        query.addBindValue(user->ID());
        ok = query.exec();
    }
    else if(user->firstName()!="" && user->lastName()!="") // Find by name
    {
        ok = query.exec("SELECT * FROM user WHERE firstname=? AND lastname =?");
        query.addBindValue(user->firstName());
        query.addBindValue(user->lastName());
        ok = query.exec();
    }

    // Return if no searching parameter or invalid query
    if(ok==false)
        return false;

    // Parse answer
    query.next();
    user->setID(query.value(0).toInt());
    user->setFirstName(query.value(1).toString());
    user->setLastName(query.value(2).toString());
    user->setAddDate(QDateTime::fromString(query.value(3).toString(),"yyyy-MM-dd hh:mm:ss"));
    user->setModifyDate(QDateTime::fromString(query.value(4).toString(),"yyyy-MM-dd hh:mm:ss"));
    user->setLevel((User::Level)query.value(5).toInt());

    return ok; // Return query result
    // Emit signal error if return false
}

bool DBParser::addUser(User *user)
{
    bool ok = false;
    QSqlQuery query;

    // If user exist UPDATE else INSERT
    if(!updateUser(user))
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

    return ok; // Return query result
    // Emit signal error if return false
}

bool DBParser::updateUser(User *user)
{
    bool ok = false;
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

    if (query.numRowsAffected() == 0)
       return false; // User doesn't exist

    return ok; // Return query result
}

/*!
 * \brief DBParser::getComponent
 * Search Component by ID : field ID should be set
 * \param component
 * \return
 */
bool DBParser::getComponent(Component *component)
{
    bool ok = false;
    QSqlQuery query;

    if(component->ID()!=0) // Find by ID
    {
        ok = query.prepare("SELECT * FROM component WHERE id=?");
        query.addBindValue(component->ID());
        ok = query.exec();
    }
//    else if(component->firstName()!="" && component->lastName()!="") // Find by name
//    {
//        ok = query.exec("SELECT * FROM user WHERE firstname=? AND lastname =?");
//        query.addBindValue(user->firstName());
//        query.addBindValue(user->lastName());
//        ok = query.exec();
//    }

    // Return if no searching parameter or invalid query
    if(ok==false)
        return false;

    // Parse answer
    query.next();
    component->setID(query.value(0).toInt());
    component->setCategory(query.value(1).toString());
    component->setSubCategory(query.value(2).toString());
    component->setSpecification(query.value(3).toString());
    component->setValue(query.value(4).toString());
    component->setDescription(query.value(5).toString());
    component->setManuf(query.value(6).toString());
    component->setManufRef(query.value(7).toString());
    component->setDistribList(query.value(8).toString());
    component->setDistribRef(query.value(9).toString());
    component->setDistribQuantityList(query.value(10).toString());
    component->setDevicePackage(query.value(11).toString());
    component->setPackageCode(query.value(12).toString());
    component->setComment(query.value(13).toString());
    component->setStandard(query.value(14).toString());
    component->setAccessoryIDList(query.value(15).toString());
    component->setSimilarIDList(query.value(16).toString());
    component->setAlternativeIDList(query.value(17).toString());
    component->setComponentStatus(query.value(18).toString());
    component->setAddDate(QDateTime::fromString(query.value(19).toString(),"yyyy-MM-dd hh:mm:ss"));
    component->setModifyDate(QDateTime::fromString(query.value(20).toString(),"yyyy-MM-dd hh:mm:ss"));
    component->setAutorID(query.value(21).toInt());
    component->setModifierID(query.value(22).toInt());

    return ok; // Return query result
    // Emit signal error if return false
}

bool DBParser::addComponent(Component *component)
{
    bool ok = false;
    QSqlQuery query;

    // If component exist UPDATE else INSERT
    if (!updateComponent(component))
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

bool DBParser::updateComponent(Component *component)
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

    if (query.numRowsAffected() == 0)
       return false; // Component doesn't exist

    return ok; // Return query result
}

QStringList DBParser::getComponentCategory()
{
    return listColumnDistinctValue("component", "category");
}

QStringList DBParser::getComponentSubCategory()
{
    return listColumnDistinctValue("component", "subcategory");
}

QStringList DBParser::listColumnDistinctValue(QString Table, QString Column)
{
    QSqlQuery query;
    QStringList strList;

    query.exec(QString("SELECT DISTINCT %1 FROM %2").arg(Column).arg(Table));

    // Parse answer
    while(query.next())
        strList.append(query.value(0).toString());

    return strList;
}

