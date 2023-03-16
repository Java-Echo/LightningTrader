#pragma once
#include <define.h>
#include <lightning.h>
#include <strategy.h>


class engine
{

private:

	static inline filter_function _filter_function = nullptr;
	static inline bool _filter_callback(const code_t& code, offset_type offset, direction_type direction,uint32_t count, double_t price, order_flag flag)
	{
		if (_filter_function)
		{
			return _filter_function(code, offset, direction, count, price, flag);
		}
		return true;
	}

protected:
	
	/***
	* ע�����
	*/
	void regist_strategy(straid_t id, std::shared_ptr<strategy> stra);

	/***
	* ȡ��ע�����
	*/
	void unregist_strategy(straid_t id);

public:

	/*
	* ���ý��׹�����
	*/
	void set_trading_filter(filter_function callback);

	/**
	* ��ȡ��ǰ�����յĶ���ͳ��
	*	�罻���ջᱻ���
	*/
	const order_statistic& get_order_statistic()const;

	/**
	* ��ȡ��λ��Ϣ
	*/
	const position_info& get_position(const code_t& code) const;


protected:

	ltobj _lt;

	std::unique_ptr<class strategy_manager> _strategy_manager ;
};


