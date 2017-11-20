#include "login_window.h"
#include "ui_login_window.h"

#include "limit_checker.h"
#include "message_dialog.h"
#include "global_storage.h"

#include "consts.h"
#include "roles.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    checkLogin(username, password);
    doLogin(username, password);
}

void LoginWindow::checkLogin(const QString &username, const QString &password)
{
    QString error;
    if ((error = LimitChecker::instance()->check(username)) != "")
        MessageDialog::instance()->err(QString("Username %1!").arg(error), this);
    else if ((error = LimitChecker::instance()->check(password)) != "")
        MessageDialog::instance()->err(QString("Password %1!").arg(error), this);
}

void LoginWindow::doLogin(const QString &username, const QString &password)
{
    if (username != password)
        MessageDialog::instance()->err("Username or password is incorrect!", this);
    else if (username == "admin")
        GlobalStorage::instance()->put(USER_ROLE, Admin);
    else if (username == "commander")
        GlobalStorage::instance()->put(USER_ROLE, Roles::Commander);
    else
        GlobalStorage::instance()->put(USER_ROLE, Roles::Guest);
}
