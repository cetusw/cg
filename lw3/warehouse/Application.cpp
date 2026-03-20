#include "Application.h"
#include "utils/SignalHandler.h"

#include <iostream>

Application::Application(const int numSuppliers, const int numClients, const int numAuditors, const int capacity)
	: m_warehouse(capacity)
	, m_numSuppliers(numSuppliers)
	, m_numClients(numClients)
	, m_numAuditors(numAuditors)
{
}

void Application::Run()
{
	std::cout << "Warehouse is running..." << std::endl;

	SignalHandler::Setup();
	CreateThreads();

	JoinThreads();

	std::cout << std::endl;

	PrintStatistics();
}

void Application::CreateThreads()
{
	for (int i = 0; i < m_numSuppliers; ++i)
	{
		m_suppliers.push_back(std::make_unique<Supplier>(m_warehouse));
		m_threads.emplace_back(&Supplier::Run, m_suppliers.back().get(), SignalHandler::GetToken());
	}
	for (int i = 0; i < m_numClients; ++i)
	{
		m_clients.push_back(std::make_unique<Client>(m_warehouse));
		m_threads.emplace_back(&Client::Run, m_clients.back().get(), SignalHandler::GetToken());
	}
	for (int i = 0; i < m_numAuditors; ++i)
	{
		m_auditors.push_back(std::make_unique<Auditor>(m_warehouse));
		m_threads.emplace_back(&Auditor::Run, m_auditors.back().get(), SignalHandler::GetToken());
	}
}

void Application::JoinThreads()
{
	for (auto& thread : m_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void Application::PrintStatistics() const
{
	std::cout << "--- Final Statistics ---" << std::endl;

	int totalSupplied = 0;
	for (const auto& supplier : m_suppliers)
	{
		totalSupplied += supplier->GetTotalProcessed();
	}
	std::cout << "Total items supplied: " << totalSupplied << std::endl;

	int totalBought = 0;
	for (const auto& client : m_clients)
	{
		totalBought += client->GetTotalProcessed();
	}
	std::cout << "Total items bought: " << totalBought << std::endl;

	std::cout << "Remaining stock: " << m_warehouse.GetStock() << std::endl;
}