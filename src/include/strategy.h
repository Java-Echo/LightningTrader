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
	void init(const ltobj& lt);

private:


	static inline strategy* _self ;
	static inline void _tick_callback(const tick_info* tick)
	{
		if(_self)
		{
			_self->on_tick(tick);
		}
	}

	static inline void _entrust_callback(estid_t localid) 
	{
		if (_self)
		{
			_self->on_entrust(localid);
		}
	};

	static inline void _deal_callback(estid_t localid, uint32_t deal_volume, uint32_t total_volume)
	{
		if(_self)
		{
			_self->on_deal(localid, deal_volume, total_volume);
		}
	}

	static inline void _trade_callback(estid_t localid, code_t	code, offset_type offset, direction_type direction, double_t price, uint32_t volume) 
	{
		if(_self)
		{
			_self->on_trade(localid, code, offset, direction, price, volume);
		}
	}


	static inline void _cancel_callback(estid_t localid, code_t	code, offset_type offset, direction_type direction, double_t price, uint32_t cancel_volume, uint32_t total_volume) 
	{
		if (_self)
		{
			_self->on_cancel(localid, code, offset, direction, price, cancel_volume, total_volume);
		}
	}

	static inline std::map<estid_t, std::function<bool(const tick_info*)>> _condition_function ;
	static inline bool _condition_callback(estid_t localid,const tick_info* tick)
	{
		auto it = _condition_function.find(localid);
		if(it == _condition_function.end())
		{
			return false;
		}
		return it->second(tick);
	}

	
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


