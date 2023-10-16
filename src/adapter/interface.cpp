﻿#include <interface.h>
#include "market/ctp_market.h"

#include "trader/ctp_trader.h"

actual_market* create_actual_market(const std::shared_ptr<std::unordered_map<std::string, std::string>>& id_excg_map,const params& config)
{
	auto market_type = config.get<std::string>("market");
	if (market_type == "ctp")
	{
		return new ctp_market(id_excg_map, config);
	}
	return nullptr;
}

void destory_actual_market(actual_market*& api)
{
	if (nullptr != api)
	{
		delete api;
		api = nullptr;
	}
}
actual_trader* create_actual_trader(const std::shared_ptr<std::unordered_map<std::string, std::string>>& id_excg_map, const params& config)
{
	auto trader_type = config.get<std::string>("trader");
	if (trader_type == "ctp")
	{
		return new ctp_trader(id_excg_map, config);
	}
	return nullptr;
}

void destory_actual_trader(actual_trader*& api)
{
	if (nullptr != api)
	{
		delete api;
		api = nullptr;
	}
}