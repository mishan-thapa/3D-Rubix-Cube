#include <GL/freeglut.h>
#include <vector>
#include<iostream>
using namespace std;


//global variables start

struct cube_rotate{

  GLfloat angle, x, y, z;

};

GLfloat angle, fAspect, cube_size;
GLint rot_x, rot_y, crement, x_i, x_k, y_i, y_k, z_i, z_k, gap,count=0;
vector<cube_rotate> cube_rotations[3][3][3];
//global variables end

void load_visualization_parameters(void);

//delay garney function start
void delay(int v)
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glRectf(-90.0f, 90.0f, -10.0f, 10.0f);
	glutPostRedisplay();
	glutTimerFunc(1000, delay, v);
}
//delay garney function end

//try wala start   rotation wala
void apply_rotation(GLfloat angle){

  vector<cube_rotate> face[3][3];
  int index;
  cube_rotate rotation;

  // copy face to be rotated
  // apply rotation to face
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      index = 2 - j%3;

      if(x_i == x_k){
	rotation = {angle, 1.0, 0.0, 0.0};
	cube_rotations[x_k][i][j].push_back(rotation);
      }

      if(y_i == y_k){
	rotation = {angle, 0.0, 1.0, 0.0};
	cube_rotations[j][y_k][i].push_back(rotation);
      }

      if(z_i == z_k){
	rotation = {-1 * angle, 0.0, 0.0, 1.0};
  cube_rotations[j][i][z_k].push_back(rotation);
      }

   

    }



}   
//try wala end  rotation wala

/*
void apply_rotation(GLfloat angle){

  vector<cube_rotate> face[3][3];
  int index;
  cube_rotate rotation;

  // copy face to be rotated
  // apply rotation to face
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      index = 2 - j%3;

      if(x_i == x_k){
	rotation = {angle, 1.0, 0.0, 0.0};
	face[index][i] = cube_rotations[x_k][i][j];
      }

      if(y_i == y_k){
	rotation = {angle, 0.0, 1.0, 0.0};
	face[index][i] = cube_rotations[j][y_k][i];
      }

      if(z_i == z_k){
	rotation = {-1 * angle, 0.0, 0.0, 1.0};
	face[index][i] = cube_rotations[j][i][z_k];
      }

      face[index][i].push_back(rotation);

    }

  // copy back rotated face
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      if(x_i == x_k)
	cube_rotations[x_k][i][j] = face[i][j];

      if(y_i == y_k)
	cube_rotations[j][y_k][i] = face[i][j];

      if(z_i == z_k)
	cube_rotations[j][i][z_k] = face[i][j];
    } 

}   */


//reset face selection start
void reset_selected_face(){
count=1;
  x_i = 0;
  x_k = 2;
  y_i = 0;
  y_k = 2;
  z_i = 0;
  z_k = 2;

}
//reset face selection end

//set camera start
void set_camera()
{

  gluLookAt(0,80,200, 0,0,0, 0,1,0);

}
//set camera end

//draw_cube start
void draw_cube(int x, int y, int z)
{
	
  vector<cube_rotate> lrot = cube_rotations[x][y][z];

  glPushMatrix();

  // translate to final position
  glTranslatef((x - 1) * cube_size + x * 1, (y - 1) * cube_size + y * 1, (z - 1) * cube_size + z * 1);   //gap=1
cout<<"x"<<(x - 1) * cube_size + x * 1<< "y"<<(y - 1) * cube_size + y * 1<<"z"<< (z - 1) * cube_size + z * 1;

  // rotate cube to correct position
  
  for(int i = lrot.size() - 1; i >= 0; --i){
  
    glRotatef(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);
	//cout<<lrot.size();
	} 

  glColor3f(0.0f, 0.0f, 1.0f);     //blue
  glBegin(GL_QUADS);  // front
   // glNormal3f(0.0, 0.0, 1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

   glColor3f(1.0f, 0.0f, 1.0f);     //magenta
  glBegin(GL_QUADS);  // back
   // glNormal3f(0.0, 0.0, -1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 0.0f, 0.0f);    //red
  glBegin(GL_QUADS);  // left
   // glNormal3f(-1.0, 0.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();
  
  glColor3f(0.0f, 1.0f, 0.0f);     //green
  glBegin(GL_QUADS);  // right
    //glNormal3f(1.0, 0.0, 0.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);       //white
  glBegin(GL_QUADS);  // top
   // glNormal3f(0.0, 1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f);      //yellow
  glBegin(GL_QUADS);  // bottom
    //glNormal3f(0.0, -1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();    

  glPopMatrix();

}
//draw_cube end

// draw_func start

void draw_func(void)
{

//  int x = -cube_size, y = -cube_size, z = -cube_size;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // reset transformations
  glLoadIdentity();

  // set camera position
  set_camera();

  // apply visualization transformations
  glRotatef(rot_x, 1.0, 0.0, 0.0); // rotate in y axis
  glRotatef(rot_y, 0.0, 1.0, 0.0); // rotate in x axis

  for(int i = 0; i < 3; ++i) // step through x axis
    for(int j = 0; j < 3; ++j) // step through y axis
      for(int k = 0; k < 3; ++k) { // step through z axis

	// draw a single cube
	draw_cube(i, j, k);
	

      }

  // flush opengl commands
  glutSwapBuffers();

}

//draw_func end

//load_visualization_paramenter start
void load_visualization_parameters(void)
{
  // specify projection coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // specify projection perspective
  gluPerspective(angle,fAspect,0.4,500);

  // init model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // specify observer and target positions
  set_camera();
}
//load_blah blah end




//reshape start

void reshape_func(GLsizei w, GLsizei h)
{
  // prevents division by zero
  if ( h == 0 ) h = 1;

  // viewport size
  glViewport(0, 0, w, h);

  // aspect ratio
  fAspect = (GLfloat)w/(GLfloat)h;

  load_visualization_parameters();
} 
//reshape end


//init_func start
void init_func (void)
{ 

  // init parameters
  cube_size = 30.0; // cuboid size
  rot_x = 0.0; // view rotation x
  rot_y = 0.0; // view rotation y
  crement = 5; // rotation (in/de)crement
  //gap = 1;
  
  // initialize cuboid rotations

  
  // black background
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  

  // enable depth buffering
  glEnable(GL_DEPTH_TEST);

  angle=45;

} 
//init_func end
//key press wala start

void keyboard_func(unsigned char key, int x, int y)
{

  switch(key) {

   
    // view rotation
   

    // cube movements

    // select cube face
    // x-axis faces
    case 'I':
    case 'i':
      reset_selected_face();
      x_i = 0;
      x_k = 0;
      break;

    case 'O':
    case 'o':
      reset_selected_face();
      x_i = 1;
      x_k = 1;
      break;

    case 'P':
    case 'p':
      reset_selected_face();
      x_i = 2;
      x_k = 2;
      break;

    // y-axis faces
    case 'J':
    case 'j':
      reset_selected_face();
      y_i = 0;
      y_k = 0;
      break;

    case 'K':
    case 'k':
      reset_selected_face();
      y_i = 1;
      y_k = 1;
      break;

    case 'L':
    case 'l':
      reset_selected_face();
      y_i = 2;
      y_k = 2;
      break;

    // z-axis faces
    case 'M':
    case 'm':
      reset_selected_face();
      z_i = 0;
      z_k = 0;
      break;

    case 'N':
    case 'n':
      reset_selected_face();
      z_i = 1;
      z_k = 1;
      break;

    case 'B':
    case 'b':
      reset_selected_face();
      z_i = 2;
      z_k = 2;
      break;

    // move selected face
    case 'Q': // counter-clockwise
    case 'q':
    	if(count==1){
		apply_rotation(-90);		
		}else{
			apply_rotation(0);
		}
      
      break;

    case 'E': // clockwise
    case 'e':
      if(count==1){
		apply_rotation(90);		
		}else{
			apply_rotation(0);
		}
      break;

    // end of cube movements

    default:
      break;

  }

  glutPostRedisplay();

}

//key press wala end

//special key wala use start
void ProcessSpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)   //use up key     but boxes are moving down
    {
         rot_x = (rot_x + crement) % 360;
    }
    if (key == GLUT_KEY_DOWN)   //down key   
    {
         rot_x = (rot_x - crement) % 360;
    }
    if (key == GLUT_KEY_LEFT)
    {
         rot_y = (rot_y + crement) % 360;
    }
    if (key == GLUT_KEY_RIGHT)
    {
         rot_y = (rot_y - crement) % 360;
    }

    glutPostRedisplay();
}

//special key wala use end


//mouse wala kam grney start
void mouse_func(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN) {  // Zoom-in     
	    if (angle >= 10) angle -= 5;         //distance = cot(angle)  jati distance badcha teti angle ghatdai jancha nita
    }
  if (button == GLUT_RIGHT_BUTTON)
    if (state == GLUT_DOWN) {  // Zoom-out
	    if (angle <= 130) angle += 5;
    }
  load_visualization_parameters();
  glutPostRedisplay();
} 
//mouse wala kam grney end

//main wala start

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);    //GLUT_DOUBLE | 
  glutInitWindowPosition(80,80);
  glutInitWindowSize(1050,600);
  glutCreateWindow("Rubix Cube version 1.9");
  init_func();
  //callback functions
  glutDisplayFunc(draw_func);
  glutReshapeFunc(reshape_func);
  glutMouseFunc(mouse_func);
  glutKeyboardFunc(keyboard_func);
  glutSpecialFunc(ProcessSpecialKeys);
  
  
  glutMainLoop();
} 


//main wala end
