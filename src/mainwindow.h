#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QSqlQueryModel;
class QGridLayout;
class EditableSqlModel;
class UserView;
class UserEditor;
class User;
class ComponentEditor;
class DBParser;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbAddUser_clicked();
    void on_pbModifyUser_clicked();
    void on_pbAddComponent_clicked();
    void on_pbModifyComponent_clicked();

private:
    Ui::MainWindow *ui;
    DBParser *mDBParser = nullptr;
    EditableSqlModel *mModel = nullptr;
    UserView *mUserView = nullptr;
    UserEditor *mUserEditor = nullptr;
    ComponentEditor *mComponentEditor = nullptr;
    void initializeModel(QSqlQueryModel *model);
};

#endif // MAINWINDOW_H
