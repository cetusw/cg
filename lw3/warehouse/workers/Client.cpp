#include "Client.h"
#include "../utils/Config.h"
#include "../utils/Rand.h"

void Client::Run(const std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		const int amount = Rand::Get(1, Config::MAX_PURCHASE_AMOUNT);
		if (m_warehouse.TryToTake(amount))
		{
			m_totalProcessed += amount;
		}
		std::this_thread::sleep_for(Config::PURCHASE_INTERVAL);
	}
}