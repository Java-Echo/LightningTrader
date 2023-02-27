#pragma once
#include <define.h>
#include <data_types.hpp>
#include <lightning.h>
#include <functional>

typedef untid_t straid_t;

class strategy
{

private:

	straid_t _id;

	class strategy_manager* _manager;

public:

	strategy();
	
	virtual ~strategy();

	/*
	*	��ʼ��
	*/
	void init(straid_t id,class strategy_manager* manager);

	//�ص�����
private:

	/*
	 *	��ʼ���¼�
	 *	����������ֻ��ص�һ��
	 */
	virtual void on_init() {};

public:
	
	/*
	*	�����ճ�ʼ�����
	*/
	virtual void on_ready() {};

	/*
	 *	tick����
	 */
	virtual void on_tick(const tick_info& tick) {}

	
	/*
	 *	�������ջر�
	 *  @is_success	�Ƿ�ɹ�
	 *	@order	���ض���
	 */
	virtual void on_entrust(const order_info& order) {};

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
	virtual void on_trade(estid_t localid, const code_t& code, offset_type offset, direction_type direction, double_t price, uint32_t volume) {}


	/*
	 *	����
	 *	@localid	���ض���id
	 */
	virtual void on_cancel(estid_t localid, const code_t& code, offset_type offset, direction_type direction, double_t price, uint32_t cancel_volume, uint32_t total_volume) {}

	/*
	 *	����
	 *	@localid	���ض���id
	 *	@error �������
	 */
	virtual void on_error(error_type type, estid_t localid, const uint32_t error) {}


protected:
	//���ܺ���
	/*
	 *	���൥
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t buy_for_open(const code_t& code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	ƽ�൥
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t sell_for_close(const code_t& code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	���յ�
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t sell_for_open(const code_t& code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	 *	ƽ�յ�
	 *	code �ڻ����� SHFF.rb2301
	 *  price �����0��ʾ�м۵���������ʾ�ּ۵�
	 *  flag Ĭ��Ϊ������
	 *	@localid	���ض���id
	 */
	estid_t buy_for_close(const code_t& code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);

	/*
	*	�µ���
	*	order_id �µ����ص�id
	*/
	estid_t place_order(offset_type offset, direction_type direction, const code_t& code, uint32_t count, double_t price = 0, order_flag flag = OF_NOR);
	/*
	 *	����
	 *	order_id �µ����ص�id
	 */
	void cancel_order(estid_t order_id);

	/**  
	* ��ȡ��λ��Ϣ
	*/
	const position_info& get_position(const code_t& code) const;

	/**
	* ��ȡ�˻��ʽ�
	*/
	const account_info& get_account() const;

	/**  
	* ��ȡί�ж���
	**/
	const order_info& get_order(estid_t order_id) const;


	/**
	* ��������
	**/
	void subscribe(const code_t& code) ;

	/**
	* ȡ����������
	**/
	void unsubscribe(const code_t& code) ;

	/**
	* ��ȡʱ��
	* 
	*/
	time_t get_last_time() const ;

	/**
	* ʹ���Զ��彻��ͨ��
	*/
	void use_custom_chain(trading_optimal opt, bool flag);

	/*
	* ���ó�������(����trueʱ����)
	*/
	void set_cancel_condition(estid_t order_id, std::function<bool(const tick_info&)> callback);


	/**
	* ��ȡ���һ���µ�ʱ��
	*	�罻���շ���0
	*/
	time_t last_order_time();



	inline straid_t get_id()
	{
		return _id;
	}

	/**
	* ��ȡ�û����ݣ�ֱ��д��ᱻ���浽�����ڴ���
	*	ע��������ʱ��id���ܸı�
	*	ID���ֵ��localdb�����е�userdata_block��Ӧ
	*/

	void* get_username(size_t size);

	/**
	* ��ȡ������
	*/
	uint32_t get_trading_day()const;

	/**
	*	�Ƿ�׼������
	*/
	bool is_trading_ready()const;

};


