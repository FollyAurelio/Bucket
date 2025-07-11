#include <iostream>
#include "gfx/window.h"
#include <ft2build.h>
#include FT_FREETYPE_H

int main()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}	
	FT_Face face;
	if (FT_New_Face(ft, "res/fonts/JetBrainsMono-Regular.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	Window window;
	window.loop();
	window.destroy();
	return 0;

}
