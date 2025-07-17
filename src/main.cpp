#include <iostream>
#include "gfx/window.h"
#include <ft2build.h>
#include FT_FREETYPE_H

int main()
{
	Window window;
	window.loop();
	window.destroy();
	return 0;

}
