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

    // 광원효과와 텍스쳐를 둘다 해줄땐 이거 두개만 해줘도 된다.
	gluQuadricTexture(g_qobj, GL_TRUE); // 텍스쳐가 된다.
	gluQuadricNormals(g_qobj, GLU_SMOOTH); // 노말값을 부드럽게 준다.
	gluSphere(g_qobj, radius, slices, slices);

	//gluDeleteQuadric(g_qobj);
}

void loadTexture(void) {
    // 솔루션 폴더 말고 프로젝트 폴더에 넣어야 됨.
    AUX_RGBImageRec* pTextureImage = auxDIBImageLoad(L"earth.bmp");

    if (pTextureImage != NULL) {
        glGenTextures(1, &g_textureID);// 텍스쳐 객체를 하나만 만들겠다.

        glBindTexture(GL_TEXTURE_2D, g_textureID);

        //2d텍스쳐를 타겟으로, 텍스쳐가 축소될때 선형보간을 해서 축소해주겠다.
        // 확대할때도 리니어 (선형보간)해서 확대.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
    }

    // 5에서 썼던 할당된 메모리를 반환.
    if (pTextureImage) {
        if (pTextureImage->data)
            free(pTextureImage->data);

        free(pTextureImage);
    }
}

void init(void) {
    loadTexture();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);// 텍스쳐 기능 활성화.

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