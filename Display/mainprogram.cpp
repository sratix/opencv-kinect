/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Basic Shapes" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <cstdlib> 
#include <vector>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "SimpleReader.h"


using namespace std;

std::vector<std::vector<float> > makeColors()
{
	std::vector<std::vector<float> > theColors;
	
	std::vector<float > aColor;
	
	// Color 1
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 2
	aColor.push_back(0);
	aColor.push_back(1);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 3
	aColor.push_back(0);
	aColor.push_back(1);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 4
	aColor.push_back(1);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 5
	aColor.push_back(1);
	aColor.push_back(0);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 6
	aColor.push_back(1);
	aColor.push_back(1);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 7
	aColor.push_back(1);
	aColor.push_back(1);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 8
	aColor.push_back(0.5);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 9
	aColor.push_back(0.5);
	aColor.push_back(0);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 10
	aColor.push_back(0.5);
	aColor.push_back(0.5);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 11
	aColor.push_back(0.5);
	aColor.push_back(0.5);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 12
	aColor.push_back(0);
	aColor.push_back(0.5);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 13
	aColor.push_back(0);
	aColor.push_back(0.5);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 14
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 15
	aColor.push_back(0.75);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 16
	aColor.push_back(0.75);
	aColor.push_back(0);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 17
	aColor.push_back(0.25);
	aColor.push_back(0.25);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 18
	aColor.push_back(0.75);
	aColor.push_back(0.75);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 19
	aColor.push_back(0);
	aColor.push_back(0.75);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 20
	aColor.push_back(0);
	aColor.push_back(0.75);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 21
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 22
	aColor.push_back(0.25);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 23
	aColor.push_back(0.85);
	aColor.push_back(0);
	aColor.push_back(0.35);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 24
	aColor.push_back(0.65);
	aColor.push_back(0.35);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 25
	aColor.push_back(0.25);
	aColor.push_back(0.5);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 26
	aColor.push_back(0);
	aColor.push_back(0.25);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 27
	aColor.push_back(1);
	aColor.push_back(0.25);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 28
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 29
	aColor.push_back(0.75);
	aColor.push_back(0);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	
	// Color 30
	aColor.push_back(0);
	aColor.push_back(0.5);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 31
	aColor.push_back(0.25);
	aColor.push_back(0);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();
	
	return theColors;
}

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
}

int findLabelling(std::string aLabel,std::vector<std::string> theLabelling)
{
	int counter = 0;	
	bool found= false;
	while (counter< theLabelling.size() && found==false)
	{
		if (theLabelling[counter].compare(aLabel)==0)
		{
			return counter;
		}
		counter++;
	}
	return -1;
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {

	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(50.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}


int getPatchColor(std::vector<int> colorDecision)
{
	
	std::vector<int> values;
	std::vector<int> counters;
	bool found = false;
	
	// Code to get Counters and values stack set
	for (int check=0; check<colorDecision.size();check++)
	{
		for (int find=0; find<values.size();find++)
		{
			if (values[find] == colorDecision[check])
			{
				found = true;
				counters[find] = counters[find]+1;
				
				//std::cout<<"Value: "<<values[find]<<" contains " << counters[find]<<" at "<<find<<std::endl;				
			}
		}
		
		if (found==false)
		{
			values.push_back(colorDecision[check]);
			counters.push_back(1);
		}
		
		found= false;
	}
	
	//std::cout<<"values Size: "<<values.size()<<std::endl;
	

	if (values.size()==1)
	{		
		//std::cout<<"Returning: "<<values[0]<<std::endl;	
		return values[0];
	}
	else if (values.size()== 2)
	{		
		if (counters[0] ==3)
		{
			return values[0];
		}
		else if (counters[1]==3)
		{
			return values[1];			
		}
		else
		{
			// its a tie
			std::cout<<"Its a tie between two colors with equal counters\n";
			return values[1];
		}
	}
	else if (values.size()==3)
	{
		if (counters[0]==2)
		{
			return values[0];
		}
		else if (counters[1]==2)
		{
			return values[1];
		}
		else if (counters[2]==2)
		{
			return values[2];
		}
	}
	else
	{
		std::cout<<"All Four vertices have different Labels so Im Screwed\n";
		return values[3];
	}
	return 1;
	
}

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	
	// Reading Coordinates to draw
	SimpleReader aReader;
	
	// First Step: Set paths to all key files generated by script using .obj Mesh 	
	std::string pathCoordinates = "D:\\GSOC-Kinect\\Rendering\\GirlOne_MHX_Mesh.coords";
	std::string pathLabels = "D:\\GSOC-Kinect\\Rendering\\New_MHX_Mesh.labels";
	std::string pathFaces = "D:\\GSOC-Kinect\\Rendering\\retargettedfaces.faces";
	
	std::vector<std::vector<float> > theCoordinates =  aReader.readCoordinates(pathCoordinates);
	std::vector<std::vector<int> > theFace = aReader.readFaces(pathFaces);
	std::vector<std::string> theLabels = aReader.readLabels(pathLabels);
	
	std::vector<std::vector<int> > theColors;
	std::vector<std::string > theLabelling;
	
	for (int makeColor = 0; makeColor<theLabels.size();makeColor++)
	{
		theCoordinates[makeColor][2] = theCoordinates[makeColor][2]-25;
		theCoordinates[makeColor][1] = theCoordinates[makeColor][1]+5;
		
		if (findLabelling(theLabels[makeColor],theLabelling) == -1)
		{
			theLabelling.push_back(theLabels[makeColor]);
						
		}		
	}
	
	
	theColors = makeColors();
	// OPEN GL SETTINGS
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	
	std::cout<<"Size is: "<<theCoordinates.size()<<std::endl;
	 
	std::vector<float> colorDecision;
	int colorIndex = 0;
	
	
	for (int aFace = 0; aFace<theFace.size(); aFace++)
	{
		
		colorDecision.push_back(findLabelling(theLabels[theFace[aFace][0]],theLabelling));		
		colorDecision.push_back(findLabelling(theLabels[theFace[aFace][1]],theLabelling));		
		colorDecision.push_back(findLabelling(theLabels[theFace[aFace][2]],theLabelling));		
		colorDecision.push_back(findLabelling(theLabels[theFace[aFace][3]],theLabelling));
				
		colorIndex = getPatchColor(colorDecision);
		colorDecision.clear();
		
		glColor3f(theColors[colorIndex][0],theColors[colorIndex][1],theColors[colorIndex][2]); 
		glVertex3f(theCoordinates[theFace[aFace][0]][0], theCoordinates[theFace[aFace][0]][1], theCoordinates[theFace[aFace][0]][2]);		
		//std::cout<<theLabels[(theFace[aFace][0])]<<std::endl;
				
		//glColor3f(theColors[colorIndex][0],theColors[colorIndex][1],theColors[colorIndex][2]); 
		glVertex3f(theCoordinates[theFace[aFace][1]][0], theCoordinates[theFace[aFace][1]][1], theCoordinates[theFace[aFace][1]][2]);		
		//std::cout<<theLabels[(theFace[aFace][1])]<<std::endl;
		
		
		//glColor3f(theColors[colorIndex][0],theColors[colorIndex][1],theColors[colorIndex][2]); 
		glVertex3f(theCoordinates[theFace[aFace][2]][0], theCoordinates[theFace[aFace][2]][1], theCoordinates[theFace[aFace][2]][2]);		
		//std::cout<<theLabels[(theFace[aFace][2])]<<std::endl;
		
		
		//glColor3f(theColors[colorIndex][0],theColors[colorIndex][1],theColors[colorIndex][2]); 
		glVertex3f(theCoordinates[theFace[aFace][3]][0], theCoordinates[theFace[aFace][3]][1], theCoordinates[theFace[aFace][3]][2]);
		//std::cout<<theLabels[(theFace[aFace][3])]<<std::endl<<std::endl;
			
		
	}
	
	
	glEnd(); //End triangle coordinates
	
	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
	
	//Initialize GLUT
	//glutInit(&argc, argv);
	
	
	
	// Declaring screen size
	int width = 640;
	int height = 480;
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(width, height); //Set the window size
	
	//Create the window
	glutCreateWindow("Mesh");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.
	
	return 0; //This line is never reached
}









