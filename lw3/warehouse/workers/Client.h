#pragma once
#include "Worker.h"

class Client final : public Worker
{
public:
	explicit Client(Warehouse& warehouse)
		: Worker(warehouse)
	{
	}
	void Run(std::stop_token stopToken) override;
};
