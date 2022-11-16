#pragma once
#include "strategy.h"

class hft_1_strategy : public strategy
{
public:
	hft_1_strategy(double open_delta, double close_delta, double lose_delta,int lose_cd_seconds):
		_sell_order(INVALID_ESTID), _buy_order(INVALID_ESTID), _profit_order(INVALID_ESTID), _loss_order(INVALID_ESTID),
		_lose_cd_seconds(lose_cd_seconds), _open_delta(open_delta), _close_delta(close_delta), _lose_delta(lose_delta)
		, _last_lose_time(0)
		{};
	~hft_1_strategy(){};


public:


	/*
	 *	��ʼ���¼�
	 *	����������ֻ��ص�һ��
	 */
	virtual void on_init() override ;

	/*
	 *	tick����
	 */
	virtual void on_tick(const tick_info* tick)  override;


	/*
	 *	�������ջر�
	 *  @is_success	�Ƿ�ɹ�
	 *	@localid	���ض���id
	 */
	virtual void on_entrust(estid_t localid) override;

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



private:

	double _open_delta;

	double _close_delta;

	double _lose_delta;

	int _lose_cd_seconds ;

	estid_t _sell_order ;

	estid_t _buy_order ;

	estid_t _profit_order;

	estid_t _loss_order;

	tick_info _last_tick;

	//���һ��ֹ��ʱ�䣬����ֹ��cd��
	time_t _last_lose_time;

	time_t _coming_to_close ;
};

