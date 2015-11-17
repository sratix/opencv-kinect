# Structure #

Documentation for the Class

Explains
  * Class variables
  * public access functions

## Brief ##

_Class is made to store a single Structure._
_One may augment the class with additional functions that can be performed on the structure_

## Class Variables ##

_Listed below are the variables used by this class. These variables encode all important information related to the Structure_

> _Notes regarding variables used._

> _1- part is an array of type 'SubStructure' which is used to store all joints of the Structure being defined in the BVH_

> _2- totalParts is used to store the total amount of parts that are present in the Structure once the file has been read_

## Public Functions ##


### Constructors and Destructors ###


_Default constructor for the class._

_Contains no parts and other variables initialized to default or null_

```
Structure();
```

_Standard destructor for the class_

_Clears all vectors used to free allocated space_

```
~Structure();
```

### Display ###
_Display function for the class data_

_Prints the complete Structure with all the joints to the console_

```
void print();
```

_Adds a component to the current Structure_

_Also increments the counter for commulative parts of the structure_

`void printToFile(std::string fileName);`

### Mutator ###

_Mutator for specifying the parent joint of a current Joint_

_Joint to whom a parent is being assigned must exist_

_The variable parentIndex must be a valid joint or -1 indicating it is the root joint_

```
void setParent(int joint,int parentIndex);
```

_Mutator for specifying the offset for a joint_

_Joint to whom a offset is being assigned must exist_

_Offset being assigned must have three values_

```
void setOffset(int joint,std::vector<float> offset);
```

_Mutator for specifying the end points of the joints which are the last in a chain_

_The variable userEndsiteCoordinates must have 3 float values to maintain integrity of data_

_the variable partNumber must have indicate a valid part ( non negative and within the parts defined )_

_The variable partNumber must not point to a part that is the parent of another Part._
```
void setEndPoints(int partNumber,std::vector<float> userEndsiteCoordinates);
```

### Accessors ###


_Accessor for obtaining the name of a specific part_

_The variable joint must refer to a valid joint number_
```
std::string getPartName(int joint);
```

_Accessor for obtaining the name of a specific part_

_The variable joint must refer to a valid joint number_

_In case of invalid Joint entry the function will return -2_

```
int getParentJointIndex(int joint);
```

_Accessor for obtaining SubStructure offsets from parent of a particular joint_

_the variable partNumber must have indicate a valid part ( non negative and within the parts defined )_

```
std::vector<float> getSubStrcutureOffset(int joint);
```

_Accessor for obtaining the total Number of Channels for the data in the structure_

```
int getTotalNumberOfChannels();
```

_Accessor for obtaining the total parts in the structure_

_Mostly used in making loops over all joints in the structure_

```
int getTotalParts();
```



_Function for obtaining the Min Coordinate in either of X Y or Z
Direction for the entire structure_

_The term varibale must contain only 'X' 'Y' or 'Z'_

_Any other value of term Variable will return 0.0_

```
float getMinCoordinate(std::string term);
```

_Function for obtaining the Max Coordinate in either of X Y or Z Direction for the entire structure_

_The term varibale must contain only 'X' 'Y' or 'Z'_

_Any other value of term Variable will return 0.0_

```
float getMaxCoordinate(std::string term);
```

### Additional Functions ###

_To augment the Structure with a new component related to the current structure_

```
void addSubStructure(SubStructure aSubStructure);
```

_A 2D orthographic Visualization of the entire Structure as described by its current Offsets_

_Visualization may be improved by using PCL (Point Cloud Library)_

_Centers the Structure_

_does not make use of Translation_

```
cv::Mat visualizeStructure();
```