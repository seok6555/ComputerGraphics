#include <gl/glut.h>
#include <gl/glu.h>

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; 

void MyDisplay( ) {
    glViewport(0, 0, 500, 500);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
       glVertex3f(TopLeftX/500.0, (500-TopLeftY)/500.0, 0.0);
       glVertex3f(TopLeftX/500.0, (500-BottomRightY)/500.0, 0.0);
       glVertex3f(BottomRightX/500.0, (500-BottomRightY)/500.0, 0.0);
       glVertex3f(BottomRightX/500.0, (500-TopLeftY)/500.0, 0.0);
    glEnd( );
    glFlush( );
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if(Button==GLUT_LEFT_BUTTON && State==GLUT_DOWN){
        TopLeftX = X;
        TopLeftY = Y;
    }
}

void MyMouseMove(GLint X, GLint Y) { 
    BottomRightX = X;
    BottomRightY = Y;
    glutPostRedisplay( ); // 시스템에서 콜백함수가 호출됨.
}

void MyInit() {
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mouse Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);

    glutMainLoop( );
    return 0;	
}