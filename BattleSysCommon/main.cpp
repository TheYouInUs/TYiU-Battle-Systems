#include "Graphics/Util/GLFont.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#define WIDTH  250
#define HEIGHT 500

GLFont font = GLFont(0, 16, 16, "font.png", 0);
void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, HEIGHT, 0.0, WIDTH, -1.0, 1.0);
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	font.render("Test");
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

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
	font.initialize();
	glutMainLoop();
	font.dispose();
	return 0;
}
