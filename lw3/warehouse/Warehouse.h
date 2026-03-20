#pragma once
#include <condition_variable>
#include <mutex>
#include <shared_mutex>

class Warehouse
{
public:
	explicit Warehouse(int capacity);

	bool TryToAdd(int amount);
	bool TryToTake(int amount);

	int GetCapacity() const;
	int GetStock() const;

private:
	const int m_capacity;
	int m_stock;
	mutable std::shared_mutex m_mutex;
};
