#include "tableViewTest.h"
#include <QtWidgets/QApplication>
#include "DataCaChed.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataCached::get_instance().init();

    tableViewTest w;
    w.show();
    int ret = a.exec();
    DataCached::get_instance().exit();
    return ret;
}
