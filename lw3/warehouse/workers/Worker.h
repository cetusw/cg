#pragma once
#include "../Warehouse.h"

class Worker
{
public:
	explicit Worker(Warehouse& warehouse);
	virtual ~Worker() = default;

	virtual void Run(std::stop_token stopToken) = 0;
	int GetTotalProcessed() const;

protected:
	Warehouse& m_warehouse;
	int m_totalProcessed;
};
