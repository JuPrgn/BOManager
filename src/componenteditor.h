#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include <QDialog>
#include "component.h"

namespace Ui {
class ComponentEditor;
}

QT_BEGIN_NAMESPACE
class DBParser;
QT_END_NAMESPACE

class ComponentEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ComponentEditor(QWidget *parent = 0, DBParser *parser = nullptr);
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

    void on_cmbCategory_currentIndexChanged(const QString &arg1);

private:
    Ui::ComponentEditor *ui;
    DBParser *mDBParser;

signals:
    void signalEditComponent(Component*);
};

#endif // COMPONENTEDITOR_H
