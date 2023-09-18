#pragma once
enum ObstructSelectNo
{
	EMPTY_PRESS,
	EMPTY_RESULT,

	OBSTRUCT_PRESS,
	OBSTRUCT_RESULT,

	POWER_UP_PRESS,
	POWER_UP_RESULT,

	ERASE_PRESS,
	ERASE_RESULT,

	HRAVY_PRESS,
	HRAVY_RESULT,

	NORMAL_PRESS,
	NORMAL_RESULT
};

struct ObstructSelect
{
	// ëIëÇµÇΩî‘çÜ
	ObstructSelectNo no;
};