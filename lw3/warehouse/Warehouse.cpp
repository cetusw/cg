#include "Warehouse.h"

#include <shared_mutex>

Warehouse::Warehouse(const int capacity)
	: m_capacity(capacity)
	, m_stock(0)
{
}

bool Warehouse::TryToAdd(const int amount)
{
	std::unique_lock lock(m_mutex);
	if (m_stock + amount > m_capacity)
	{
		return false;
	}
	m_stock += amount;
	lock.unlock();
	return true;
}

bool Warehouse::TryToTake(const int amount)
{
	std::unique_lock lock(m_mutex);
	if (m_stock < amount)
	{
		return false;
	}
	m_stock -= amount;
	lock.unlock();
	return true;
}

int Warehouse::GetCapacity() const
{
	return m_capacity;
}

int Warehouse::GetStock() const
{
	std::shared_lock lock(m_mutex);
	return m_stock;
}