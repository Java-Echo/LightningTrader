#include <data_types.hpp>
#include "csv_tick_loader.h"
#include <rapidcsv.h>
#include <time_utils.hpp>

bool csv_tick_loader::init(const std::string& root_path)
{
	_root_path = root_path;
	return true ;
}


void csv_tick_loader::load_tick(std::vector<tick_info>& result ,code_t code, uint32_t trade_day)
{
	char buffer[128];
	sprintf_s(buffer, 128, _root_path.c_str(), code.get_id(), trade_day);
	rapidcsv::Document doc(buffer, rapidcsv::LabelParams(0, -1));
	for(size_t i = 0;i < doc.GetRowCount();i++)
	{
		const auto& id = doc.GetCell<std::string>("��Լ����", i);
		if(id != code.get_id())
		{
			continue;
		}
		tick_info tick ;
		tick.id = code;
		const std::string& date_str = doc.GetCell<std::string>("ҵ������",i);
		const std::string& time_str = doc.GetCell<std::string>("����޸�ʱ��",i);
		tick.time = make_time(date_str.c_str(), time_str.c_str());
		tick.tick = doc.GetCell<uint32_t>("����޸ĺ���",i);
		tick.price = doc.GetCell<double_t>("���¼�",i);
		tick.open = doc.GetCell<double_t>("����",i);
		tick.high = doc.GetCell<double_t>("��߼�", i);
		tick.low = doc.GetCell<double_t>("��ͼ�", i);
		tick.standard = doc.GetCell<double_t>("�ϴν����", i);
		tick.volume = doc.GetCell<uint32_t>("����", i);
		tick.trading_day = doc.GetCell<uint32_t>("������", i);
	
		tick.buy_order[0] = std::make_pair(doc.GetCell<double_t>("�����һ", i), doc.GetCell<uint32_t>("������һ", i));
		tick.buy_order[1] = std::make_pair(doc.GetCell<double_t>("����۶�", i), doc.GetCell<uint32_t>("��������", i));
		tick.buy_order[2] = std::make_pair(doc.GetCell<double_t>("�������", i), doc.GetCell<uint32_t>("��������", i));
		tick.buy_order[3] = std::make_pair(doc.GetCell<double_t>("�������", i), doc.GetCell<uint32_t>("��������", i));
		tick.buy_order[4] = std::make_pair(doc.GetCell<double_t>("�������", i), doc.GetCell<uint32_t>("��������", i));
		
		tick.sell_order[0] = std::make_pair(doc.GetCell<double_t>("������һ", i), doc.GetCell<uint32_t>("������һ", i));
		tick.sell_order[1] = std::make_pair(doc.GetCell<double_t>("�����۶�", i), doc.GetCell<uint32_t>("��������", i));
		tick.sell_order[2] = std::make_pair(doc.GetCell<double_t>("��������", i), doc.GetCell<uint32_t>("��������", i));
		tick.sell_order[3] = std::make_pair(doc.GetCell<double_t>("��������", i), doc.GetCell<uint32_t>("��������", i));
		tick.sell_order[4] = std::make_pair(doc.GetCell<double_t>("��������", i), doc.GetCell<uint32_t>("��������", i));
		result.emplace_back(tick);
	}
}