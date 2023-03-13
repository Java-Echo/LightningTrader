#pragma once
#include "strategy.h"

class hcc_strategy : public strategy
{
public:
	hcc_strategy(code_t code,
	float record_ratio,
	int lose_offset,
	int drag_limit,
	int cancel_seconds
	): _code(code), 
	_record_ratio(record_ratio),
	_lose_offset(lose_offset),
	_drag_limit(drag_limit),
	_cancel_seconds(cancel_seconds),
	long_drag(0), 
	short_drag(0),
	current_volume(0),
	_last_order_time(0), 
	_short_lose_price(.0F),
	_long_lose_price(.0F)
	{}
protected:
	/*
	 *	��ʼ���¼�
	 *	����������ֻ��ص�һ��
	 */
	virtual void on_init() override;

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
	virtual void on_cancel(estid_t localid, const code_t& code, offset_type offset, direction_type direction, double_t price, uint32_t cancel_volume, uint32_t total_volume)  override;


private:

	void on_price_change(const tick_info& tick, bool is_up);
	
private:

	std::pair<double, int> buy_pending_order;
	std::pair<double, int> sell_pending_order;

	float long_drag;
	float short_drag;
	int current_volume;

	estid_t _order_id ;

	time_t _last_order_time ;

	double _long_lose_price ; //ֹ���
	double _short_lose_price; //ֹ���

	code_t _code ;
	float _record_ratio ;
	int _lose_offset ;
	int _drag_limit ;
	int _cancel_seconds;

};

