##########
# Blender Script 
# To be Used with Imported Obj Mesh with Groups Option Checked

# Inputs Needed:
# 1 - Character Name (to be used for distinguishing between differnet Characters)
# 2 - path (to be used for writing output files )

# Outputs : 
# 1 - _BrokenMesh.coords            ( contains the Coordinates of the Mesh in T-Stance Pose) 
# 2 - _BrokenMesh.labels            ( contais the Label for each Coordinate. A Label tells us which body part this pixel belongs to )
# 3 - _BrokenMesh.faces             ( contains the data for which coordinates to use to make faces that draw the whole character
# 4 - _BodyPartsSchematic.labels    ( contains the names of all the body parts in the mesh )

# Author
# Mohammad Haris Baig
# baig.haris@gmail.com

# Script August: 2011
# Revision Number : 2


## Importing Data From Blender and OS 
import bpy
import os

## Setting the Paths

# 'rootPath' refers to the Directory Where you want to output the Files
rootPath = "D:\\GSOC-Kinect\\Characters\\GirlTest"
# 'newDirectory adds a subdirectory in the Root Directory so that all the Different Files for a character can be put in the same directory yet be organized
# 'newDirectory' creates a directory called '
newDirectory = rootPath + "\\Mesh\\"
# 'characterName is what you want to name your Character. 
# all files generated come with the characterName as the prefix to their name. This allows for easy reading
characterName = 'GirlOne'

# Creating New Directory if it does not exist
if not os.path.exists(newDirectory):
    os.makedirs(newDirectory)    

# Initializing file writers
writeVertices = open(newDirectory +characterName + "_BrokenMesh.coords","w")
writeLabels = open(newDirectory +characterName+ "_BrokenMesh.labels","w")
writePartFaces = open(newDirectory+characterName+"_BrokenMesh.faces","w")
writePartLabels = open(newDirectory+characterName+"_BodyPartsSchematic.labels","w")

# Initializing Structures to hold data that we are going to read and subsequently write
bodyPartsCoordinates = [];
bodyPartsCoordinatesLabels=[];
bodyPartsFaces = [];


# Reading Data From Meshes
# Each Character has been designed as combination of Mesh Parts.
# Each Part has a fixed number of Coordinates that are deformed to make different Characters.

# Writing Known Data
# 1- the number of different component Meshes that make up a character.


# Writing number of component Meshes that make up this character
# It is always 266
writePartLabels.write("%d\n"%len(bpy.data.meshes))


# Data is read Part by Part, first the mesh for a part is completly read and then the next one is read
for aMesh in range(0,len(bpy.data.meshes)):

    # Initializing a Character Part
    characterPart = bpy.data.meshes[aMesh]    
    
    if (characterPart.name != 'Cube'):
    
        # Writing Mesh name to the file
        writePartLabels.write("%s\n"%characterPart.name)
    
        # Reading all coordinates of the current Part and appending them to their respective storage structure.                          
        # Reading all labels of coordinates of the current Part and appending them to their respective storage structure.                          
        for aVertice in characterPart.vertices:
            bodyPartsCoordinates.append(aVertice.co)
            bodyPartsCoordinatesLabels.append(characterPart.name)

        # Reading all faces of the current Part and appending them to their respective storage structure.                               
        for aFace in characterPart.faces:        
            bodyPartsFaces.append(aFace.vertices)
        
        # Deleting the meory we got allocated in this run
    del characterPart
        
               
# Closing the file Part Labels as it has  been written
writePartLabels.close();
   
# Writing number of Vertices that make up this character
# It is always 17735
writeVertices.write("%d\n"%len(bodyPartsCoordinates))

# Writing number of Labels for the coordinates that make up this character
# It is always 17735
writeLabels.write("%d\n"%len(bodyPartsCoordinatesLabels))

# Writing number of Faces that make up this character
writePartFaces.write("%d\n"%len(bodyPartsFaces))

## Output the Data stored in the files

# Single for loop used as both have same number of elements
for aCoordinate in range(0,len(bodyPartsCoordinates)):
    # The vertices are in the order of X Y Z and so are written that way.
    writeVertices.write("%f %f %f\n" %(bodyPartsCoordinates[aCoordinate][0],bodyPartsCoordinates[aCoordinate][1],bodyPartsCoordinates[aCoordinate][2]))
   
    writeLabels.write("%s\n"%bodyPartsCoordinatesLabels[aCoordinate])

# Closing the Files that have been completed
writeLabels.close()
writeVertices.close()


# Writing data for faces used for rendering the mesh                   
for aFace in bodyPartsFaces:
    writePartFaces.write("%d %d %d %d\n"%(aFace[0],aFace[1],aFace[2],aFace[3]))

# Closing the file as all data has been written to it
writePartFaces.close()  

# Emptying out the data structures that we constructed
del bodyPartsFaces;
del bodyPartsCoordinates;
del bodyPartsCoordinatesLabels
