struct Button_State
{
	bool is_down;
	bool changed;
};

struct Colour_Scheme
{
	u32 arena;
	u32 players;
	u32 text;
};

Colour_Scheme col_scheme_arr [3] = { 
	0xee7878,0xc82828,0x82EE57,
	0x7d95dd,0x1f4bcd,0xdf2f2f,
	0x74b385,0x25783b,0x00ffd8 
};

enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_W,
	BUTTON_S,
	BUTTON_ENTER,
	BUTTON_ESCAPE,

	BUTTON_COUNT,
};

enum Players
{
	PLAYER_1,
	PLAYER_2
};

enum GameMode
{
	MAIN_MENU,
	PLAYER_SELECTION,
	OPTIONS,
	GAME
};

enum NumPlayers
{
	ONEPLAYER,
	TWOPLAYER
};
struct Input
{
	Button_State buttons[BUTTON_COUNT];
};