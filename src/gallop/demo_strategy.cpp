#include "demo_strategy.h"

void demo_strategy::on_init()
{
	subscribe(_code);
}

void demo_strategy::on_tick(const tick_info& tick)
{
	_last_tick = tick;
	LOG_DEBUG("on_tick time : %d tick : %d\n", tick.time,tick.tick);
	//һ�ֻ�û�н����꣬���ܿ�����һ��
	if (INVALID_ESTID != _short_order || INVALID_ESTID != _long_order)
	{
		return ;
	}
	//������ͣ����
	if(tick.buy_price()<tick.low_limit)
	{
		return ;
	}
	//������ͣҲ����
	if (tick.sell_price() > tick.high_limit)
	{
		return;
	}
	if(tick.sell_price() - tick.buy_price()<_offset)
	{
		return;
	}
	// ͬʱ�ҳ�����������Ϊ�����˿�ƽ��ת�����Բ���Ҫ����ƽ�����⣬ֻ��Ҫ���Կ��֣�
	_long_order = buy_for_open(tick.id, 1, tick.buy_price());
	_short_order = sell_for_open(tick.id, 1, tick.sell_price());

}



void demo_strategy::on_entrust(const order_info& order)
{
	//
	double_t order_price = order.price ;
	set_cancel_condition(order.est_id, [this, order_price](const tick_info& tick)->bool {

		if (order_price != tick.buy_price()&& order_price != tick.sell_price())
		{
			return true;
		}
		return false;
	});
	LOG_INFO("on_entrust tick : %llu\n", order.est_id);
}

void demo_strategy::on_trade(estid_t localid, const code_t& code, offset_type offset, direction_type direction, double_t price, uint32_t volume)
{
	//�ɽ��Ժ�ǵð�_long_order��_short_order���ó�NULL�����ſ��Խ�����һ��
	if(localid == _long_order)
	{
		_long_order = INVALID_ESTID;
	}
	if(localid == _short_order)
	{
		_short_order = INVALID_ESTID;
	}
	
}

void demo_strategy::on_cancel(estid_t localid, const code_t& code, offset_type offset, direction_type direction, double_t price, uint32_t cancel_volume, uint32_t total_volume)
{
	LOG_INFO("on_cancel tick : %llu\n", localid);
	if (localid == _long_order)
	{
		_long_order = place_order(offset, direction, code, cancel_volume, _last_tick.buy_price());
	}
	if (localid == _short_order)
	{
		_short_order = place_order(offset, direction, code, cancel_volume, _last_tick.sell_price());
	}
}

void demo_strategy::on_error(error_type type,estid_t localid, const uint32_t error)
{
	LOG_ERROR("on_error tick : %llu %u\n", localid , error);
	if(type != ET_ORDER_MATCH)
	{
		return ;
	}
	if (localid == _long_order)
	{
		_long_order = INVALID_ESTID;
	}
	if (localid == _short_order)
	{
		_short_order = INVALID_ESTID;
	}
}
