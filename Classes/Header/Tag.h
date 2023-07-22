#pragma once

////////////////////////////////
// PLTANK:					  //
// Category	0x01	00000001  //
// Test		0x02	00000010  //
//							  //
// PLBULLET:				  //
// Category	0x04	00000100  //
// Test		0x01	00000001  //
//							  //
// ENEMY:					  //
// Category	0x01	00000001  //
// Test		0x04	00000100  //
//							  //
// ENEMYBULLET:				  //
// Category	0x02	00000010  //
// Test		0x01	00000001  //
////////////////////////////////

// Infinity2 properties
const int WIDTH = 1000;
const int HEIGHT = 800;

//id tag
const int PLTANK = 1;
const int PLBULLET = 2;
const int ENEMY = 3;
const int ENEMYBULLET = 4;
const int MAP = 100;

//physics group tag
const int HITPL = 1;
const int HITENEMY = 2;

//the priority objects have
const int Z_MAP_LAYER = 0;
const int Z_TANK = 2;
const int Z_BULLET = 3;
const int Z_LABEL = 10;
const int Z_BUTTON = 10;