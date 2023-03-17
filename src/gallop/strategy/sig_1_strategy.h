#pragma once
#include "strategy.h"
#include <random>
#include "signal/signal.h"
#include "pms/pms.h"


class sig_1_strategy : public strategy
{
	struct persist_data
	{
		uint32_t trading_day;

		estid_t order_estid;

		persist_data() :
			trading_day(0x0U),
			order_estid(INVALID_ESTID)
		{
		}
	};

public:
	
	sig_1_strategy(const param& p):
		strategy(),
		_code(p.get<const char*>("code")),
		_open_once(p.get<uint32_t>("open_once")),
		_beta(p.get<double_t>("beta")),
		_prb_delta(p.get<uint32_t>("prb_delta")),
		_expire(p.get<const char*>("expire")),
		_current_prb_st(ST_INVALID),
		_expire_prb_st(ST_INVALID)
	{
		};


	~sig_1_strategy(){};


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

	code_t _expire ;

	uint32_t _prb_delta ;

	uint32_t _open_once ;

	double_t _beta ;

	std::vector<std::shared_ptr<signal>> _current_signals;

	std::vector<std::shared_ptr<signal>> _expire_signals;

	time_t _coming_to_close;

	signal_type _current_prb_st;

	signal_type _expire_prb_st;

	persist_data* _order_data;

	std::shared_ptr<pms> _current_pcm;
	std::shared_ptr<pms> _expire_pcm;

};

