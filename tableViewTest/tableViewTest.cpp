#include "tableViewTest.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
#include "DataCaChed.h"
#include <QCheckBox>


tableViewTest::tableViewTest(QWidget *parent)
    : QMainWindow(parent)
    , m_tableView(nullptr)
    , btnLoad(nullptr)
    , btnClear(nullptr)
{
    ui.setupUi(this);
    btnLoad = ui.pushButton_0;
    connect(btnLoad, SIGNAL(clicked()), this, SLOT(btnLoadIsClicked()));

    btnClear = ui.pushButton_1;
    connect(btnClear, SIGNAL(clicked()), this, SLOT(btnClearIsClicked()));

    m_tableView = ui.tableView;
    connect(m_tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(ItemIsDoubleClicked(const QModelIndex&)));

    QStringList strListHeader;
    strListHeader << QString::fromLocal8Bit("选择") << QString::fromLocal8Bit("通知单编号") << QString::fromLocal8Bit("型号") << QString::fromLocal8Bit("厚度") << QString::fromLocal8Bit("长度")
        << QString::fromLocal8Bit("宽度") << QString::fromLocal8Bit("总卷数");
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(strListHeader.size());
    model->setHorizontalHeaderLabels(strListHeader);
    m_tableView->setModel(model);
    m_tableView->verticalHeader()->show();
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
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isValid())
    {
        QSqlQuery query(db);
        query.prepare("SELECT TOP (10) [TZDBH],[XH],[GGDEEP],[GGWIDTH],[GGLENGTH],[ROLL],[TZDLSH] FROM [RXSCALE_KL].[dbo].[T_SCTZD_WXMX] where [XH] = ? and [GGDEEP] = ?;");
        query.bindValue(0, "PG11");
        query.bindValue(1, 25);
        query.exec();
        if (query.isActive())
        {
            while (query.next())
            {
                DataOrder orderItem;
                orderItem.TZDBH = query.value("TZDBH").toString();
                orderItem.type = query.value("XH").toString();
                orderItem.orderThickness = query.value("GGDEEP").toInt();
                orderItem.orderWidth = query.value("GGWIDTH").toInt();
                orderItem.orderLength = query.value("GGLENGTH").toInt();
                qDebug() << query.value("ROLL").toInt();
                orderItem.orderRolls = query.value("ROLL").toInt();
                orderItem.TZDLSH = query.value("TZDLSH").toString();

                DataCached::get_instance().getDataCached()->push_back(orderItem);
            }
            std::vector<DataOrder>* vecDatas = DataCached::get_instance().getDataCached();
            if (vecDatas->size())
            {
                QStandardItemModel* model = qobject_cast<QStandardItemModel*>(m_tableView->model());
                int row = 0;
                for (auto& it : *vecDatas)
                {
                    int col = 0;
                    col++;
                    QStandardItem* item = new QStandardItem(it.TZDBH);
                    item->setData(it.TZDLSH);
                    model->setItem(row, col, item);
                    model->item(row, col)->setTextAlignment(Qt::AlignCenter);

					col++;
					model->setItem(row, col, new QStandardItem(it.type));
					model->item(row, col)->setTextAlignment(Qt::AlignCenter);

					col++;
					model->setItem(row, col, new QStandardItem(QString::number(it.orderThickness)));
					model->item(row, col)->setTextAlignment(Qt::AlignCenter);

					col++;
					model->setItem(row, col, new QStandardItem(QString::number(it.orderLength)));
					model->item(row, col)->setTextAlignment(Qt::AlignCenter);

					col++;
					model->setItem(row, col, new QStandardItem(QString::number(it.orderWidth)));
					model->item(row, col)->setTextAlignment(Qt::AlignCenter);

					col++;
					model->setItem(row, col, new QStandardItem(QString::number(it.orderRolls)));
					model->item(row, col)->setTextAlignment(Qt::AlignCenter);

					QWidget* widget = new QWidget();
					widget->setFixedWidth(40);
					QCheckBox* checkbox = new QCheckBox();
					checkbox->setChecked(false);
					checkbox->setFixedHeight(24);
					QGridLayout* layout = new QGridLayout();
					checkbox->setObjectName(QString("check_box"));

					layout->addWidget(checkbox);
					layout->setAlignment(Qt::AlignCenter);
					widget->setLayout(layout);
					m_tableView->setIndexWidget(model->index(row, 0), widget);

                    row++;
                }
                m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
                m_tableView->setColumnWidth(0, 40);

#ifdef TEST_GET_CHECKBOX 
				QWidget* pWidget = m_tableView->indexWidget(model->index(0, 0));
                if (pWidget)
                {
                    QCheckBox* pCheckBox = pWidget->findChild<QCheckBox*>(QString::fromLocal8Bit("check_box"));
                    qDebug() << pCheckBox->isChecked();
                }
#endif
            }
        }
    }
}

void tableViewTest::btnClearIsClicked()
{

}

void tableViewTest::ItemIsDoubleClicked(const QModelIndex& index)
{

}