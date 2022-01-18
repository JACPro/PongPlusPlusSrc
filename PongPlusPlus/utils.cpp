typedef unsigned char u8;
typedef signed char s8; 
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef long long u64;
typedef signed long long s64;

#define global_variable static
#define internal static

int clamp(int value, int min, int max)
{
	if (value > max) return max;
	if (value < min) return min;
	return value;
}
