#include <gl/glut.h>

static int Day = 0, Time = 0;

float eX = 0.7, eY = 0, eZ = 0;
float mX = 0.2, mY = 0.0, mZ = 0.0;

GLboolean isWireframe = false;

const GLfloat gray[] = { 0.1, 0.1, 0.1, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat sun_light_pos[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat earth_light_pos[] = { eX, eY, eZ, 1.0 };
GLfloat moon_light_pos[] = { mX, mY, mZ, 1.0 };

/// <summary>
/// 모델링 모드에 따라 모델링 출력 함수.
/// </summary>
void showModelingMode(GLdouble radius, GLint slices, GLint stacks) {
	if (isWireframe)            glutWireSphere(radius, slices, stacks);		// 와이어프레임 모드
	else if (!isWireframe)      glutSolidSphere(radius, slices, stacks);    // 솔리드 모드
}

/// <summary>
/// 메인 메뉴 콜백함수
/// </summary>
/// <param name="entryID">1: 모델링 모드. 2: 종료.</param>
void MyMainMenu(int entryID) {
	switch (entryID) {
	case 1:
		isWireframe = !isWireframe;
		break;
	case 2:
		exit(0);
		break;
	}

	glutPostRedisplay();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// 태양 모델링 및 광원
	glPushMatrix();
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_pos);
		glDisable(GL_LIGHTING);
		glColor3d(1.0, 0.3, 0.3);
		showModelingMode(0.2, 20, 16);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//지구 모델링 및 광원
    glPushMatrix();
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
		glTranslatef(eX, eY, eZ);
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT1, GL_POSITION, earth_light_pos);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT, GL_SHININESS, polished);
		showModelingMode(0.1, 10, 8);

		// 달 모델링 및 광원
		glPushMatrix();
			glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
			glTranslatef(mX, mY, mZ);
			glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
			glLightfv(GL_LIGHT2, GL_POSITION, moon_light_pos);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, white);
			glMaterialfv(GL_FRONT, GL_SHININESS, polished);
			showModelingMode(0.04, 10, 8);
		glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd':
        Day = (Day + 10) % 360;
        break;
    case 't':
        Time = (Time + 5) % 360;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void MyInit() {
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };	// 주변광
	GLfloat light0_diffuse[] = { 0.8, 0.7, 0.6, 1.0 };	// 반사광

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Wireframe/Solid", 1);
	glutAddMenuEntry("Exit", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);// 조명 기능 활성화.
	glEnable(GL_LIGHT0);// 0번 광원 활성화
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

	glEnable(GL_LIGHT1);// 1번 광원 활성화
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue);

	glEnable(GL_LIGHT2);// 2번 광원 활성화
	glLightfv(GL_LIGHT2, GL_DIFFUSE, gray);
	glLightfv(GL_LIGHT2, GL_SPECULAR, gray);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");
	MyInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}