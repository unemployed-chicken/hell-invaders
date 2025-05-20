# hell-invaders
cpp project recreating space invaders


Steps for Building Release Version on Windows:
	- Build Release version using x64
		- The release folder can be found at hell-invaders\x64\Release
	- Copy over the following files into the release folder
		- hell-invaders\audio\Lean\audio
		- hell-invaders\textures\Lean\textures
		- hell-invaders\properties
			- Make sure High-score and user_defined_properties.json are zero'ed out
	- Move release folder and rename to  Hell_Invaders_Win_x.x.x



/*
* Workflow for Properties: 
*    Created on GameMap where it reads the predefined values and stores those that exists.
*    If They do not exist, the vaules are grabbed from default.
*    If a user wants to change the values, they can set an individual one in the document. 
*        - If all changes are confirmed, they written to the properties.json file.
*               - Properties object is recreated from scratch. (see above workflow)
*        - If a user decides to cancel their changes, they can cancel. The file is not saved. 
*               - Properties object is recreated from scratch.
*    A user can reset all custom changes by restoreDefaults(). 
*        - Properties object is recreated from scratch.
*    
*/