#include "Observable.h"

void Observable::Add(IObserver* observer)
{
	m_observers.push_back(observer);
}

void Observable::Notify() const
{
	for (const auto observer : m_observers)
	{
		observer->OnModelChanged();
	}
}