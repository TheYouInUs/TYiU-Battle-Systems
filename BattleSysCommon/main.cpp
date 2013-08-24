#include "Graphics/Util/GLFont.h"
#include "Graphics/Util/FontInformation.h"
#include "Graphics/Util/GLWindow.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include <GL/gl.h>
#include "Graphics/GUI/GUIContainer.h"
#include "Graphics/GUI/GUIWidget.h"
#include <GLFW/glfw3.h>

#define WIDTH  500
#define HEIGHT 500

GLFont *font;
FontInformation *fontInfo;
GUIContainer *root;
void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
}

double cFPS = 0;
int frameCount = 0;
double lastFrameUpdate = 0;
char fpsString[10];
void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	font->render("Testing 1 2 3 4 5 6");

	glPushMatrix();
	glTranslatef(0, 200, 0);
	sprintf(fpsString, "FPS: %f", cFPS);
	font->render(fpsString);
	glPopMatrix();

	glPushMatrix();
	sprintf(fpsString, "Mx: %f", InputManager::get()->getMouseX());
	glTranslatef(0, 100, 0);
	font->render(fpsString);

	sprintf(fpsString, "My: %f", InputManager::get()->getMouseY());
	glTranslatef(0, 25, 0);
	font->render(fpsString);
	glPopMatrix();

	frameCount++;
	if (glfwGetTime() - lastFrameUpdate > 1.0) {
		double time = glfwGetTime() - lastFrameUpdate;
		cFPS = ((double) frameCount) / time;
		lastFrameUpdate = glfwGetTime();
		frameCount = 0;
	}

	root->render();

	glFlush();
}

void glfwError(int code, const char* desc) {
	fprintf(stderr, "Error %d: %s\n", code, desc);
}

int main(int argc, char** argv) {
	glfwSetErrorCallback(glfwError);
	glfwInit();
	ResourceManager::get()->initialize(10);
	fontInfo = ResourceManager::get()->loadAsync<FontInformation>("font.png");
	font = new GLFont(fontInfo);
	font->setSize(16.0);

	GLWindow window("Test", WIDTH, HEIGHT);
	InputManager::get()->initialize(window.getHandle());

	printf("Doing other stuff lol!\n");
	double startTime = glfwGetTime();
	ResourceManager::get()->waitForLoad(fontInfo);
	printf("Waited for: %f seconds\n", glfwGetTime() - startTime);
	window.bindContext();
	reshape(WIDTH, HEIGHT);
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	root = new GUIContainer();
	root->size.set(50.0, 50.0);

	while (!window.isClosing()) {
		render();
		window.swapBuffers();
		glfwPollEvents();
		InputManager::get()->update();
	}

	delete font;
	root->deepDelete();
	delete root;
	ResourceManager::get()->destroy(fontInfo);
	ResourceManager::get()->terminate();
	InputManager::get()->terminate();

	// We need the context to free textures.
	window.destroy();
	glfwTerminate();
	return 0;
}
