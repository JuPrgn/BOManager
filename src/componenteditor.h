#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include <QDialog>
#include "component.h"

namespace Ui {
class ComponentEditor;
}

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class ComponentEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ComponentEditor(QWidget *parent = 0);
    ~ComponentEditor();

public slots:
    void add();
    void modify(const Component &);

private slots:
    void loadComponentParameters(const Component &component);
    Component* getComponent(void);
    void on_tbBack_clicked();
    void on_tbNext_clicked();
    void on_tbCancel_clicked();
    void on_tbFinish_clicked();

private:
    Ui::ComponentEditor *ui;

signals:
    void signalEditComponent(Component*);
};

#endif // COMPONENTEDITOR_H
