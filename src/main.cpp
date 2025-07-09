#include <iostream>
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/vbo.h"
#include "gfx/vao.h"
#include "gfx/texture.h"
#include "gfx/gmath.h"
#include "gfx/renderer.h"
#include "data/loader.h"
#include "gfx/window.h"

int main()
{
	Window window;
	window.loop();
	window.destroy();
	return 0;

}
