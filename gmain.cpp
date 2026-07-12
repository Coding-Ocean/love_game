#include "framework.h"

void gmain()
{
	window("love", 1920, 1080, full);

	while (!quit())
	{
		begin();

		printInfo();
		end();
	}
}
