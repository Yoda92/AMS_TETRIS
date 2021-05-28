#include "graphics.h"
#include "XPT2046/xpt2046.h"
#include "SD/SD_Driver.h"
#include "menu.h"

void Init() {
	InitGraphics();
	InitXPT2046();
	SD_init();
}

int main(void)
{
	Init();
	RunMenu();
	return 0;
}
