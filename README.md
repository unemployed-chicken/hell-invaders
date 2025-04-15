# hell-invaders
cpp project recreating space invaders


TODO:
	- Shipping Game:
		- Figure out how to ship to steam
	- Bug Fixes: 
		- Change to Props does not take effect until second play through.
		- Changing audio output crashes game?


Properties to be refactored
	- Add in a key to control demon attack chance
	- constexpr float skull_points{ base_demon_points * skull_multiplier }; (Remove this and move it to creation)
	- constexpr float fledge_points{ base_demon_points * fledgling_multiplier }; (remove this and move it to creation)
	- constexpr float scamp_points{ base_demon_points * scamp_multiplier }; (remove this and move it to creation)
	- constexpr float special_demon_points{ base_demon_points * special_demon_multiplier }; (remove this and move it to creation)

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