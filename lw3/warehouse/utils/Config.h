#pragma once
#include <chrono>

namespace Config
{
using namespace std::chrono_literals;
constexpr auto SUPPLY_INTERVAL = 500ms;
constexpr auto PURCHASE_INTERVAL = 700ms;
constexpr auto AUDIT_INTERVAL = 2s;

constexpr int MAX_SUPPLY_AMOUNT = 20;
constexpr int MAX_PURCHASE_AMOUNT = 5;
} // namespace Config
