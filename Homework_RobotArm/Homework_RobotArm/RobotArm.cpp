#include <gl/glut.h>

static int rightShoulder = 0, rightElbow = 0, leftShoulder = 0, leftElbow = 0;
int height = 0, width = 0;
GLboolean isWireframe = true, IsXYZLine = true, isOrtho = true;

/// <summary>
/// ������ ��� �Լ�.
/// </summary>
void XYZ() {
    // x��
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(-100.0, 0.0, 0.0);
        glVertex3f(100.0, 0.0, 0.0);
    glEnd();

    // y��
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, -100.0, 0.0);
        glVertex3f(0.0, 100.0, 0.0);
    glEnd();

    // z��
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, -100.0);
        glVertex3f(0.0, 0.0, 100.0);
    glEnd();
}

/// <summary>
/// ����ȯ ���� �Լ�.
/// </summary>
/// <param name="w">����</param>
/// <param name="h">����</param>
void showProjectionMode(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isOrtho) {
        GLfloat widthFactor = (GLfloat)w / (GLfloat)800;
        GLfloat heightFactor = (GLfloat)h / (GLfloat)600;
        // widthFactor / heightFactor�� ���༭ left�� right���� �־��൵ ��.
        // �ᱹ ��Ⱦ��� widthFactor / heightFactor�� ������.
        glOrtho(-5.0 * widthFactor, 5.0 * widthFactor, -5.0 * heightFactor, 5.0 * heightFactor, 1.0, 20.0);
    }
    else if (!isOrtho)          gluPerspective(70.0, (GLdouble)w / (GLdouble)h, 1.0, 20.0);
}

/// <summary>
/// �𵨸� ��忡 ���� �𵨸� ��� �Լ�.
/// </summary>
void showModelingMode() {
    if (isWireframe)            glutWireCube(1.0);          // ���̾������� ���
    else if (!isWireframe)      glutSolidCube(1.0);         // �ָ��� ���
}

/// <summary>
/// ���� �޴� �ݹ��Լ�
/// </summary>
/// <param name="entryID">1: ������ ON/OFF. 2: �𵨸� ���. 3: ����ȯ ����.</param>
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
    if (IsXYZLine)                                          // IsXYZLine�� �Ǻ� �� true�϶��� ������ ���.
        XYZ();

    // ������
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);                        // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)rightShoulder, 0.0, 0.0, 1.0);   // ������ �������� ȸ��
        glTranslatef(1.0, 0.0, 0.0);	                    // Pivot���� ������ ��ġ�� �������� �̵�

        glPushMatrix();	                                    // ������ �������� ��ü ���� �� ���/Ȯ��
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();

        glTranslatef(1.0, 0.0, 0.0);	                    // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)rightElbow, 0.0, 0.0, 1.0);      // ������ �������� ȸ��
        glTranslatef(1.0, 0.0, 0.0);	                    // Pivot���� ������ ��ġ�� �������� �̵�

        glPushMatrix();	                                    // ������ �������� ��ü ���� �� ���/Ȯ��
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();
    glPopMatrix();

    // ����
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);                        // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)leftShoulder, 0.0, 0.0, 1.0);    // ������ �������� ȸ��
        glTranslatef(-1.0, 0.0, 0.0);	                    // Pivot���� ������ ��ġ�� �������� �̵�

        glPushMatrix();	                                    // ������ �������� ��ü ���� �� ���/Ȯ��
            glColor3f(1.0, 1.0, 1.0);
            glScalef(2.0, 0.4, 1.0);
            showModelingMode();
        glPopMatrix();

        glTranslatef(-1.0, 0.0, 0.0);	                    // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)leftElbow, 0.0, 0.0, 1.0);       // ������ �������� ȸ��
        glTranslatef(-1.0, 0.0, 0.0);	                    // Pivot���� ������ ��ġ�� �������� �̵�

        glPushMatrix();	                                    // ������ �������� ��ü ���� �� ���/Ȯ��
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

    showProjectionMode(width, height); // display���� ���� �� glLoadIdentity()�� �������.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        //������ ��Ʈ��
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

        // ���� ��Ʈ��
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