#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDateTime>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 id READ ID WRITE setID NOTIFY IDChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QDateTime addDate READ addDate WRITE setAddDate NOTIFY addDateChanged)
    Q_PROPERTY(QDateTime modifyDate READ modifyDate WRITE setModifyDate NOTIFY modifyDateChanged)
    Q_PROPERTY(Level level READ level WRITE setLevel NOTIFY levelChanged)

public:
    User(){}

    enum Level { SuperAdmin, Admin, StandardUser, Viewer };
    Q_ENUM(Level)

    void setID(quint16 id)                      { mID = id;                 emit IDChanged(id); }
    void setFirstName(QString firstName)        { mFirstName = firstName;   emit firstNameChanged(firstName); }
    void setLastName(QString lastName)          { mLastName = lastName;     emit lastNameChanged(lastName); }
    void setAddDate(QDateTime addDate)          { mAddDate = addDate;       emit addDateChanged(addDate); }
    void setModifyDate(QDateTime modifyDate)    { mModifyDate = modifyDate; emit modifyDateChanged(modifyDate); }
    void setLevel(Level level)                  { mLevel = level;           emit levelChanged(level); }

    quint16 ID() const                          { return mID; }
    QString firstName() const                   { return mFirstName; }
    QString lastName() const                    { return mLastName; }
    QDateTime addDate() const                   { return mAddDate; }
    QDateTime modifyDate() const                { return mModifyDate; }
    Level level() const                         { return mLevel; }

//    void copy(User user)
//    {
//        setID(user.ID());
//        setFirstName(user.firstName());
//        setLastName(user.lastName());
//        setAddDate(user.addDate());
//        setModifyDate(user.modifyDate());
//        setLevel(user.level());
//    }

signals:
    void IDChanged(quint16);
    void firstNameChanged(QString);
    void lastNameChanged(QString);
    void addDateChanged(QDateTime);
    void modifyDateChanged(QDateTime);
    void levelChanged(Level);

public slots:

private:
    quint16 mID = 0;
    QString mFirstName;
    QString mLastName;
    QDateTime mAddDate = QDateTime();
    QDateTime mModifyDate = QDateTime();
    Level mLevel = Viewer;
};

#endif // USER_H
