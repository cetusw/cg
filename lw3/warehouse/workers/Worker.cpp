#include "Worker.h"

Worker::Worker(Warehouse& warehouse)
	: m_warehouse(warehouse)
	, m_totalProcessed(0)
{
}

int Worker::GetTotalProcessed() const
{
	return m_totalProcessed;
}