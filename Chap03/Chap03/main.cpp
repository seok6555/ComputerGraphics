#include <gl/glut.h>

GLfloat Tx = 0.5, Ty = 0.0, Tz = 0.0;

// OpenGL ���ο��� ��� ���� ����� �ݴ�� ��. �׷��� ������ �ƴ� �Ʒ��ʿ�{Tx, Ty, Tz, 1.0}�� �����.
GLfloat Translate_matrix[4][4] = {
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{Tx, Ty, Tz, 1.0}
};

void MyDisplay() {
	glMultMatrixf((float*)Translate_matrix);
	//glTranslatef(0.0, 0.0, 0.5);
	glutSolidTeapot(0.5);
	glFlush();
}

int main(int argc, char** argv) {
	glutCreateWindow("OpenGL Translate Example");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}
