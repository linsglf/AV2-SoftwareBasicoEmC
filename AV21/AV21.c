#include <stdio.h>
#include <time.h>
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    time_t now;
    time(&now);
    struct tm *current_time = localtime(&now);

    char time_str[9];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", current_time);

    glRasterPos2f(-0.22, 0);
    for (int i = 0; i < 8; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, time_str[i]);
    }

    char am_pm;
    if (current_time->tm_hour >= 12)
    {
        am_pm = 'P';    
    }else {
        am_pm = 'A';
    }
    

    glRasterPos2f(-0.08, -0.15);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, am_pm);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');

    glFlush();
}

int segundos = 0;
void update(int temposegundos) {
    segundos++;
    glutPostRedisplay();

    printf("%d\n", segundos);

    if (segundos < 60) {
        glutTimerFunc(1000, update, 0);
    }else if (segundos == 60){
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutCreateWindow("1 MINUTO AV2");
    glClearColor(0.4, 0.1,0.3, 0);
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
