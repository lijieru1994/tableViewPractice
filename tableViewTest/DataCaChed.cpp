#include "DataCached.h"

DataCached::DataCached() : vecOrders(nullptr)
{
}

DataCached::~DataCached()
{
}

void DataCached::init()
{
	vecOrders = new std::vector<DataOrder>();
}

void DataCached::exit()
{
	delete vecOrders;
	vecOrders = nullptr;
}

std::vector<DataOrder>* DataCached::getDataCached()
{
	return vecOrders;
}
