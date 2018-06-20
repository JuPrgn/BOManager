#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include <QDateTime>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class Component : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 id READ ID WRITE setID NOTIFY IDChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString subCategory READ subCategory WRITE setSubCategory NOTIFY subCategoryChanged)
    Q_PROPERTY(QString specification READ specification WRITE setSpecification NOTIFY specificationChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString manuf READ manuf WRITE setManuf NOTIFY manufChanged)
    Q_PROPERTY(QString manufRef READ manufRef WRITE setManufRef NOTIFY manufRefChanged)
    Q_PROPERTY(QString distribList READ distribList WRITE setDistribList NOTIFY distribListChanged)
    Q_PROPERTY(QString distribRef READ distribRef WRITE setDistribRef NOTIFY distribRefChanged)
    Q_PROPERTY(QString distribQuantityList READ distribQuantityList WRITE setDistribQuantityList NOTIFY distribQuantityListChanged)
    Q_PROPERTY(QString devicePackage READ devicePackage WRITE setDevicePackage NOTIFY devicePackageChanged)
    Q_PROPERTY(QString packageCode READ packageCode WRITE setPackageCode NOTIFY packageCodeChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QString standard READ standard WRITE setStandard NOTIFY standardChanged)
    Q_PROPERTY(QString accessoryIDList READ accessoryIDList WRITE setAccessoryIDList NOTIFY accessoryIDListChanged)
    Q_PROPERTY(QString similarIDList READ similarIDList WRITE setSimilarIDList NOTIFY similarIDListChanged)
    Q_PROPERTY(QString alternativeIDList READ alternativeIDList WRITE setAlternativeIDList NOTIFY alternativeIDListChanged)
    Q_PROPERTY(QString componentStatus READ componentStatus WRITE setComponentStatus NOTIFY componentStatusChanged)
    Q_PROPERTY(QDateTime addDate READ addDate WRITE setAddDate NOTIFY addDateChanged)
    Q_PROPERTY(QDateTime modifyDate READ modifyDate WRITE setModifyDate NOTIFY modifyDateChanged)
    Q_PROPERTY(quint16 autorID READ autorID WRITE setAutorID NOTIFY autorIDChanged)
    Q_PROPERTY(quint16 modifierID READ modifierID WRITE setModifierID NOTIFY modifierIDChanged)

public:
    Component(){}

    void setID(quint16 value)                       { mID = value;                  emit IDChanged(value); }
    void setCategory(QString value)                 { mCategory = value;            emit categoryChanged(value); }
    void setSubCategory(QString value)              { mSubCategory = value;         emit subCategoryChanged(value); }
    void setSpecification(QString value)            { mSpecification = value;       emit specificationChanged(value); }
    void setValue(QString value)                    { mValue = value;               emit valueChanged(value); }
    void setDescription(QString value)              { mDescription = value;         emit descriptionChanged(value); }
    void setManuf(QString value)                    { mManuf = value;               emit manufChanged(value); }
    void setManufRef(QString value)                 { mManufRef = value;            emit manufRefChanged(value); }
    void setDistribList(QString value)              { mDistribList = value;         emit distribListChanged(value); }
    void setDistribRef(QString value)               { mDistribRef = value;          emit distribRefChanged(value); }
    void setDistribQuantityList(QString value)      { mDistribQuantityList = value; emit distribQuantityListChanged(value); }
    void setDevicePackage(QString value)            { mDevicePackage = value;       emit devicePackageChanged(value); }
    void setPackageCode(QString value)              { mPackageCode = value;         emit packageCodeChanged(value); }
    void setComment(QString value)                  { mComment = value;             emit commentChanged(value); }
    void setStandard(QString value)                 { mStandard = value;            emit standardChanged(value); }
    void setAccessoryIDList(QString value)          { mAccessoryIDList = value;     emit accessoryIDListChanged(value); }
    void setSimilarIDList(QString value)            { mSimilarIDList = value;       emit similarIDListChanged(value); }
    void setAlternativeIDList(QString value)        { mAlternativeIDList = value;   emit alternativeIDListChanged(value); }
    void setComponentStatus(QString value)          { mComponentStatus = value;     emit componentStatusChanged(value); }
    void setAddDate(QDateTime value)                { mAddDate = value;             emit addDateChanged(value); }
    void setModifyDate(QDateTime value)             { mModifyDate = value;          emit modifyDateChanged(value); }
    void setAutorID(quint16 value)                  { mAutorID = value;             emit autorIDChanged(value); }
    void setModifierID(quint16 value)               { mModifierID = value;          emit modifierIDChanged(value); }

    quint16 ID() const { return mID; }
    QString category() const { return mCategory; }
    QString subCategory() const { return mSubCategory; }
    QString specification() const { return mSpecification; }
    QString value() const { return mValue; }
    QString description() const { return mDescription; }
    QString manuf() const { return mManuf; }
    QString manufRef() const { return mManufRef; }
    QString distribList() const { return mDistribList; }
    QString distribRef() const { return mDistribRef; }
    QString distribQuantityList() const { return mDistribQuantityList; }
    QString devicePackage() const { return mDevicePackage; }
    QString packageCode() const { return mPackageCode; }
    QString comment() const { return mComment; }
    QString standard() const { return mStandard; }
    QString accessoryIDList() const { return mAccessoryIDList; }
    QString similarIDList() const { return mSimilarIDList; }
    QString alternativeIDList() const { return mAlternativeIDList; }
    QString componentStatus() const { return mComponentStatus; }
    QDateTime addDate() const { return mAddDate; }
    QDateTime modifyDate() const { return mModifyDate; }
    quint16 autorID() const { return mAutorID; }
    quint16 modifierID() const { return mModifierID; }

signals:
    void IDChanged(quint16);
    void categoryChanged(QString);
    void subCategoryChanged(QString);
    void specificationChanged(QString);
    void valueChanged(QString);
    void descriptionChanged(QString);
    void manufChanged(QString);
    void manufRefChanged(QString);
    void distribListChanged(QString);
    void distribRefChanged(QString);
    void distribQuantityListChanged(QString);
    void devicePackageChanged(QString);
    void packageCodeChanged(QString);
    void commentChanged(QString);
    void standardChanged(QString);
    void accessoryIDListChanged(QString);
    void similarIDListChanged(QString);
    void alternativeIDListChanged(QString);
    void componentStatusChanged(QString);
    void addDateChanged(QDateTime);
    void modifyDateChanged(QDateTime);
    void autorIDChanged(quint16);
    void modifierIDChanged(quint16);

public slots:

private:
    quint16 mID = 0;
    QString mCategory;
    QString mSubCategory;
    QString mSpecification;
    QString mValue;
    QString mDescription;
    QString mManuf;
    QString mManufRef;
    QString mDistribList;
    QString mDistribRef;
    QString mDistribQuantityList;
    QString mDevicePackage;
    QString mPackageCode;
    QString mComment;
    QString mStandard;
    QString mAccessoryIDList;
    QString mSimilarIDList;
    QString mAlternativeIDList;
    QString mComponentStatus;
    QDateTime mAddDate = QDateTime();
    QDateTime mModifyDate = QDateTime();
    quint16 mAutorID;
    quint16 mModifierID;
};

#endif // COMPONENT_H
