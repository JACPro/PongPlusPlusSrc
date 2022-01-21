#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;

float base_move_speed = 20.f;
float curr_move_speed = base_move_speed;
float sprint_modifier = 2.5f;

internal void
SimulateGame(Input* input, float delta_time)
{
	ClearScreen(0x7de1ff);

	curr_move_speed = (is_down(BUTTON_SHIFT)) ? base_move_speed * sprint_modifier : base_move_speed;

	//Middle
	if (is_down(BUTTON_UP))
	{ 
		//Account for increased diagonal speed by multiplying by root of 2
		if (is_down(BUTTON_RIGHT) != is_down(BUTTON_LEFT))
			curr_move_speed /= 1.414214f;
		player_pos_y += curr_move_speed * delta_time;
	}
	if (is_down(BUTTON_DOWN))
	{
		if (is_down(BUTTON_RIGHT) != is_down(BUTTON_LEFT))
			curr_move_speed /= 1.414214f;
		player_pos_y -= curr_move_speed * delta_time;
	}
	if (is_down(BUTTON_RIGHT)) 
		player_pos_x += curr_move_speed * delta_time;
	if (is_down(BUTTON_LEFT)) 
		player_pos_x -= curr_move_speed * delta_time;

	DrawRect(player_pos_x, player_pos_y, 10, 10, 0xfc6358);
	//Bottom left
	DrawRect(-40, -40, 5, 5, 0xfc6358);
	//Top left
	DrawRect(-40, 40, 7, 7, 0xfc6358);
	//Top right
	DrawRect(40, 40, 5, 5, 0xfc6358);
	//Bottom right
	DrawRect(40, -40, 7, 7, 0xfc6358);
}