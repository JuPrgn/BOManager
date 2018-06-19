#include "componenteditor.h"
#include "ui_componenteditor.h"

ComponentEditor::ComponentEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComponentEditor)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    setModal(true);
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
    ui->leCategory->setText(component.category());
    ui->leSubCategory->setText(component.subCategory());
    ui->leSpecification->setText(component.specification());
    ui->leValue->setText(component.value());
    ui->leDescription->setText(component.description());
    ui->leManuf->setText(component.manuf());
    ui->leManufRef->setText(component.manufRef());
    ui->leDistribList->setText(component.distribList().at(0));
    ui->leDistribRef->setText(component.distribRef().at(0));
    ui->leDistribQuantityList->setText(QString::number(component.distribQuantityList().at(0)));
    ui->leDevicePackage->setText(component.devicePackage());
    ui->lePackageCode->setText(component.packageCode());
    ui->leComment->setText(component.comment());
    ui->leStandard->setText(component.standard());
    ui->leAccessoryIDList->setText(QString::number(component.accessoryIDList().at(0)));
    ui->leSimilarIDList->setText(QString::number(component.similarIDList().at(0)));
    ui->leAlternativeIDList->setText(QString::number(component.alternativeIDList().at(0)));
    ui->leComponentStatus->setText(component.componentStatus());
    ui->lbAddDate->setText(component.addDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lbModifyDate->setText(component.modifyDate().toString("yyyy-MM-dd hh:mm:ss"));
    ui->lbAutor->setText(QString::number(component.autorID())); // Convert ID to text
    ui->lbModifier->setText(QString::number(component.modifierID())); // Convert ID to text
}

Component* ComponentEditor::getComponent(void)
{
    Component *component = new Component;
    component->setID(ui->lbID->text().toInt());
    component->setCategory(ui->leCategory->text());
    component->setSubCategory(ui->leSubCategory->text());
    component->setSpecification(ui->leSpecification->text());
    component->setValue(ui->leValue->text());
    component->setDescription(ui->leDescription->text());
    component->setManuf(ui->leManuf->text());
    component->setManufRef(ui->leManufRef->text());
    //component->setDistribList(ui->leDistribList->text());
    //component->setDistribRef(ui->leDistribRef->text());
    //component->setDistribQuantityList(ui->leDistribQuantityList->text());
    component->setDevicePackage(ui->leDevicePackage->text());
    component->setPackageCode(ui->lePackageCode->text());
    component->setComment(ui->leComment->text());
    component->setStandard(ui->leStandard->text());
    //component->setAccessoryIDList(ui->leAccessoryIDList->text());
    //component->setSimilarIDList(ui->leSimilarIDList->text());
    //component->setAlternativeIDList(ui->leAlternativeIDList->text());
    component->setComponentStatus(ui->leComponentStatus->text());
    component->setAddDate(QDateTime::fromString(ui->lbAddDate->text(),"yyyy-MM-dd hh:mm:ss"));
    component->setModifyDate(QDateTime::fromString(ui->lbModifyDate->text(),"yyyy-MM-dd hh:mm:ss"));
    //component->setAutorID(ui->lbAutor->text()); // Convert text to ID
    //component->setModifierID(ui->lbModifier->text()); // Convert text to ID
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
