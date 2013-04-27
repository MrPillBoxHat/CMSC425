#include <cstdlib>						// C++ standard definitions
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

int main(int argc, char **argv) 
{
	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Megaman CMSC451");

	// register callbacks
	glutReshapeFunc(); // window reshape callback
	glutDisplayFunc(); // (re)display callback
	glutIdleFunc(); // incremental update 
	glutIgnoreKeyRepeat(); // ignore key repeat when holding key down
	glutMouseFunc(); // process mouse button push/release
	glutMotionFunc(); // process mouse dragging motion
	glutKeyboardFunc(); // process standard key clicks
	glutSpecialFunc(); // process special key pressed
	glutSpecialUpFunc(); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}