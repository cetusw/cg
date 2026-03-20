#pragma once
#include "Worker.h"

class Auditor final : public Worker
{
public:
	explicit Auditor(Warehouse& warehouse)
		: Worker(warehouse)
	{
	}
	void Run(std::stop_token stopToken) override;
};
