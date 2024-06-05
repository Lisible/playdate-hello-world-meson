#include "pd_api.h"

static int update(void* userdata);

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	(void)arg;

	if(event == kEventInit)
	{
		pd->system->setUpdateCallback(update, pd);
	}
	
	return 0;
}

#define TEXT_WIDTH 86
#define TEXT_HEIGHT 16

int x = (400-TEXT_WIDTH)/2;
int y = (240-TEXT_HEIGHT)/2;

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;
	pd->graphics->clear(kColorWhite);
	pd->graphics->drawText("Hello, world!", strlen("Hello, world!"), kASCIIEncoding, x, y);
	return 1;
}


