#include "Graphics/Util/GLFont.h"
#include "Graphics/Util/FontInformation.h"
#include "Graphics/Util/GLTexture.h"
#include "Graphics/Util/GLWindow.h"
#include "Resources/ResourceManager.h"
#include <GL/gl.h>

#define WIDTH  500
#define HEIGHT 500

GLFont *font;
FontInformation *fontInfo;
//GLTexture texture;
void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	font->render("Testing 1 2 3 4 5 6");
	glFlush();
}

int main(int argc, char** argv) {
	glfwInit();
	ResourceManager::get()->initialize(10);
	fontInfo = ResourceManager::get()->find<FontInformation>("font.png");
	font = new GLFont(fontInfo);
	font->setSize(16.0);

	GLWindow window("Test", WIDTH, HEIGHT);

	window.bindContext();
	reshape(WIDTH, HEIGHT);
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!window.isClosing()) {
		render();
		window.swapBuffers();
	}

	window.destroy();

	delete font;
	ResourceManager::get()->destroy(fontInfo);
	glfwTerminate();
	return 0;
}
