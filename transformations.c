#include <stdio.h>
#include <GL/glut.h> 
 
char title[] = "OPENGL ASSIGNMENT";
GLfloat anglePyramid = 0.0f;  
GLfloat scalingfactor=0.2f;
int refresh_time= 10;       
 
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);                   
   glEnable(GL_DEPTH_TEST);   
   glDepthFunc(GL_LEQUAL);    
   glShadeModel(GL_SMOOTH);  
}
 
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW);    
   glLoadIdentity();               
   glTranslatef(-1.5f+scalingfactor, 0.0f, -6.0f+scalingfactor);  // Move left and into the screen
   glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
   glScalef(0.2f+scalingfactor,0.2f+scalingfactor,0.2f+scalingfactor);
   glBegin(GL_TRIANGLES);
   glColor3f(10.0f, 10.0f, 10.0f);
   glVertex3f(0.0f, 1.0f, 0.0f);
   glColor3f(10.0f, 10.0f, 0.0f);     
   glVertex3f(1.0f, -1.0f, -1.0f);
   glColor3f(10.0f, 10.0f, 1.0f);    
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glEnd(); 
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
   anglePyramid += 0.2f;
   scalingfactor+=0.0002f;
}
 
void timer(int value) {
   glutPostRedisplay();
   glutTimerFunc(refresh_time, timer, 0);
}
 
void reshape(GLsizei width, GLsizei height) {
   if (height == 0) height = 1;                
   GLfloat aspectratio = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();     
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspectratio, 0.1f, 100.0f);
}
 
int main(int argc, char** argv) {
   
   glutInit(&argc, argv);           
   glutInitDisplayMode(GLUT_SINGLE); // Enable double buffered mode
   glutInitWindowSize(840, 680);   
   glutInitWindowPosition(50, 50); 
   glutCreateWindow(title);          
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();
   glutTimerFunc(0, timer, 0);
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
