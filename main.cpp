#include <GL/glut.h>

/* Global variables */
char title[] = "[CG Project] WATER CYCLE";
int refreshMills = 360;        // refresh interval in milliseconds

GLfloat sunRadius = 0.15, sunPosX = -1.6, sunPoxY = 0.7;
GLfloat dx = 0.01; //change in x
GLfloat cloudRad = 0.09, Cloud1PosX = -1.2, Cloud1PosY = 0.7, Cloud2PosX = 1.55, Cloud2PosY = 0.4 ; //Cloud Position of X and Y coordinate
GLfloat Cloud3PosX = -3.54, Cloud3PosY = 0.84;
GLfloat swan1PosX = -1.0, swan2PosX = 1.5, swan3PosX = 2.5;
GLfloat WVx = -1.69, WVy = -0.43; //WaterVapor
GLfloat RDx = Cloud2PosX+8*dx/2, RDy = Cloud2PosY+0.09; //RainDrop
//Depths
GLfloat  sunPosZ = -2.5,  CloudPosZ = -2;
bool RainStatus = TRUE;

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest

   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test

   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
   //glEnable(GL_LIGHTING);
}

void Clouds(GLfloat CloudPosX, GLfloat CloudPosY)
{
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(CloudPosX, CloudPosY, CloudPosZ);
    glutSolidSphere(cloudRad, 50, 50);

    glLoadIdentity();
    glTranslatef(CloudPosX+4*0.08, CloudPosY, CloudPosZ);
    glutSolidSphere(cloudRad, 50, 50);

    for (int i = 1; i<=3; i++)
    {
        glLoadIdentity();
        glTranslatef(CloudPosX+i*0.08, CloudPosY, CloudPosZ);
        glutSolidSphere(cloudRad, 50, 50);

        glLoadIdentity();
        glTranslatef(CloudPosX+i*0.09, CloudPosY+0.07, CloudPosZ);
        glutSolidSphere(cloudRad, 50, 50);

        glLoadIdentity();
        glTranslatef(CloudPosX+i*0.09, CloudPosY-0.07, CloudPosZ);
        glutSolidSphere(cloudRad, 50, 50);
        glLoadIdentity();
    }
}

void tree(GLfloat radius, GLfloat treePosX, GLfloat treePosY)
{

    glColor3f(0.28, 0.56, 0.0);
    glTranslatef(treePosX, treePosY, -5);
        glutSolidSphere(radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX, treePosY+2*radius, -5);
        glutSolidSphere(radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX-radius/2, treePosY+radius/2, -5);
        glutSolidSphere(7/6.0*radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX+radius/2, treePosY+radius/2, -5);
        glutSolidSphere(7/6.0*radius, 50, 50);

    glLoadIdentity();
        glTranslatef(treePosX-radius/2, treePosY-radius, -5);
        glutSolidSphere(3/2.0*radius, 50, 50);
    glLoadIdentity();
        glTranslatef(treePosX+radius/2, treePosY-radius, -5);
        glutSolidSphere(3/2.0*radius, 50, 50);

    glLoadIdentity();
    glBegin(GL_POLYGON);
        glVertex3f(treePosX+0.6*radius, treePosY, -5);
        glVertex3f(treePosX-0.6*radius, treePosY, -5);
        glVertex3f(treePosX-0.6*radius, treePosY-5*radius, -5);
        glVertex3f(treePosX+0.6*radius, treePosY-5*radius, -5);
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
void swan(GLfloat Size, GLfloat SwanX, GLfloat SwanY)
{
    glLoadIdentity();
    //glColor3f(0.33, 0.34, 0.3);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(SwanX+1.5*Size, SwanY+Size, -3);
    glVertex3f(SwanX-0.5*Size, SwanY+Size, -3);
    glVertex3f(SwanX, SwanY-Size, -3);
   // glEnd();

    glVertex3f(SwanX+0.01, SwanY-Size, -3);
    glVertex3f(SwanX+Size, SwanY+Size/4, -3);
    glVertex3f(SwanX+3*Size, SwanY+Size/4, -3);

    glVertex3f(SwanX-0.01, SwanY-Size, -3);
    glVertex3f(SwanX-Size, SwanY-Size, -3);
    glVertex3f(SwanX-Size, SwanY+2.5*Size, -3);

    glVertex3f(SwanX-Size, SwanY+2.5*Size, -3);
    glVertex3f(SwanX-1.3*Size, SwanY+2.51*Size, -3);
    glVertex3f(SwanX-1.5*Size, SwanY+1.5*Size, -3);
    glEnd();
}
void waterVapour()
{
  for(int j = 0; j<5; j++){
    for(int i = 0; i<4; i++)
    {
        glColor3f(0.31,0.26,1.0);
        glLoadIdentity();
        glTranslatef(WVx-i*0.05, WVy-j*0.08, -2.25);
        glutSolidSphere(0.009, 20, 20);
    }
  }
}
void RainDrops()
{
    for (int j = 0; j<10; j++)
    for (int i = 0; i<5; i++)
    {
          glColor3f(0.31,0.26,1.0);
        glLoadIdentity();
         glTranslatef(RDx+i*0.09, RDy-j*0.09, CloudPosZ);
        glutSolidSphere(0.01, 20, 20);
    }
}
void House(GLfloat Size, GLfloat HouseX, GLfloat HouseY)
{
    //WALLS
    glColor3f(0.3, 0.43, 0.6);
    glBegin(GL_POLYGON);
    glVertex3f(HouseX, HouseY, -4);
    glVertex3f(HouseX+1.2*Size, HouseY+0.4*Size, -4);
    glVertex3f(HouseX+1.2*Size, HouseY+1.4*Size, -4);
    glVertex3f(HouseX+0.5*Size, HouseY+1.53*Size, -4);
    glVertex3f(HouseX, HouseY+Size, -4);
    glVertex3f(HouseX-1.2*Size, HouseY+1.4*Size, -4);
    glVertex3f(HouseX-1.2*Size, HouseY+0.4*Size, -4);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(HouseX, HouseY, -4);
    glVertex3f(HouseX, HouseY+Size, -4);
    glEnd();

    //Front Roof
    glColor3f(1.0, 0.5, 0.3);
    glBegin(GL_POLYGON);
    glVertex3f(HouseX+0.1*Size, HouseY+0.9*Size, -3);
    glVertex3f(HouseX+0.8*Size, HouseY+1.53*Size, -3);
    glVertex3f(HouseX-0.7*Size, HouseY+1.9*Size, -3);
    glVertex3f(HouseX-1.35*Size, HouseY+1.34*Size, -3);
    glEnd();
    //Back Roof
    glBegin(GL_POLYGON);
    glVertex3f(HouseX+0.8*Size, HouseY+1.53*Size, -3);
    glVertex3f(HouseX+1.3*Size, HouseY+1.4*Size, -3);
    glVertex3f(HouseX+1.2*Size, HouseY+1.4*Size, -3);
    glVertex3f(HouseX+0.5*Size, HouseY+1.53*Size, -3);
    glEnd();



    //DOOR WINDOW
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(HouseX-0.25*Size, HouseY+0.65*Size, -1);
    glVertex3f(HouseX-0.25*Size, HouseY+0.75*Size, -1);
    glVertex3f(HouseX-0.44*Size, HouseY+0.80*Size, -1);
    glVertex3f(HouseX-0.44*Size, HouseY+0.70*Size, -1);
    glEnd();

    //DOOR
    glColor3f(0.42, 0.49, 0.56);
    glBegin(GL_POLYGON);
    glVertex3f(HouseX-0.2*Size, HouseY+0.15*Size, -3);
    glVertex3f(HouseX-0.2*Size, HouseY+0.85*Size, -3);
    glVertex3f(HouseX-0.5*Size, HouseY+0.95*Size, -3);
    glVertex3f(HouseX-0.5*Size, HouseY+0.25*Size, -3);
    glEnd();


    //Windows
    glBegin(GL_POLYGON);
    glVertex3f(HouseX-0.6*Size, HouseY+0.45*Size, -3);
    glVertex3f(HouseX-0.6*Size, HouseY+0.85*Size, -3);
    glVertex3f(HouseX-Size, HouseY+0.95*Size, -3);
    glVertex3f(HouseX-Size, HouseY+0.55*Size, -3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(HouseX+0.4*Size, HouseY+0.45*Size, -3);
    glVertex3f(HouseX+0.4*Size, HouseY+0.85*Size, -3);
    glVertex3f(HouseX+0.8*Size, HouseY+0.95*Size, -3);
    glVertex3f(HouseX+0.8*Size, HouseY+0.55*Size, -3);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(HouseX+0.6*Size, HouseY+0.50*Size, -3);
    glVertex3f(HouseX+0.6*Size, HouseY+0.90*Size, -3);
    glVertex3f(HouseX+0.4*Size, HouseY+0.65*Size, -3);
    glVertex3f(HouseX+0.8*Size, HouseY+0.75*Size, -3);

    glVertex3f(HouseX-0.8*Size, HouseY+0.50*Size, -3);
    glVertex3f(HouseX-0.8*Size, HouseY+0.90*Size, -3);
    glVertex3f(HouseX-0.6*Size, HouseY+0.65*Size, -3);
    glVertex3f(HouseX-Size, HouseY+0.75*Size, -3);
    glEnd();

    //DOOR Knob
    glLoadIdentity();
    glTranslatef(HouseX-0.45*Size, HouseY+0.60*Size, -3);
    glutSolidSphere(0.01, 10, 10);
}
void display() {
 {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   //SUN
   glLoadIdentity();                 // Reset the model-view matri
   glColor3f(1.0, 1.0, 0.0);
   glTranslatef(sunPosX, sunPoxY, sunPosZ);
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
      glVertex3f(2, -0.3, -6);
      glVertex3f(-2, 0.0, -6);
      glVertex3f(-2, -0.5, -6);
      glVertex3f(2, -0.5, -6);
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

}
   Clouds(Cloud1PosX, Cloud1PosY);
   Clouds(Cloud2PosX, Cloud2PosY);
   Clouds(Cloud3PosX, Cloud3PosY);
   trees();

   waterVapour();
   RainDrops();

   swan(0.05,swan1PosX , -0.7);
   swan(0.07, swan2PosX, -0.8);
   swan(0.06, swan3PosX, -0.6);

   House(0.35, 0.4, -0.35);
   glutSwapBuffers();

   Cloud1PosX+=dx;
   Cloud2PosX+=dx/2;
   Cloud3PosX+=dx;

   WVy+=dx;
   RDy -= 3*dx;

   swan1PosX-=dx;
   swan2PosX-=dx/2;
   swan3PosX-=dx/3;

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
