#pragma once
#include "workers/Auditor.h"
#include "workers/Client.h"
#include "workers/Supplier.h"
#include <memory>
#include <vector>

class Application
{
public:
	Application(int numSuppliers, int numClients, int numAuditors, int capacity);

	void Run();

private:
	Warehouse m_warehouse;
	std::vector<std::unique_ptr<Supplier>> m_suppliers;
	std::vector<std::unique_ptr<Client>> m_clients;
	std::vector<std::unique_ptr<Auditor>> m_auditors;
	std::vector<std::thread> m_threads;
	int m_numSuppliers;
	int m_numClients;
	int m_numAuditors;

	void CreateThreads();
	void JoinThreads();
	void PrintStatistics() const;
};
