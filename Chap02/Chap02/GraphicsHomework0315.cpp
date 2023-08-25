#include <gl/glut.h>

// 모양, 크기, 프레임을 결정하는 bool값.
GLboolean IsSphere = true;
GLboolean IsSmall = true;
GLboolean IsWire = true;

// 화면에 출력을 담당하는 함수.
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.5, 0.5);

    // if문으로 도형의 형태, 크기, 표면을 결정.
    if ((IsSphere) && (IsSmall) && (IsWire))        // Sphere, Small, Wire
        glutWireSphere(0.5, 30, 30);
    else if ((IsSphere) && (!IsSmall) && (IsWire))  // Sphere, Big, Wire
        glutWireSphere(0.7, 30, 30);
    else if ((IsSphere) && (IsSmall) && (!IsWire))  // Sphere, Small, Solid
        glutSolidSphere(0.5, 30, 30);
    else if ((IsSphere) && (!IsSmall) && (!IsWire)) // Sphere, Big, Solid
        glutSolidSphere(0.7, 30, 30);
    else if ((!IsSphere) && (IsSmall) && (IsWire))  // Torus, Small, Wire
        glutWireTorus(0.1, 0.3, 40, 20);
    else if ((!IsSphere) && (!IsSmall) && (IsWire)) // Torus, Big, Wire
        glutWireTorus(0.2, 0.5, 40, 20);
    else if ((!IsSphere) && (IsSmall) && (!IsWire)) // Torus, Small, Solid
        glutSolidTorus(0.1, 0.3, 40, 20);
    else glutSolidTorus(0.2, 0.5, 40, 20);          // Torus, Big, Solid

    glFlush();
}

/// <summary>
/// 메인 메뉴 콜백함수
/// </summary>
/// <param name="entryID">1: 프레임 결정. 2: 프로그램 종료.</param>
void MyMainMenu(int entryID) {
    if (entryID == 1) {
        if (IsWire)             IsWire = false;
        else if (!IsWire)       IsWire = true;
    }
    else if (entryID == 2)      exit(0);

    glutPostRedisplay();
}

/// <summary>
/// 구체 사이즈 결정 콜백함수
/// </summary>
/// <param name="entryID">1: 작은 크기. 2: 큰 크기.</param>
void MySphereSizeMenu(int entryID) {
    IsSphere = true;
    if (entryID == 1)           IsSmall = true;
    else if (entryID == 2)      IsSmall = false;

    glutPostRedisplay();
}

/// <summary>
/// 도넛 사이즈 결정 콜백함수
/// </summary>
/// <param name="entryID">1: 작은 크기. 2: 큰 크기.</param>
void MyTorusSizeMenu(int entryID) {
    IsSphere = false;
    if (entryID == 1)           IsSmall = true;
    else if (entryID == 2)      IsSmall = false;

    glutPostRedisplay();
}

/// <summary>
/// 메뉴 및 기타 초기화 함수.
/// </summary>
void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    GLint MySphereSizeID = glutCreateMenu(MySphereSizeMenu);
    glutAddMenuEntry("Small Sphere", 1);
    glutAddMenuEntry("Large Sphere", 2);

    GLint MyTorusSizeID = glutCreateMenu(MyTorusSizeMenu);
    glutAddMenuEntry("Small Torus", 1);
    glutAddMenuEntry("Large Torus", 2);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddSubMenu("Draw Sphere", MySphereSizeID);
    glutAddSubMenu("Draw Torus", MyTorusSizeID);
    glutAddMenuEntry("Modeling Mode", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Menu Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);

    glutMainLoop();
    return 0;
}