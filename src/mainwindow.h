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
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EditableSqlModel *mModel = nullptr;
    UserView *mUserView = nullptr;
    UserEditor *mUserEditor = nullptr;
    void initializeModel(QSqlQueryModel *model);
    void createUserTable();
};

#endif // MAINWINDOW_H
