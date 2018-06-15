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
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EditableSqlModel *mModel;
    UserView *mUserView;
    void initializeModel(QSqlQueryModel *model);
};

#endif // MAINWINDOW_H
