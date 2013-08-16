#include "Graphics/Util/GLFont.h"
#include "Graphics/Util/FontInformation.h"
#include "Graphics/Util/GLTexture.h"
#include "Resources/ResourceManager.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
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
	glutInit(&argc, argv);
	ResourceManager::get()->initialize(10);
	fontInfo = ResourceManager::get()->find<FontInformation>("font.png");
	font = new GLFont(fontInfo);
	font->setSize(16.0);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Test");

	glutDisplayFunc(render);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	reshape(WIDTH, HEIGHT);

	glutIdleFunc(glutPostRedisplay);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();

	delete font;
	ResourceManager::get()->destroy(fontInfo);
	return 0;
}
