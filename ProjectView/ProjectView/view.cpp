#include <gl/glut.h>

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); // 전부 0이면 검정색.
	glShadeModel(GL_SMOOTH);
}

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT); //칼라 버퍼를 지워줌.

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(1.5);

	glutSwapBuffers();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 5.0);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); // 좌상단에서부터 시작해서 오른쪽(x)으로 100만큼, 아래(y)로 100만큼
	// glut가 쓰는 좌표계는 화면 좌표계임.
	glutCreateWindow("Projection - gluPerspective");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}
