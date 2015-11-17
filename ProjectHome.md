Please take a loot at the Overview Page in the list of featured pages for details on how to use the code and the work done

## Showcasing: Labelling of Body Parts ##
<table>
<tr>
<td>
<img width='320' height='240' src='http://opencv-kinect.googlecode.com/svn/wiki/Images/FinalLabelling.jpg' />
Final Renderring of Labelled Body Parts (OpenGL Based)<br>
</td>
<td><img width='320' height='240' src='http://opencv-kinect.googlecode.com/svn/wiki/Images/JointAdditions.jpg' />
Adding Missing Joints From First Rendering (MATLAB Based)<br>
</td>
<td>
<img width='320' height='240' src='http://opencv-kinect.googlecode.com/svn/wiki/Images/FirstRendering.jpg' />
First Renderring of Labelled Body Parts (MATLAB Based)<br>
</td>
</tr>
</table>

## Obtaining Depth Data From the Kinect ##
<a href='http://www.youtube.com/watch?feature=player_embedded&v=ryqCsjIXI34' target='_blank'><img src='http://img.youtube.com/vi/ryqCsjIXI34/0.jpg' width='425' height=344 /></a>

## Goals ##
  * To Filter the CMU Mocap Database for unique poses (for studies on Pose Estimation).
  * To build a complete Rendering Pipeline that can be used to label Vertices of Meshes belonging to characters (the labelling identifies what part of the body the Vertice Corresponds to)
  * To Enable Users to make a Different Labelling Scheme for their characters Easily (different labelling for a different purpose).
  * To use the trained Trees to generate Joint Proposals based on Depth Data from the Kinect

## Current State of Project ##
  * Assists in generating huge volumes of Data that will be used to train Randomised Forests
  * Provides Support for parsing a BVH file for Unique Poses
  * Provides Support for Viewing a pose (a character is made to adopt a pose by applying a bvh file to it) using opengl based Renderring.


## Current Repository ##

1- Code for Labelling MHX Meshes is Avaliable in Repository

2- Code for Exploring the Contents of a Directory for a file is avialable

3- Code for a BVH Reader is available on Repository

4- Code for Connecting to Kinect through CL/NUI (maybe if time permits)

This page is going to host code that makes use of OpenCV and is going to be incorporated into **Opencv**.
## Intended Repository ##
The source code shared here will enable users to
  * Interface with a **Kinect** Camera using no IDE based dependency. (Compilable through CMake)
  * Label Meshes Completely and Render in different Poses so Randomised trees can be trained on them

  * Train Randomised Forests on GPU (100 times faster! ) [future](future.md)
  * Provide Joint Proposals




Pre-Requisites to Using Code:

1- Dirent.h (Windows Based Users for using Explore Module)

2- Blender

3- MakeHuman

4- GLUT

5- CMake