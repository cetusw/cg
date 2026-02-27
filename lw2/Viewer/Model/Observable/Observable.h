#pragma once

#include "../../View/Observer/IObserver.h"

#include <vector>

class Observable
{
public:
	void Add(IObserver* observer);
	void Notify() const;

private:
	std::vector<IObserver*> m_observers;
};
