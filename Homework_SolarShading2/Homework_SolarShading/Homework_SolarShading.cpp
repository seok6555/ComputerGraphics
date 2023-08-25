#include <Windows.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/GLAux.h>
#include <math.h>

static int Day = 0, Time = 0;

GLboolean isLight = true;
GLboolean isTexture = true;
GLboolean isPerspective = true;
GLboolean isXYZ = true;

GLint nModeling = 1;
GLint nWidth = 500, nHeight = 500;

GLfloat red[] = { 0.8f, 0.0f, 0.0f, 1.0f };
GLfloat blue[] = { 0.0f, 0.2f, 1.0f, 1.0f };
GLfloat gray[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat light0_pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat material_diffuse0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat material_diffuse1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat material_diffuse2[] = { 0.5f, 0.5f, 0.5f, 1.0f };

AUX_RGBImageRec* pTextureImage[3];  // �̹��� ���� ���� ���� �迭
GLuint g_textureID[3];              // �ؽ��� ���� �迭
GLUquadricObj* sun, * earth, * moon;// �༺ ������

/// <summary>
/// ���� On/Off �Լ�
/// </summary>
void LightController() {
    if (isLight)
    {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
    }
    else
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
}

/// <summary>
/// �ؽ��� ���� On/Off �Լ�
/// </summary>
void TextureMappingController() {
    if (isTexture)
    {
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
}

/// <summary>
/// X, Y, Z �� ���� ǥ�� �Լ�
/// </summary>
void XYZ() {
    if (isXYZ)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(-2.0f, 0.0f, 0.0f);
        glVertex3f(2.0f, 0.0f, 0.0f);
        glEnd();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(0.0f, -2.0f, 0.0f);
        glVertex3f(0.0f, 2.0f, 0.0f);
        glEnd();

        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, -2.0f);
        glVertex3f(0.0f, 0.0f, 2.0f);
        glEnd();
    }
}

/// <summary>
/// ����ȯ ���� �Լ�
/// </summary>
void ProjectionModelView(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isPerspective)
        gluPerspective(45.0, (double)nWidth / nHeight, 0.1, 100.0);
    else
        glOrtho(-2.0, 2.0, -2.0 * (double)nWidth / nHeight, 2.0 * (double)nWidth / nHeight, -6.0, 6.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
}

/// <summary>
/// oglSphere ��ü ���� �Լ�
/// </summary>
void oglSphere(double radius, int slices) {
    gluQuadricNormals(sun, GLU_SMOOTH);
    gluQuadricNormals(earth, GLU_SMOOTH);
    gluQuadricNormals(moon, GLU_SMOOTH);
    gluSphere(sun, radius, slices, slices);
    gluSphere(earth, radius, slices, slices);
    gluSphere(moon, radius, slices, slices);
}

/// <summary>
/// renderSphere ��ü ���� �Լ�
/// </summary>
void renderSphere(float cx, float cy, float cz, float r, int p) {
    // cx, cy, cz: Sphere�� �߽� ��ǥ, r: radius(������), p: precision(���е�)
    const float PI = 3.14159265358979f;
    const float TWOPI = 6.28318530717958f;
    const float PIDIV2 = 1.57079632679489f;

    float theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;
    float ex = 0.0f, ey = 0.0f, ez = 0.0f;
    float px = 0.0f, py = 0.0f, pz = 0.0f;

    if (r < 0) r = -r;	// radius�� ���� �����̾�� �Ѵ�.
    if (p < 0) p = -1;	// precision�� ���� �����̾�� �Ѵ�.

    if (p < 4 || r <= 0) {
        glBegin(GL_POINTS);
        glVertex3f(cx, cy, cz);
        glEnd();
        return;
    }

    for (int i = 0; i < p / 2; ++i) {
        theta1 = i * TWOPI / p - PIDIV2;
        theta2 = (i + 1) * TWOPI / p - PIDIV2;

        glBegin(GL_TRIANGLE_STRIP);
        {
            for (int j = 0; j <= p; ++j) {
                theta3 = j * TWOPI / p;

                ex = cos(theta2) * cos(theta3);
                ey = sin(theta2);
                ez = cos(theta2) * sin(theta3);
                px = cx + r * ex;
                py = cy + r * ey;
                pz = cz + r * ez;

                glNormal3f(ex, ey, ez);
                glTexCoord2f(-(j / (float)p), 2 * (i + 1) / (float)p);
                glVertex3f(px, py, pz);
                ex = cos(theta1) * cos(theta3);
                ey = sin(theta1);
                ez = cos(theta1) * sin(theta3);
                px = cx + r * ex;
                py = cy + r * ey;
                pz = cz + r * ez;

                glNormal3f(ex, ey, ez);
                glTexCoord2f(-(j / (float)p), 2 * i / (float)p);
                glVertex3f(px, py, pz);
            }
        }
        glEnd();
    }
}

/// <summary>
/// �𵨸� ��忡 ���� �𵨸� ��� �Լ�.
/// </summary>
void drawSphere(GLdouble radius, GLint slices) {
    switch (nModeling)
    {
    case 1:
        oglSphere(radius, slices);
        break;
    case 2:
        renderSphere(0, 0, 0, radius, slices);
        break;
    case 3:
        glutWireSphere(radius, slices, slices);
        break;
    case 4:
        glutSolidSphere(radius, slices, slices);
        break;
    default:
        break;
    }
}

/// <summary>
/// ���� �޴� �ݹ��Լ�
/// </summary>
void MyMainMenu(int entryID) {
    switch (entryID) {
    case 1:
        isLight = !isLight;
        break;
    case 2:
        isTexture = !isTexture;
        break;
    case 3:
        isXYZ = !isXYZ;
        break;
    case 4:
        isPerspective = !isPerspective;
        ProjectionModelView();
        break;
    case 5:
        gluDeleteQuadric(sun);
        gluDeleteQuadric(earth);
        gluDeleteQuadric(moon);
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

/// <summary>
/// �𵨸� �޴� �ݹ��Լ�
/// </summary>
void MyModelingModeMenu(int entryID) {
    nModeling = entryID;
    glutPostRedisplay();
}

/// <summary>
/// Ű���� ����� �Լ�
/// </summary>
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd':
        Day = (Day + 10) % 360;
        break;
    case 'D':
        Day = (Day - 10) % 360;
        break;
    case 't':
        Time = (Time + 5) % 360;
        break;
    case 'T':
        Time = (Time - 5) % 360;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    LightController();
    glDisable(GL_LIGHTING);
    TextureMappingController();
    XYZ();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, g_textureID[0]);
    drawSphere(0.2, 20);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);

    glPushMatrix();
        glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
        glTranslatef(0.7, 0.0, 0.0);
        glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
        glColor3f(0.0, 0.2, 1.0);
        glBindTexture(GL_TEXTURE_2D, g_textureID[1]);
        glLightfv(GL_LIGHT1, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
        drawSphere(0.1, 10);

        glPushMatrix();
            glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
            glTranslatef(0.2, 0.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, g_textureID[2]);
            glLightfv(GL_LIGHT2, GL_POSITION, light0_pos);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, gray);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse2);
            drawSphere(0.04, 10);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void MyReshape(int width, int height) {
    nWidth = width;
    nHeight = height;

    glViewport(0, 0, width, height);
    ProjectionModelView();
}

void Init() {
    GLint MyModelingModeID = glutCreateMenu(MyModelingModeMenu);
    glutAddMenuEntry("oglSphere", 1);
    glutAddMenuEntry("renderSphere", 2);
    glutAddMenuEntry("WireSphere", 3);
    glutAddMenuEntry("SolidSphere", 4);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Light On/Off", 1);
    glutAddMenuEntry("Texture Mapping On/Off", 2);
    glutAddMenuEntry("XYZ Line On/Off", 3);
    glutAddSubMenu("Modeling Mode", MyModelingModeID);
    glutAddMenuEntry("ProjectionMode Perspective/Ortho", 4);
    glutAddMenuEntry("Exit", 5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // ��ü ����
    sun = gluNewQuadric();
    earth = gluNewQuadric();
    moon = gluNewQuadric();

    // �ؽ��� ���� ���
    gluQuadricTexture(sun, GL_TRUE);
    gluQuadricTexture(earth, GL_TRUE);
    gluQuadricTexture(moon, GL_TRUE);

    memset(pTextureImage, 0, sizeof(void*) * 1);

    // �̹��� �ε�
    pTextureImage[0] = auxDIBImageLoad(L"sun.bmp");
    pTextureImage[1] = auxDIBImageLoad(L"earth.bmp");
    pTextureImage[2] = auxDIBImageLoad(L"moon.bmp");

    if (pTextureImage != NULL) {
        glGenTextures(3, &g_textureID[0]);// �ؽ��� ����

        for (int i = 0; i < 3; i++)
        {
            glBindTexture(GL_TEXTURE_2D, g_textureID[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[i]->sizeX, pTextureImage[i]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[i]->data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glEnable(GL_TEXTURE_2D);// �ؽ��� ��� Ȱ��ȭ.
        }
    }

    // �Ҵ�� �޸𸮸� ��ȯ.
    for (int i = 0; i < 3; i++)
    {
        if (pTextureImage[i]) {
            if (pTextureImage[i]->data)
                free(pTextureImage[i]->data);
            free(pTextureImage[i]);
        }
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(nWidth, nHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    Init();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}