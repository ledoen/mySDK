#include "commen_headers.h"
#include "mybsp_sysinit.h"
#include "mybsp_gpit.h"

int main(void)
{
	system_Init();
	epit1_init(66, 2000000);
	
}