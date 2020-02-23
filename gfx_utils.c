#include "gfx_utils.h"


int itoc(char *buffer, int maxsize, int value)
{
	int size = 0;
	for(int i = 0; i < maxsize; i++)
	{
		if(value == 0)
		{
			break;
		}
		
		buffer[maxsize - i - 1] = value % 10 + 0x30;
		value /= 10;
		size++;
	}
	if(size == 0)
	{
        buffer[maxsize - 1] = 0x30;
		size++;
	}
    return size;
}

int ftoc(char *buffer, int maxsize, float value, unsigned char points)
{
    int size = 0;
    for(int i = 0; i < points; i++)
    {
        value *= 10;
    }
    int v = value;
    int is_zero = v ? 0 : 1;
    int is_point = 0;
    int i;
    for(i = 0; i < maxsize; i++)
    {
        if(v == 0 && is_zero == 0)
        {
            break;
        }

        if(i == points)
        {
            buffer[maxsize - i - 1] = '.';
            size++;
            is_point = 1;
            is_zero = 0;
            continue;
        }
        is_point = 0;

        buffer[maxsize - i - 1] = v % 10 + 0x30;
        v /= 10;
        size++;
    }

    if(is_point && i < maxsize)
    {
        buffer[maxsize - i - 1] = '0';
        size++;
    }

    return size;
}
