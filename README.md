# hell-invaders
cpp project recreating space invaders

Setting up a Mac Release File:
- Pull any necessary changes (Not sure how this will work the first time. Good Luck)
- Change base_path to new release number in Hell_Invaders.cpp
- Terminal > Run Task > Build Release
- Move newly compiled file to applications\Hell_Invaders_Mac_x.x.x 
	- This may require using the old folder and removing the old executable command file and replacing it with the new one then changing the folder name to the new version
- Change the icon (once you figure out how to change the icon)



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