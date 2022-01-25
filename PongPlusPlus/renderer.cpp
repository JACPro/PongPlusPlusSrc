internal void 
ClearScreen(u32 colour)
{
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel++ = colour;
		}
	}
}

internal void 
DrawRectInPixels(int x0, int y0, int x1, int y1, u32 colour)
{
	x0 = clamp(x0, 0, render_state.width);
	x1 = clamp(x1, 0, render_state.width);
	y0 = clamp(y0, 0, render_state.height);
	y1 = clamp(y1, 0, render_state.height);
	
	for (int y = y0; y < y1; y++)
	{
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = colour;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
DrawRect(float x, float y, float half_size_x, float half_size_y, u32 colour)
{
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//Change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	DrawRectInPixels(x0, y0, x1, y1, colour);
}

internal void
DrawNumber(int number, float x_pos, float y_pos, float size, u32 colour)
{
	float half_size = size * 0.5f;
	bool drawn_first_digit = false;
	while (number || !drawn_first_digit)
	{
		drawn_first_digit = true;

		int digit = number % 10;
		number /= 10;

		switch (digit) {
			case 0: {
				DrawRect(x_pos - size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos, y_pos + size * 2.f, half_size, half_size, colour);
				DrawRect(x_pos, y_pos - size * 2.f, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 1: {
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				x_pos -= size * 2.f;
			} break;

			case 2: {
				DrawRect(x_pos, y_pos + size * 2.f, 1.5f * size, half_size, colour);
				DrawRect(x_pos, y_pos, 1.5f * size, half_size, colour);
				DrawRect(x_pos, y_pos - size * 2.f, 1.5f * size, half_size, colour);
				DrawRect(x_pos + size, y_pos + size, half_size, half_size, colour);
				DrawRect(x_pos - size, y_pos - size, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 3: {
				DrawRect(x_pos - half_size, y_pos + size * 2.f, size, half_size, colour);
				DrawRect(x_pos - half_size, y_pos, size, half_size, colour);
				DrawRect(x_pos - half_size, y_pos - size * 2.f, size, half_size, colour);
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				x_pos -= size * 4.f;
			} break;

			case 4: {
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos - size, y_pos + size, half_size, 1.5f * size, colour);
				DrawRect(x_pos, y_pos, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 5: {
				DrawRect(x_pos, y_pos + size * 2.f, 1.5f * size, half_size, colour);
				DrawRect(x_pos, y_pos, 1.5f * size, half_size, colour);
				DrawRect(x_pos, y_pos - size * 2.f, 1.5f * size, half_size, colour);
				DrawRect(x_pos - size, y_pos + size, half_size, half_size, colour);
				DrawRect(x_pos + size, y_pos - size, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 6: {
				DrawRect(x_pos + half_size, y_pos + size * 2.f, size, half_size, colour);
				DrawRect(x_pos + half_size, y_pos, size, half_size, colour);
				DrawRect(x_pos + half_size, y_pos - size * 2.f, size, half_size, colour);
				DrawRect(x_pos - size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos + size, y_pos - size, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 7: {
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos - half_size, y_pos + size * 2.f, size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 8: {
				DrawRect(x_pos - size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos, y_pos + size * 2.f, half_size, half_size, colour);
				DrawRect(x_pos, y_pos - size * 2.f, half_size, half_size, colour);
				DrawRect(x_pos, y_pos, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;

			case 9: {
				DrawRect(x_pos - half_size, y_pos + size * 2.f, size, half_size, colour);
				DrawRect(x_pos - half_size, y_pos, size, half_size, colour);
				DrawRect(x_pos - half_size, y_pos - size * 2.f, size, half_size, colour);
				DrawRect(x_pos + size, y_pos, half_size, 2.5f * size, colour);
				DrawRect(x_pos - size, y_pos + size, half_size, half_size, colour);
				x_pos -= size * 4.f;
			} break;
		}
	}
}