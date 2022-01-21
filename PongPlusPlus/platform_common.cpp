struct Button_State
{
	bool is_down;
	bool changed;
};

enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_W,
	BUTTON_S,

	BUTTON_COUNT
};

enum PLAYERS
{
	PLAYER_1,
	PLAYER_2
};

struct Input
{
	Button_State buttons[BUTTON_COUNT];
};