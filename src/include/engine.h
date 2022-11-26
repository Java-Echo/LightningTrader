#pragma once
#include <define.h>
#include <lightning.h>
#include <functional>
#include <strategy.h>

class engine
{

private:

	static inline std::function<bool(offset_type offset, direction_type direction)> _filter_function = nullptr;
	static inline bool _filter_callback(offset_type offset, direction_type direction)
	{
		if (_filter_function)
		{
			return _filter_function(offset, direction);
		}
		return true;
	}


public:

	/***
	* ���Ӳ���
	*/
	void add_strategy(straid_t id, std::shared_ptr<strategy> stra);

	/**
	* opt:
	*	���ý����Ż�����ƽ��ת��
	*	���ݵ�ǰ�ĳֲ�������Ż���ʽ������ת��ƽ�� ����תƽ�� ���� ƽ��ת���� ƽ��ת����
	* flag:
	*	�������һ���µ��źţ���ǰδ�ɽ�ί�е��պ���һ����������������Գ壬
	*   �򽫵�ǰ�µ��ź�ת�ɶԳ嵥�ĳ����źţ�ͬʱ������ǰ����
	*/
	void set_trading_optimize(uint32_t max_position, trading_optimal opt = TO_INVALID, bool flag = false);


	/*
	* ���ý��׹�����
	*/
	void set_trading_filter(std::function<bool(offset_type offset, direction_type direction)> callback);

	/**
	* ��ȡ��ǰ�����յĶ���ͳ��
	*	�罻���ջᱻ���
	*/
	const order_statistic& get_order_statistic()const;

protected:

	ltobj _lt;

	std::unique_ptr<class strategy_manager> _strategy_manager ;
};


