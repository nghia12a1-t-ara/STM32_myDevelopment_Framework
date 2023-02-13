
int u32Result __attribute__((section(".result")));

void CHECK_RESULT(int a, int b)
{
	if (a != b)
	{
		u32Result = 1U;
	}
}
