#include "Supplier.h"
#include "../utils/Config.h"
#include "../utils/Rand.h"

void Supplier::Run(const std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		const int amount = Rand::Get(1, Config::MAX_SUPPLY_AMOUNT);
		if (m_warehouse.TryToAdd(amount))
		{
			m_totalProcessed += amount;
		}
		std::this_thread::sleep_for(Config::SUPPLY_INTERVAL);
	}
}