#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("employees");
    db.setUserName("root");
    db.setPassword("");

    if(db.open())
    {
        ui->statusbar->showMessage("Connection to database succesfully: " + db.databaseName());
        model = new QSqlTableModel(this,db);
        model->setTable("Users");
        model->select();
        ui->tableView->setModel(model);
    }
    else
    {
        ui->statusbar->showMessage("Connection to database failed: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    //Добавляес строку и заполняем
    model->insertRow(model->rowCount());
}


void MainWindow::on_btnRemove_clicked()
{
    //Удаляем строку
    model->removeRow(currentRow);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //Save row Сохраняем строку
    currentRow = index.row();
}

