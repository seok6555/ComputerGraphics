#include <gl/glut.h>

GLfloat Tx = 0.5, Ty = 0.0, Tz = 0.0;

// OpenGL 내부에선 행렬 벡터 계산을 반대로 함. 그래서 우측이 아닌 아래쪽에{Tx, Ty, Tz, 1.0}를 써야함.
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
