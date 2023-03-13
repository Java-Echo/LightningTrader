#pragma once
#include "strategy.h"
#include <random>



class emg_1_strategy : public strategy
{

	struct persist_data
	{
		uint32_t trading_day;
		estid_t sell_order;
		estid_t buy_order;

		persist_data() :
			trading_day(0x0U),
			sell_order(INVALID_ESTID),
			buy_order(INVALID_ESTID)
		{}
	};
public:
	
	emg_1_strategy(const code_t& code, uint32_t open_once, double open_delta,int32_t yestoday_multiple, int32_t yestoday_threshold, double_t yestoday_growth, int32_t random_offset):
		strategy(),
		_code(code),
		_open_once(open_once),
		_open_delta(open_delta),
		_yestoday_multiple(yestoday_multiple),
		_yestoday_threshold(yestoday_threshold),
		_yestoday_growth(yestoday_growth),
		_order_data(nullptr),
		_coming_to_close(0),
		_random(0, random_offset)
		{
		};


	~emg_1_strategy()
	{
		_order_data = nullptr;
	};


public:


	/*
	 *	��ʼ���¼�
	 *	����������ֻ��ص�һ��
	 */
	virtual void on_init() override ;

	/*
	*	�����ճ�ʼ�����
	*/
	virtual void on_ready() override;

	/*
	 *	tick����
	 */
	virtual void on_tick(const tick_info& tick, const deal_info& deal)  override;


	/*
	 *	�������ջر�
	 *  @is_success	�Ƿ�ɹ�
	 *	@order	���ض���
	 */
	virtual void on_entrust(const order_info& order) override;

	/*
	 *	�ɽ��ر�
	 *
	 *	@localid	���ض���id
	 */
	virtual void on_trade(estid_t localid, const code_t& code, offset_type offset, direction_type direction, double_t price, uint32_t volume)  override;


	/*
	 *	����
	 *	@localid	���ض���id
	 */
	virtual void on_cancel(estid_t localid, const code_t& code, offset_type offset, direction_type directionv, double_t price, uint32_t cancel_volume, uint32_t total_volume)  override;

	/*
	 *	����
	 *	@localid	���ض���id
	 *	@error �������
	 */
	virtual void on_error(error_type type,estid_t localid, const uint32_t error) override;
	
	/*
	 *	����
	 */
	virtual void on_destory()override;

private:
	
	code_t _code ;

	double _open_delta;

	uint32_t _open_once;

	uint32_t _yestoday_multiple;

	uint32_t _yestoday_threshold;

	double_t _yestoday_growth;

	tick_info _last_tick;

	time_t _coming_to_close;

	persist_data* _order_data;

	std::default_random_engine _random_engine;

	std::uniform_int_distribution<int> _random;
};

