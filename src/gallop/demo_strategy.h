#pragma once
#include "strategy.h"
#include <list>
/*
	����ԭ��
	����һ�����в��ԣ�����ԭ���������һ�����룬��һ��۸�������
	���۸�䶯�����Լ��ļ۸�����һ�۸������һ�۸�ʱ��ִ�г������������µ�����֤�Լ��ı���ά������һ����һλ��
	����һ��һ�ֱ�ɽ��Ժ�ִ����һ�ֲ���
	���շ�����
	�˲��Է������ڼ۸񵥱����飬�ᵼ�²��Ͽ��𣬽������µ��ͳ�����������
	ʵ��˼·
	1�����ڽ������г����������ƣ����Կ���ͨ��ltpp�Ĺ�������������
	2��Ϊ��ʹ�߼���ü򵥣�����ͨ��ltpp��ƽ��ת���ܣ�������ת��ƽ�֣�ʹ���ǿ��Բ���עƽ�����⣬������ֻ��Ҫʵ�ֿ��ջ��߿���
	3���۸�仯�������ǵĶ���������һ��һλ��ʱ��ͨ��set_cancel_condition���г��������ҳ����������µ�

*/




class demo_strategy : public strategy
{

public:

	demo_strategy() :
		_offset(1),
		_short_order(INVALID_ESTID),
		_long_order(INVALID_ESTID)
	{};

	demo_strategy(const code_t& code,uint32_t offset):
	_code(code),
	_offset(offset),
	_short_order(INVALID_ESTID), 
	_long_order(INVALID_ESTID)
	{};
	
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
	virtual void on_error(estid_t localid, const uint32_t error)override;


private:

	tick_info _last_tick ;

	uint32_t _offset ;

	code_t _code ;

	// �ղֶ���
	estid_t _short_order ;

	// ��ֶ���
	estid_t _long_order ;

	
};

