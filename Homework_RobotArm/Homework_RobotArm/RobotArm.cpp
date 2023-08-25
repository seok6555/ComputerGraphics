#include <gl/glut.h>

static int rightShoulder = 0, rightElbow = 0, leftShoulder = 0, leftElbow = 0;
int height = 0, width = 0;
GLboolean isWireframe = true, IsXYZLine = true, isOrtho = true;

/// <summary>
/// 기준축 출력 함수.
/// </summary>
void XYZ() {
    // x축
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(-100.0, 0.0, 0.0);
        glVertex3f(100.0, 0.0, 0.0);
    glEnd();

    // y축
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, -100.0, 0.0);
        glVertex3f(0.0, 100.0, 0.0);
    glEnd();

    // z축
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, -100.0);
        glVertex3f(0.0, 0.0, 100.0);
    glEnd();
}

/// <summary>
/// 투상변환 변경 함수.
/// </summary>
/// <param name="w">가로</param>
/// <param name="h">세로</param>
void showProjectionMode(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isOrtho) {
        GLfloat widthFactor = (GLfloat)w / (GLfloat)800;
        GLfloat heightFactor = (GLfloat)h / (GLfloat)600;
        // widthFactor / heightFactor를 해줘서 left랑 right에만 넣어줘도 됨.
        // 결국 종횡비는 widthFactor / heightFactor기 때문에.
        glOrtho(-5.0 * widthFactor, 5.0 * widthFactor, -5.0 * heightFactor, 5.0 * heightFactor, 1.0, 20.0);
    }
    else if (!isOrtho)          gluPerspective(70.0, (GLdouble)w / (GLdouble)h, 1.0, 20.0);
}

/// <summary>
/// 모델링 모드에 따라 모델링 출력 함수.
/// </summary>
void showModelingMode() {
    if (isWireframe)            glutWireCube(1.0);          // 와이어프레임 모드
    else if (!isWireframe)      glutSolidCube(1.0);         // 솔리드 모드
}

/// <summary>
/// 메인 메뉴 콜백함수
/// </summary>
/// <param name="entryID">1: 기준축 ON/OFF. 2: 모델링 모드. 3: 투상변환 변경.</param>
void MyMainMenu(int entryID) {
    switch (entryID) {
    case 1:
        IsXYZLine = !IsXYZLine;
        break;
    case 2:
        isWireframe = !isWireframe;
        break;
    case 3:
        isOrtho = !isOrtho;
        showProjectionMode(width, height);
        break;
    case 4:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void init(void) {
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("XYZ Line ON/OFF", 1);
    glutAddMenuEntry("Wireframe/Solid", 2);
    glutAddMenuEntry("Ortho/Perspective", 3);
    glutAddMenuEntry("Exit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (IsXYZLine)                                          // IsXYZLine을 판별 후 true일때만 기준축 출력.
        XYZ();

    // 오른팔
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);                        // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)rightShoulder, 0.0, 0.0, 1.0);   // 원점을 기준으로 회전
        glTranslatef(1.0, 0.0, 0.0);	                    // Pivot으로 지정할 위치를 원점으로 이동

        glPushMatrix();	                                    // 원점을 기준으로 객체 생성 및 축소/확대
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();

        glTranslatef(1.0, 0.0, 0.0);	                    // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)rightElbow, 0.0, 0.0, 1.0);      // 원점을 기준으로 회전
        glTranslatef(1.0, 0.0, 0.0);	                    // Pivot으로 지정할 위치를 원점으로 이동

        glPushMatrix();	                                    // 원점을 기준으로 객체 생성 및 축소/확대
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();
    glPopMatrix();

    // 왼팔
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);                        // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)leftShoulder, 0.0, 0.0, 1.0);    // 원점을 기준으로 회전
        glTranslatef(-1.0, 0.0, 0.0);	                    // Pivot으로 지정할 위치를 원점으로 이동

        glPushMatrix();	                                    // 원점을 기준으로 객체 생성 및 축소/확대
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();

        glTranslatef(-1.0, 0.0, 0.0);	                    // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)leftElbow, 0.0, 0.0, 1.0);       // 원점을 기준으로 회전
        glTranslatef(-1.0, 0.0, 0.0);	                    // Pivot으로 지정할 위치를 원점으로 이동

        glPushMatrix();	                                    // 원점을 기준으로 객체 생성 및 축소/확대
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    width = w;
    height = h;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    showProjectionMode(width, height); // display에서 쓸땐 꼭 glLoadIdentity()를 해줘야함.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        //오른팔 컨트롤
    case 's':
        rightShoulder = (rightShoulder + 5) % 360;
        break;
    case 'S':
        rightShoulder = (rightShoulder - 5) % 360;
        break;
    case 'e':
        rightElbow = (rightElbow + 5) % 360;
        break;
    case 'E':
        rightElbow = (rightElbow - 5) % 360;
        break;

        // 왼팔 컨트롤
    case 'a':
        leftShoulder = (leftShoulder + 5) % 360;
        break;
    case 'A':
        leftShoulder = (leftShoulder - 5) % 360;
        break;
    case 'w':
        leftElbow = (leftElbow + 5) % 360;
        break;
    case 'W':
        leftElbow = (leftElbow - 5) % 360;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Arm");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}