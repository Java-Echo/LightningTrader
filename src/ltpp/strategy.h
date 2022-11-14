#pragma once
#include <define.h>
#include <data_types.hpp>
#include <lightning.h>
#include <functional>

class strategy
{

public:

	strategy();
	virtual ~strategy();

public:
	
	/*
	*	��ʼ��
	*/
	void init(ltobj lt);
	
	//�ص�����
protected:
	/*
	 *	��ʼ���¼�
	 *	����������ֻ��ص�һ��
	 */
	virtual void on_init() {};

	/*
	 *	tick����
	 */
	virtual void on_tick(const tick_info* tick) {}
	
	/*
	 *	����ʱ�����
	 *  @day	��ǰ������
	 */
	virtual void on_cross_day(uint32_t day) {}
	
	/*
	 *	�������ջر�
	 *  @is_success	�Ƿ�ɹ�
	 *	@localid	���ض���id
	 */
	virtual void on_entrust(estid_t localid) {};

	/*
	 *	�ɽ��ر�
	 *
	 *	@localid	���ض���id
	*/
	virtual void on_deal(estid_t localid,uint32_t deal_volume, uint32_t total_volume) {}

	/*
	 *	�ɽ���ɻر�
	 *
	 *	@localid	���ض���id
	 */
	virtual void on_trade(estid_t localid, code_t	code, offset_type offset, direction_type direction, double_t price, uint32_t volume) {}


	/*
	 *	����
	 *	@localid	���ض���id
	 */
	virtual void on_cancel(estid_t localid, code_t	code, offset_type offset, direction_type direction, double_t price, uint32_t cancel_volume, uint32_t total_volume) {}

	

protected:
	//���ܺ���
	/*
	 *	���൥
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t buy_for_open(code_t code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	ƽ�൥
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t sell_for_close(code_t code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	���յ�
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t sell_for_open(code_t code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	ƽ�յ�
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t buy_for_close(code_t code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	����
	 *	order_id �µ����ص�id
	 */
	void cancel_order(estid_t order_id);

	/** 
	* opt:
	*	���ý����Ż�����ƽ��ת��
	*	���ݵ�ǰ�ĳֲ�������Ż���ʽ������ת��ƽ�� ����תƽ�� ���� ƽ��ת���� ƽ��ת����
	* flag:
	*	�������һ���µ��źţ���ǰδ�ɽ�ί�е��պ���һ����������������Գ壬
	*   �򽫵�ǰ�µ��ź�ת�ɶԳ嵥�ĳ����źţ�ͬʱ������ǰ����
	*/
	void set_trading_optimize(uint32_t max_position, trading_optimal opt = TO_INVALID, bool flag = false);

	/**  
	* ��ȡ��λ��Ϣ
	*/
	const position_info* get_position(code_t code) const;

	/**
	* ��ȡ�˻��ʽ�
	*/
	const account_info* get_account() const;

	/**  
	* ��ȡί�ж���
	**/
	const order_info* get_order(estid_t order_id) const;


	/**
	* ��������
	**/
	void subscribe(code_t code) ;

	/**
	* ȡ����������
	**/
	void unsubscribe(code_t code) ;

	/**
	* ��ȡʱ��
	* 
	*/
	time_t get_last_time() const ;

	/*
	* ���ó�������
	*/
	void set_cancel_condition(estid_t order_id, std::function<bool(const tick_info*)> callback);

private:

	ltobj _lt;

};


