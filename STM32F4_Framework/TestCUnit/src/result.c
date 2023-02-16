
static unsigned int u32Result __attribute__((section(".result")));

void CHECK_RESULT(unsigned int expression, unsigned int expected_value)
{
	if (expression != expected_value)
	{
		u32Result = 2U;
	}
    else
    {
        u32Result = 1U;
    }
}
