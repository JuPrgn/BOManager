#include "componenteditor.h"
#include "ui_componenteditor.h"
#include "dbparser.h"

ComponentEditor::ComponentEditor(QWidget *parent, DBParser *parser) :
    QDialog(parent),
    ui(new Ui::ComponentEditor)
{
    ui->setupUi(this);
    mDBParser = parser;

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    setModal(true);


    ui->cmbCategory->addItem("");
    ui->cmbCategory->addItems(mDBParser->parse(QString("SELECT DISTINCT category FROM component")));

    ui->cmbSubCategory->addItem("");
    ui->cmbSubCategory->addItems(mDBParser->parse(QString("SELECT DISTINCT subcategory FROM component")));

    ui->cmbDistributor->addItem("");
    for(QString str : mDBParser->parse(QString("SELECT DISTINCT distriblist FROM component")))
        ui->cmbDistributor->addItems(str.split(';'));

    ui->cmbComponentStatus->addItem("");
    ui->cmbComponentStatus->addItems(mDBParser->parse(QString("SELECT DISTINCT componentstatus FROM component")));
}

ComponentEditor::~ComponentEditor()
{
    delete ui;
}

void ComponentEditor::add()
{
    QString str("Add Component");
    setWindowTitle(str);
    ui->lbTitle->setText(str);
    Component component;
    component.setAddDate(QDateTime::currentDateTime());
    component.setModifyDate(QDateTime::currentDateTime());
    loadComponentParameters(component);
    show();
}

void ComponentEditor::modify(const Component &component)
{
    QString str("Modify Component");
    setWindowTitle(str);
    ui->lbTitle->setText(str);
    loadComponentParameters(component);
    show();
}

void ComponentEditor::loadComponentParameters(const Component &component)
{
    ui->lbID->setText(QString::number(component.ID()));
    ui->cmbCategory->setCurrentText(component.category());
    ui->cmbSubCategory->setCurrentText(component.subCategory());
    ui->leSpecification->setText(component.specification());
    ui->leValue->setText(component.value());
    ui->leDescription->setText(component.description());
    ui->cmbManufacturer->setCurrentText(component.manuf());
    ui->leManufRef->setText(component.manufRef());
    ui->cmbDistributor->setCurrentText(component.distribList());
    ui->leDistribRef->setText(component.distribRef());
    ui->leDistribQuantityList->setText(component.distribQuantityList());
    ui->cmbDevicePackage->setCurrentText(component.devicePackage());
    ui->cmbPackageCode->setCurrentText(component.packageCode());
    ui->leComment->setText(component.comment());
    ui->leStandard->setText(component.standard());
    ui->leAccessoryIDList->setText(component.accessoryIDList());
    ui->leSimilarIDList->setText(component.similarIDList());
    ui->leAlternativeIDList->setText(component.alternativeIDList());
    ui->cmbComponentStatus->setCurrentText(component.componentStatus());
    ui->lbAddDate->setText(component.addDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lbModifyDate->setText(component.modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lbAuthor->setText(QString::number(component.authorID())); // Convert ID to text
    ui->lbModifier->setText(QString::number(component.modifierID())); // Convert ID to text
}

Component* ComponentEditor::getComponent(void)
{
    Component *component = new Component;
    component->setID(ui->lbID->text().toInt());
    component->setCategory(ui->cmbCategory->currentText());
    component->setSubCategory(ui->cmbSubCategory->currentText());
    component->setSpecification(ui->leSpecification->text());
    component->setValue(ui->leValue->text());
    component->setDescription(ui->leDescription->text());
    component->setManuf(ui->cmbManufacturer->currentText());
    component->setManufRef(ui->leManufRef->text());
    component->setDistribList(ui->cmbDistributor->currentText());
    component->setDistribRef(ui->leDistribRef->text());
    component->setDistribQuantityList(ui->leDistribQuantityList->text());
    component->setDevicePackage(ui->cmbDevicePackage->currentText());
    component->setPackageCode(ui->cmbPackageCode->currentText());
    component->setComment(ui->leComment->text());
    component->setStandard(ui->leStandard->text());
    component->setAccessoryIDList(ui->leAccessoryIDList->text());
    component->setSimilarIDList(ui->leSimilarIDList->text());
    component->setAlternativeIDList(ui->leAlternativeIDList->text());
    component->setComponentStatus(ui->cmbComponentStatus->currentText());
    component->setAddDate(QDateTime::fromString(ui->lbAddDate->text(),"yyyy-MM-dd hh:mm:ss"));
    component->setModifyDate(QDateTime::fromString(ui->lbModifyDate->text(),"yyyy-MM-dd hh:mm:ss"));
    component->setAuthorID(ui->lbAuthor->text().toInt()); // Convert text to ID
    component->setModifierID(ui->lbModifier->text().toInt()); // Convert text to ID
    return component;
}

void ComponentEditor::on_tbBack_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
}

void ComponentEditor::on_tbNext_clicked()
{
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
}

void ComponentEditor::on_tbCancel_clicked()
{
    this->close();
}

void ComponentEditor::on_tbFinish_clicked()
{
    emit signalEditComponent(getComponent());
    this->close();
}

void ComponentEditor::on_cmbCategory_currentIndexChanged(const QString &arg1)
{
    if(arg1 != "")
    {
        ui->cmbSubCategory->clear();
        ui->cmbSubCategory->addItem("");
        ui->cmbSubCategory->addItems(mDBParser->parse(QString("SELECT DISTINCT subcategory FROM component WHERE category = '%1'").arg(arg1)));

        ui->cmbManufacturer->clear();
        ui->cmbManufacturer->addItem("");
        ui->cmbManufacturer->addItems(mDBParser->parse(QString("SELECT DISTINCT manuf FROM component WHERE category = '%1'").arg(arg1)));
    }
}

void ComponentEditor::on_cmbDistributor_currentIndexChanged(const QString &arg1)
{
    if(arg1 != "")
    {
        QStringList distribList = mDBParser->parse(QString("SELECT distriblist FROM component WHERE manufref = '%1'").arg(ui->leManufRef->text()));
        QStringList distribRefList = mDBParser->parse(QString("SELECT distribref FROM component WHERE manufref = '%1'").arg(ui->leManufRef->text()));
        QStringList distribQtyList = mDBParser->parse(QString("SELECT distribquantitylist FROM component WHERE manufref = '%1'").arg(ui->leManufRef->text()));

        // Check list are not empty and have the same size
        if(!distribList.isEmpty()
           && (distribList.size() == distribRefList.size() == distribQtyList.size()))
        {
            // Query should return only one result
            if(distribList.size()>1) qDebug("Error : Multiple components correspond to the manufacturer ref");

            distribList = distribList.at(0).split(';');
            distribRefList = distribRefList.at(0).split(';');
            distribQtyList = distribQtyList.at(0).split(';');

            if(distribList.contains(arg1))
            {
                int i = 0;
                for(QString str : distribList)
                {
                    if(str == arg1)
                    {
                        ui->leDistribRef->setText(distribRefList.at(i));
                        ui->leDistribQuantityList->setText(distribQtyList.at(i));
                        return;
                    }
                    i++;
                }
            }
        }
    }
    // No reference for this distributor : reset fields
    ui->leDistribRef->setText("");
    ui->leDistribQuantityList->setText("");
}
