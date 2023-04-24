#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tableViewTest.h"
#include <QTableView>
#include <QPushButton>

class tableViewTest : public QMainWindow
{
    Q_OBJECT

public:
    tableViewTest(QWidget *parent = nullptr);
    ~tableViewTest();

    void DatabaseInit();

private:
    Ui::tableViewTestClass ui;
    QTableView* tableView;
    QPushButton* btnLoad;
    QPushButton* btnClear;

public slots:
    void btnLoadIsClicked();
    void btnClearIsClicked();

    void ItemIsDoubleClicked(const QModelIndex& index);
};
