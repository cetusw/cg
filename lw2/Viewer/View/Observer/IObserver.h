#pragma once

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void OnModelChanged() = 0;
};
