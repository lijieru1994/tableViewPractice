#include "tableViewTest.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlError>

#include <QDebug>


tableViewTest::tableViewTest(QWidget *parent)
    : QMainWindow(parent)
    , tableView(nullptr)
    , btnLoad(nullptr)
    , btnClear(nullptr)
{
    ui.setupUi(this);
    btnLoad = ui.pushButton_0;
    connect(btnLoad, SIGNAL(clicked()), this, SLOT(btnLoadIsClicked()));

    btnClear = ui.pushButton_1;
    connect(btnClear, SIGNAL(clicked()), this, SLOT(btnClearIsClicked()));

    tableView = ui.tableView;
    connect(tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(ItemIsDoubleClicked(const QModelIndex&)));

    QStringList strListHeader;
    strListHeader << QString::fromLocal8Bit("ѡ��") << QString::fromLocal8Bit("֪ͨ��LSH") << QString::fromLocal8Bit("�ͺ�") << QString::fromLocal8Bit("���") << QString::fromLocal8Bit("����")
        << QString::fromLocal8Bit("���") << QString::fromLocal8Bit("�ܾ���");
    
    DatabaseInit();
}

tableViewTest::~tableViewTest()
{}

void tableViewTest::DatabaseInit()
{
    QStringList strListDrivers = QSqlDatabase::drivers();
    if (!strListDrivers.contains("QODBC"))
        return;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=192.168.21.206;DATABASE=RXSCALE_KL");
    db.setUserName("sa");
    db.setPassword("lijieru");
    db.setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=10");
    if (!db.isOpen())
    {
        db.setConnectOptions();
        qDebug() << db.lastError().type();
    }
    db.close();    
}

void tableViewTest::btnLoadIsClicked()
{

}

void tableViewTest::btnClearIsClicked()
{

}

void tableViewTest::ItemIsDoubleClicked(const QModelIndex& index)
{

}