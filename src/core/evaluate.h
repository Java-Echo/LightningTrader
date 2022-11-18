#pragma once
#include "context.h"

class evaluate : public context
{

private:
	
	class simulator * _simulator;

public:
	evaluate();
	virtual ~evaluate();
public:

	bool init_from_file(const std::string& config_path);

	double get_money();

	void play(uint32_t tradeing_day);

protected:
	
	virtual trader_api* get_trader() override;

	virtual market_api* get_market() override;

	virtual void update() override;

	virtual void add_handle(std::function<void(event_type, const std::vector<std::any>&)> handle) override;
};