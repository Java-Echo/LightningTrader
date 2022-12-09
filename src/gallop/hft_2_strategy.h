#pragma once
#include "strategy.h"

class hft_2_strategy : public strategy
{
public:
	
	hft_2_strategy(const code_t& code,double open_delta):
		strategy(),
		_code(code),
		_sell_order(INVALID_ESTID),
		_buy_order(INVALID_ESTID),
		_open_delta(open_delta),
		_history_count(1200),
		_history_ma(0),
		_coming_to_close(0),
		_clear_position(false)
		{};


	~hft_2_strategy(){};


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
	virtual void on_tick(const tick_info& tick)  override;


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


private:

	void add_to_history(double_t price);

private:
	
	code_t _code ;

	double _open_delta;

	estid_t _sell_order ;

	estid_t _buy_order ;

	tick_info _last_tick;

	size_t _history_count ;

	time_t _coming_to_close;

	double_t _history_ma ;

	std::list<double_t> _history_price ;

	bool _clear_position ;
};

