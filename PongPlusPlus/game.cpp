#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

const float acceleration_speed = 1000, ai_acceleration_speed = 700;
const float friction = 10.f;
float player_1_p, player_1_dp, player_2_p, player_2_dp;
float player_half_size_x = 2.5, player_half_size_y = 12;

float arena_half_size_x = 85, arena_half_size_y = 45;

float ball_p_x, ball_p_y, ball_dp_x = 140.f, ball_dp_y;
float ball_half_size = 1;

int player_1_score = 0, player_2_score = 0;

internal void
SimulatePlayer(float *player_p, float *player_dp, float player_ddp, float delta_time)
{
	//Friction
	player_ddp -= *player_dp * friction;

	*player_p = *player_p + *player_dp * delta_time + player_ddp * delta_time * delta_time * .5f;
	*player_dp = *player_dp + player_ddp * delta_time;

	if (*player_p + player_half_size_y > arena_half_size_y)
	{
		*player_p = arena_half_size_y - player_half_size_y;
		*player_dp = 0.f;
	}
	else if (*player_p - player_half_size_y < -arena_half_size_y)
	{
		*player_p = -arena_half_size_y + player_half_size_y;
	}
}

internal void
ScoreGoal(PLAYERS player)
{
	ball_p_x = 0, ball_p_y = 0;
	ball_dp_y = 0;
	if (player == PLAYER_1)
	{
		ball_dp_x = 100.f;
		player_1_score++;
	}
	else
	{
		ball_dp_x = -100.f;
		player_2_score++;
	}

	//Reset paddles
	player_1_p = 0;
	player_2_p = 0;
}

internal bool
AABB_VS_AABB(float p1x, float p1y, float hs1x, float hs1y,
	float p2x, float p2y, float hs2x, float hs2y)
{
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y + hs1y> p2y - hs2y &&
		p1y - hs1y < p2y + hs2y);
}

internal void
SimulateGame(Input* input, float delta_time)
{
	ClearScreen(0x25783b);

	//Process input
	float player_1_ddp = 0.f, player_2_ddp = 0.f; 
#if 0
	if (is_down(BUTTON_UP)) player_1_ddp += acceleration_speed;
	if (is_down(BUTTON_DOWN)) player_1_ddp -= acceleration_speed;
#else
	//if (ball_p_y > player_1_p + 2.f) player_1_ddp += ai_acceleration_speed;
	//if (ball_p_y < player_1_p - 2.f) player_1_ddp -= ai_acceleration_speed;
	player_1_ddp = clamp((ball_p_y - player_1_p) * 150, -ai_acceleration_speed, ai_acceleration_speed);

#endif
	if (is_down(BUTTON_W)) player_2_ddp += acceleration_speed;
	if (is_down(BUTTON_S)) player_2_ddp -= acceleration_speed;

	SimulatePlayer(&player_1_p, &player_1_dp, player_1_ddp, delta_time);
	SimulatePlayer(&player_2_p, &player_2_dp, player_2_ddp, delta_time);

	//Simulate Ball
	{
		ball_p_x += ball_dp_x * delta_time;
		ball_p_y += ball_dp_y * delta_time;

		//Player Collisions
		if (AABB_VS_AABB(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 80, player_2_p, player_half_size_x, player_half_size_y))
		{
			ball_p_x = 80 - player_half_size_x - ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = player_2_dp;
		}
		else if (AABB_VS_AABB(ball_p_x, ball_p_y, ball_half_size, ball_half_size, -80, player_1_p, player_half_size_x, player_half_size_y))
		{
			ball_p_x = -80 + player_half_size_x + ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = player_1_dp;
		}

		//Ceiling & Floor Collisions
		if (ball_p_y + ball_half_size > arena_half_size_y)
		{
			ball_dp_y *= -1;
			ball_p_y = arena_half_size_y - ball_half_size;
		}
		else if (ball_p_y - ball_half_size < -arena_half_size_y)
		{
			ball_dp_y *= -1;
			ball_p_y = -arena_half_size_y + ball_half_size;
		}

		//Left and Right Wall Collisions
		if (ball_p_x + ball_half_size > arena_half_size_x)
		{
			ScoreGoal(PLAYER_1);
		}
		else if (ball_p_x - ball_half_size < -arena_half_size_x)
		{
			ScoreGoal(PLAYER_2);
		}
	}

	
	//Rendering
	DrawRect(0, 0, arena_half_size_x, arena_half_size_y, 0x2659471);

	DrawRect(-80, player_1_p, player_half_size_x, player_half_size_y, 0x25783b);
	DrawRect(80, player_2_p, player_half_size_x, player_half_size_y, 0x25783b);
	DrawRect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0x25783b);
	
	DrawNumber(player_1_score, -10, 40, 1.f, 0xabe9ff);
	DrawNumber(player_2_score, 10, 40, 1.f, 0xabe9ff);
}