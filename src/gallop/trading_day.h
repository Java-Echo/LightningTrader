
std::vector<uint32_t> trading_day_2210 = {
	//2210
	
	20220801,
	20220802,
	20220803,
	20220804,
	20220805,
	20220808,
	20220809,
	20220810,
	20220811,
	20220812,
	20220815,
	20220816,
	20220817,
	20220818,
	20220819,
	20220822,
	20220823,
	20220824,
	20220825,
	20220826,
	20220829,
	20220830,
	20220831
};
std::vector<uint32_t> trading_day_2301 = {
	//2301

	20220901,
	20220902,
	20220905,
	20220906,
	20220907,
	20220908,
	20220909,
	20220913,
	20220914,
	20220915,
	20220916,
	20220919,
	20220920,
	20220921,
	20220922,
	20220923,
	20220926,
	20220927,
	20220928,
	20220929,
	20220930,

	20221010,
	20221011,
	20221012,
	20221013,
	20221014,
	20221017,
	20221018,
	20221019,
	20221020,
	20221021,
	20221024,
	20221025,
	20221026,
	20221027,
	20221028,
	20221031,

	20221101,
	20221102,
	20221103,
	20221104,
	20221107,
	20221108,
	20221109,
	20221110,
	20221111,
	20221114,
	20221115,
	20221116,
	20221117,
	20221118,
	20221121,
	20221122,
	20221123,
	20221124,
	20221125,
	20221128,
	20221129,
	20221130
};
std::vector<uint32_t> trading_day_2305 = {
	//2305
	20221201,
	20221202,
	20221205,
	20221206,
	20221207,
	20221208,
	20221209,
	20221212,
	20221213,
	20221214,
	20221215,
	20221216,
	20221219,
	20221220,
	20221221,
	20221222,
	20221223,
	20221226,
	20221227,
	20221228,
	20221229,
	20221230

};


std::map<uint32_t, std::vector<uint32_t>> trading_index = {{1,trading_day_2210},{2,trading_day_2301},{3,trading_day_2305}};

std::pair<const char*, transfer_info> get_rb_frist(uint32_t index)
{
	switch(index)
	{
		case 1:
			return std::make_pair("SHFE.rb2210", default_transfer);
			break;
		case 2:
			return std::make_pair("SHFE.rb2301", transfer_info("SHFE.rb2210",183));
			break;
		case 3:
			return std::make_pair("SHFE.rb2305", transfer_info("SHFE.rb2301", 13));
			break;
	}
	return std::make_pair("", default_transfer);
}
std::pair<const char*, transfer_info> get_rb_second(uint32_t index)
{
	switch (index)
	{
	case 1:
		return std::make_pair("SHFE.rb2301", default_transfer);
		break;
	case 2:
		return std::make_pair("SHFE.rb2302", transfer_info("SHFE.rb2301", 57));
		break;
	case 3:
		return std::make_pair("SHFE.rb2303", transfer_info("SHFE.rb2302", 22));
		break;
	}
	return std::make_pair("", default_transfer);
}