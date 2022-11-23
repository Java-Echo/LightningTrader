#include "demo_strategy.h"

void demo_strategy::on_init()
{
	// �������ÿ�ƽ��ת������->ƽ�֣�����->ƽ�գ�����->ƽ�ࣩ
	set_trading_optimize(16, TO_OPEN_TO_CLOSE,false);
	subscribe({"SHFF.rb2307"});
	set_trading_filter([this](offset_type offset, direction_type direction)->bool{
		const auto & statius = get_order_statistic();
		//����ÿ���µ���������480�Ͳ��ٿ����µ��ˣ����ⴥ������������
		if(statius.entrust_amount > 480)
		{	
			return false ;
		}
		return true ;
	});
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
	// ͬʱ�ҳ�����������Ϊ�����˿�ƽ��ת�����Բ���Ҫ����ƽ�����⣬ֻ��Ҫ���Կ��֣�
	_long_order = buy_for_open(tick.id, 8, tick.buy_price());
	_short_order = sell_for_open(tick.id, 8, tick.sell_price());

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
