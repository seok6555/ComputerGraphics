#include <gl/glut.h>
#include <gl/glu.h>

GLboolean IsSphere = true; 

void MyDisplay( ) {
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.0, 0.5, 0.5);
     if (IsSphere)
          glutWireSphere(0.5, 30, 30);
     else glutWireTorus(0.1, 0.3, 40, 20);
     glFlush( );
}

void MyMainMenu(int entryID) {
     if(entryID == 1)         IsSphere = true;
     else if (entryID == 2)    IsSphere = false;
     else if(entryID == 3)     exit(0);

     glutPostRedisplay(); // 플래그 설정
}

void MyInit() {
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( ); 

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    // glutCreateMenu: 메뉴 객체를 만들 수 있음 콜백 함수를 등록해야함.
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Draw Sphere", 1); 
    glutAddMenuEntry("Draw Torus", 2); 
    glutAddMenuEntry("Exit", 3); 
    glutAttachMenu(GLUT_RIGHT_BUTTON); 
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Menu Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);

    glutMainLoop( );
    return 0;
}