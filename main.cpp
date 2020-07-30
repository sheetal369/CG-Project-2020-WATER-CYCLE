#include <windows.h>
#include <GL/glut.h>

/* Global variables */
char title[] = "[CG Project] WATER CYCLE";
int refreshMills = 360;        // refresh interval in milliseconds

GLfloat sunRadius = 0.15, sunPosX = -1.6, sunPoxY = 0.7;
GLfloat dx = 0.01; //change in x
GLfloat cloudRad = 0.09, Cloud1PosX = -1.2, Cloud1PosY = 0.7, Cloud2PosX = 0.59, Cloud2PoxY = 0.4; //Cloud Position of X and Y coordinate


/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest

   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test

   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void Clouds(GLfloat CloudPosX, GLfloat CloudPosY)
{
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(CloudPosX, CloudPosY, -2);
    glutSolidSphere(cloudRad, 50, 50);

    glLoadIdentity();
    glTranslatef(CloudPosX+4*0.08, CloudPosY, -2);
    glutSolidSphere(cloudRad, 50, 50);

    for (int i = 1; i<=3; i++)
    {
        glLoadIdentity();
        glTranslatef(CloudPosX+i*0.08, CloudPosY, -2);
        glutSolidSphere(cloudRad, 50, 50);

        glLoadIdentity();
        glTranslatef(CloudPosX+i*0.09, CloudPosY+0.07, -2);
        glutSolidSphere(cloudRad, 50, 50);

        glLoadIdentity();
        glTranslatef(CloudPosX+i*0.09, CloudPosY-0.07, -2);
        glutSolidSphere(cloudRad, 50, 50);
        glLoadIdentity();
    }
}

void tree(GLfloat radius, GLfloat treePosX, GLfloat treePosY)
{

    glColor3f(0.28, 0.56, 0.0);
    glTranslatef(treePosX, treePosY, -4);
        glutSolidSphere(radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX, treePosY+2*radius, -4);
        glutSolidSphere(radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX-radius/2, treePosY+radius/2, -4);
        glutSolidSphere(7/6.0*radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX+radius/2, treePosY+radius/2, -4);
        glutSolidSphere(7/6.0*radius, 50, 50);

    glLoadIdentity();
        glTranslatef(treePosX-radius/2, treePosY-radius, -4);
        glutSolidSphere(3/2.0*radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX+radius/2, treePosY-radius, -4);
        glutSolidSphere(3/2.0*radius, 50, 50);

    glLoadIdentity();
    glBegin(GL_POLYGON);
        glVertex3f(treePosX+0.6*radius, treePosY, -3);
        glVertex3f(treePosX-0.6*radius, treePosY, -3);
        glVertex3f(treePosX-0.6*radius, treePosY-5*radius, -3);
        glVertex3f(treePosX+0.6*radius, treePosY-5*radius, -3);
    glEnd();
}
void Tree(GLfloat Size, GLfloat treePosX, GLfloat treePosY) //Christmas Tree
{
    glColor3f(0.28, 0.56, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(treePosX, treePosY+2*Size, -4);
        glVertex3f(treePosX-0.8*Size, treePosY, -4);
        glVertex3f(treePosX+0.8*Size, treePosY, -4);

        glVertex3f(treePosX, treePosY+Size, -4);
        glVertex3f(treePosX-Size, treePosY-Size, -4);
        glVertex3f(treePosX+Size, treePosY-Size, -4);

        glVertex3f(treePosX, treePosY, -4);
        glVertex3f(treePosX-1.3*Size, treePosY-2*Size, -4);
        glVertex3f(treePosX+1.3*Size, treePosY-2*Size, -4);
    glEnd();
    //Branch
    glBegin(GL_POLYGON);
        glVertex3f(treePosX+0.3*Size, treePosY-2*Size, -3);
        glVertex3f(treePosX-0.3*Size, treePosY-2*Size, -3);
        glVertex3f(treePosX-0.3*Size, treePosY-3*Size, -3);
        glVertex3f(treePosX+0.3*Size, treePosY-3*Size, -3);
    glEnd();
}
void trees()
{
    //left to right
    tree(0.06, -1.7, 0.0);
    tree(0.03, -1.2, 0.0);
    Tree(0.09, -0.8, -0.01);
    Tree(0.1, -1.5, -0.1);
    tree(0.07, -0.5, 0.0);
    Tree(0.07, 1.0, -0.2);
    tree(0.03, 1.2, -0.3);
    tree(0.04, 1.5, -0.2);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   //SUN
   glLoadIdentity();                 // Reset the model-view matri
   glColor3f(1.0, 1.0, 0.0);
   glTranslatef(sunPosX, sunPoxY, -3.0);
   glutSolidSphere(sunRadius, 100, 100);

   //SEA
   glLoadIdentity();
   glColor3f(0.31,0.26,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(2, -0.5, -5);
      glVertex3f(-2, -0.5, -5);
      glVertex3f(-2, -1, -5);
      glVertex3f(2, -1, -5);
   glEnd();

   //GRASS
   glLoadIdentity();
   glColor3f(0.6,0.8,0.196078);
   glBegin(GL_POLYGON);
      glVertex3f(2, -0.3, -5);
      glVertex3f(-2, 0.0, -5);
      glVertex3f(-2, -0.5, -5);
      glVertex3f(2, -0.5, -5);
   glEnd();

   //SKY
   glLoadIdentity();
   glColor3f(0.53,0.81,0.92);
   glBegin(GL_POLYGON);
      glVertex3f(2, 1, -5);
      glVertex3f(-2, 1, -5);
      glVertex3f(-2, 0.0, -5);
      glVertex3f(2, -0.3, -5);
   glEnd();

   Clouds(Cloud1PosX, Cloud1PosY);
   Clouds(Cloud2PosX, Cloud2PoxY);

   trees();
   glutSwapBuffers();

   Cloud1PosX+=dx;
   Cloud2PosX+=dx/2;
}

/* Called back when timer expired */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    if (width >= height) {
      glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, 0.1, 100);
   } else {
     glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, 0.1, 100);
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(1200, 600);   // Set the window's initial width & height
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title

   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization

   glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
