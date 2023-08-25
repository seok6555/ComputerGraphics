#include <iostream>
using namespace std;
#include <iomanip>
using namespace std;
#include <gl/glut.h>

int window_width = 640;
int window_height = 480;

const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };
const GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 }; // 원점에 광원을 넣겠다.

GLfloat move_y = 0.0;
GLfloat move_z = 0.0;
GLfloat const_att = 1.0;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH); // 음영

    glTranslatef(0.0, 0.0, -20.0);
    glPushMatrix();
    glTranslatef(0.0, move_y, move_z);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att); // 광원 설정 함수.(GL_LIGHT0: 광원 식별 기호)
    // GL_CONSTANT_ATTENUATION: 2차항으로 표현. 상수항의 값을 뭐로 줄것인가.
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos); // 0번 광원의 위치를 light_pos로 설정.
    glDisable(GL_LIGHTING);
    // 비활성화 하다가 활성화 하는 이유: 두 구체 사이에 광원이 있는데 그 광원을 표현해줄 방법이 없음.
    // 광원을 활성화 하면 객체에 컬러값을 주는게 의미가 없어짐.
    // 광원이 있는 것처럼 표현.
    glColor3d(0.9, 0.9, 0.5);
    glutSolidSphere(0.1, 10, 10);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // 구체에 대한 표면 특성.
    glTranslatef(-5.0, 0.0, 0.0);
    // GL_FRONT: 카메라를 바라보는 면(표면).
    // GL_AMBIENT_AND_DIFFUSE: 주변광 & 분산광 설정.
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    // GL_SPECULAR: 반사광의 반사도. 0 = 정반사를 시키지 않겠다.
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    // GL_SHININESS: 광택의 범위.
    glMaterialfv(GL_FRONT, GL_SHININESS, dull);
    // GL_SPECULAR를 설정하지 않으면 GL_SHININESS를 설정해도 보이지 않는다.

    glutSolidSphere(3.0, 40, 40);

    glTranslatef(10.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);
    glutSolidSphere(3.0, 40, 40);

    glutSwapBuffers();
    glFlush();
}

// 마우스 콜백
void Mouse_Movement(int x, int y) {
    move_z = (10.0 * x) / window_width;
    move_y = 5.0 - (10.0 * y) / window_height;

    glutPostRedisplay();
}

void MyReshape(int w, int h) {
    window_width = w;
    window_height = h;

    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(35.0, GLfloat(window_width) / GLfloat(window_height), 1.0, 50.0);
    glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        const_att *= 0.9f;
    }
    else if (key == GLUT_KEY_RIGHT) {
        const_att /= 0.9f;
    }

    glutPostRedisplay();
}

// 광원 기능 활성화. 나중에 바꿀일 없는 것들을 선언.
void MyInit() {
    // 오픈지엘은 유한상태기계기 때문에 상태를 변경해주기 전까진 계속 그 값을 가짐.
    glEnable(GL_LIGHTING);// 조명 기능 활성화.
    glEnable(GL_LIGHT0);// 0번 광원 활성화
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);// GL_DIFFUSE: 난반사. 난반사의 빛의 세기를 흰색으로
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);// GL_SPECULAR: 정반사. 정반사의 빛의 세기를 흰색으로

    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("One Lighting Two Objects");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutMotionFunc(Mouse_Movement);
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);

    glutMainLoop();
    return 0;
}