#pragma once
#include "strategy.h"
#include <list>

class demo_strategy : public strategy
{
public:
	demo_strategy(int lose_offset,int open_delta):_lose_offset(lose_offset), _open_delta(open_delta), _highest_price(0), _lowest_price(0) {};
	~demo_strategy(){};


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

private:

	bool check_lose(const tick_info* tick);

private:

	int _lose_offset;

	int _open_delta;

	estid_t _sell_order ;

	estid_t _buy_order ;

	double _highest_price; //ֹ���
	double _lowest_price; //ֹ���

	std::list<double_t> _history_list ;

};

