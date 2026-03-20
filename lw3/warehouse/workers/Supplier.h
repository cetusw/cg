#pragma once
#include "Worker.h"

class Supplier final : public Worker
{
public:
	explicit Supplier(Warehouse& warehouse)
		: Worker(warehouse)
	{
	}
	void Run(std::stop_token stopToken) override;
};
