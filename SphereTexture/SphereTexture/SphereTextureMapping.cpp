#include <stdlib.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <gl/GLAux.h>

GLuint g_textureID;
GLUquadric* g_qobj;

void oglSphere(double radius) {
	int slices = 50;

    // ����ȿ���� �ؽ��ĸ� �Ѵ� ���ٶ� �̰� �ΰ��� ���൵ �ȴ�.
	gluQuadricTexture(g_qobj, GL_TRUE); // �ؽ��İ� �ȴ�.
	gluQuadricNormals(g_qobj, GLU_SMOOTH); // �븻���� �ε巴�� �ش�.
	gluSphere(g_qobj, radius, slices, slices);

	//gluDeleteQuadric(g_qobj);
}

void loadTexture(void) {
    // �ַ�� ���� ���� ������Ʈ ������ �־�� ��.
    AUX_RGBImageRec* pTextureImage = auxDIBImageLoad(L"earth.bmp");

    if (pTextureImage != NULL) {
        glGenTextures(1, &g_textureID);// �ؽ��� ��ü�� �ϳ��� ����ڴ�.

        glBindTexture(GL_TEXTURE_2D, g_textureID);

        //2d�ؽ��ĸ� Ÿ������, �ؽ��İ� ��ҵɶ� ���������� �ؼ� ������ְڴ�.
        // Ȯ���Ҷ��� ���Ͼ� (��������)�ؼ� Ȯ��.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
    }

    // 5���� ��� �Ҵ�� �޸𸮸� ��ȯ.
    if (pTextureImage) {
        if (pTextureImage->data)
            free(pTextureImage->data);

        free(pTextureImage);
    }
}

void init(void) {
    loadTexture();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);// �ؽ��� ��� Ȱ��ȭ.

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    g_qobj = gluNewQuadric();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, g_textureID);
	oglSphere(1.0);
    glutSwapBuffers();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sphere Texture Mapping");
    init();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutMainLoop();
}