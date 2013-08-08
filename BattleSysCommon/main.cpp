#include "TexLoad/Texture.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#define WIDTH  250
#define HEIGHT 500

GLTexture t = GLTexture();

void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	t.bind();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);

	glTexCoord2f(1, 0);
	glVertex2f(WIDTH, 0);

	glTexCoord2f(1, 1);
	glVertex2f(WIDTH, HEIGHT);

	glTexCoord2f(0, 1);
	glVertex2f(0, HEIGHT);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	FILE *fp = fopen("char.png", "rb");
	if (fp) {
		t.loadFromPNG(fp);
		fclose(fp);
	} else {
		printf("Can'topen\n");
	}
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
	t.loadToVRAM();
	glutMainLoop();
	return 0;
}
