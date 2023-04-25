#ifndef _DataCached_H_
#define _DataCached_H_
#include <QObject>

#include "singleton.h"

typedef struct _DataOrder
{
	_DataOrder() : orderLength(0), orderThickness(0), orderWidth(0), orderRolls(0){}

	QString TZDBH;
	QString TZDLSH;
	QString type;
	int orderLength;
	int orderThickness;
	int orderWidth;
	int orderRolls;
}DataOrder;

class DataCached final : public async::detail::singleton<DataCached>
{
public:
	DataCached();
	virtual ~DataCached();
	void init();
	void exit();

	std::vector<DataOrder>* getDataCached();
	
protected:
	DataCached(const DataCached&) = delete;
	DataCached& operator=(const DataCached&) = delete;

private:
	std::vector<DataOrder>* vecOrders;
};
#endif