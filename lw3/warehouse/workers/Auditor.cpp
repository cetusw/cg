#include "Auditor.h"
#include "../utils/Config.h"
#include <iostream>
#include <syncstream>

void Auditor::Run(const std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		std::osyncstream(std::cout)
			<< "[Audit] Current stock: " << m_warehouse.GetStock()
			<< "/" << m_warehouse.GetCapacity() << std::endl;
		std::this_thread::sleep_for(Config::AUDIT_INTERVAL);
	}
}