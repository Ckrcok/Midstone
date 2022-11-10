#include <glew.h>
#include <iostream>
#include <SDL.h>
//#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h" // need to include Debug after Scene.h... why??
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Collision.h"


Scene0::Scene0() :sphere(nullptr), cube(nullptr), shader(nullptr), shaderCube(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
	trackball = new Trackball();

	//north limit
	Wall* wall_o1 = new Wall(Vec3(20.0f, 0.0f, -28.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o2 = new Wall(Vec3(20.0f, 0.0f, -24.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o3 = new Wall(Vec3(20.0f, 0.0f, -20.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o4 = new Wall(Vec3(20.0f, 0.0f, -16.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o5 = new Wall(Vec3(20.0f, 0.0f, -12.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o6 = new Wall(Vec3(20.0f, 0.0f, -8.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o7 = new Wall(Vec3(20.0f, 0.0f, -4.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o8 = new Wall(Vec3(20.0f, 0.0f, 0.0f),   0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o9 = new Wall(Vec3(20.0f, 0.0f, 4.0f),   0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o10 = new Wall(Vec3(20.0f, 0.0f, 8.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o11 = new Wall(Vec3(20.0f, 0.0f, 12.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o12 = new Wall(Vec3(20.0f, 0.0f, 16.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o13 = new Wall(Vec3(20.0f, 0.0f, 20.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	//south limit
	Wall* wall_o14 = new Wall(Vec3(-24.0f, 0.0f, -28.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o15 = new Wall(Vec3(-24.0f, 0.0f, -24.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o16 = new Wall(Vec3(-24.0f, 0.0f, -20.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o17 = new Wall(Vec3(-20.0f, 0.0f, -16.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o18 = new Wall(Vec3(-20.0f, 0.0f, -12.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o19 = new Wall(Vec3(-24.0f, 0.0f, -8.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o20 = new Wall(Vec3(-24.0f, 0.0f, -4.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o21 = new Wall(Vec3(-24.0f, 0.0f, 0.0f),   0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o22 = new Wall(Vec3(-24.0f, 0.0f, 4.0f),   0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o23 = new Wall(Vec3(-24.0f, 0.0f, 8.0f),   0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o24 = new Wall(Vec3(-24.0f, 0.0f, 12.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o25 = new Wall(Vec3(-24.0f, 0.0f, 16.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o26 = new Wall(Vec3(-24.0f, 0.0f, 20.0f),  0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//left limit
	Wall* wall_o27 = new Wall(Vec3(-18.0f, 0.0f, -30.0f), -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o28 = new Wall(Vec3(-14.0f, 0.0f, -30.0f), -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o29 = new Wall(Vec3(-10.0f, 0.0f, -30.0f), -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o30 = new Wall(Vec3(-6.0f, 0.0f, -30.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o31 = new Wall(Vec3(-2.0f, 0.0f, -30.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o32 = new Wall(Vec3(2.0f, 0.0f, -30.0f),   -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o33 = new Wall(Vec3(6.0f, 0.0f, -30.0f),   -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o34 = new Wall(Vec3(10.0f, 0.0f, -30.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o35 = new Wall(Vec3(14.0f, 0.0f, -30.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o36 = new Wall(Vec3(18.0f, 0.0f, -30.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_o37 = new Wall(Vec3(22.0f, 0.0f, -30.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//right limit

	Wall* wall_38 = new Wall(Vec3(-18.0f, 0.0f, 22.0f), -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_39 = new Wall(Vec3(-14.0f, 0.0f, 22.0f), -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_40 = new Wall(Vec3(-10.0f, 0.0f, 22.0f), -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_41 = new Wall(Vec3(-6.0f, 0.0f, 22.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_42 = new Wall(Vec3(-2.0f, 0.0f, 22.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_43 = new Wall(Vec3(2.0f, 0.0f, 22.0f),   -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_44 = new Wall(Vec3(6.0f, 0.0f, 22.0f),   -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_45 = new Wall(Vec3(10.0f, 0.0f, 22.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_46 = new Wall(Vec3(14.0f, 0.0f, 22.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_47 = new Wall(Vec3(18.0f, 0.0f, 22.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_48 = new Wall(Vec3(22.0f, 0.0f, 22.0f),  -90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//a room
	Wall* wall_a1 = new Wall(Vec3(4.0f, 0.0f, -28.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a2 = new Wall(Vec3(4.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a3 = new Wall(Vec3(4.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a4 = new Wall(Vec3(2.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_a5 = new Wall(Vec3(-2.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_a6 = new Wall(Vec3(-6.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_a7 = new Wall(Vec3(-8.0f, 0.0f, -28.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a8 = new Wall(Vec3(-8.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a9 = new Wall(Vec3(-8.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//b room
	Wall* wall_b0 = new Wall(Vec3(-12.0f, 0.0f, -28.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b1 = new Wall(Vec3(-12.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b2 = new Wall(Vec3(-12.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b3 = new Wall(Vec3(-16.0f, 0.0f, -16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b4 = new Wall(Vec3(-16.0f, 0.0f, -12.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b5 = new Wall(Vec3(-14.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b6 = new Wall(Vec3(-14.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b7 = new Wall(Vec3(-22.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b8 = new Wall(Vec3(-22.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b9 = new Wall(Vec3(-12.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b10 = new Wall(Vec3(-12.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b11 = new Wall(Vec3(-12.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b12 = new Wall(Vec3(14.0f, 0.0f, 0.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b13 = new Wall(Vec3(18.0f, 0.0f, 0.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b14 = new Wall(Vec3(22.0f, 0.0f, 0.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b15 = new Wall(Vec3(-14.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b16 = new Wall(Vec3(-18.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b17 = new Wall(Vec3(-22.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b18 = new Wall(Vec3(-12.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b19 = new Wall(Vec3(-12.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b20 = new Wall(Vec3(-12.0f, 0.0f, 12.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b21 = new Wall(Vec3(-12.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b22 = new Wall(Vec3(-12.0f, 0.0f, 20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);


	//c room
	Wall* wall_c1 = new Wall(Vec3(18.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c2 = new Wall(Vec3(14.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c3 = new Wall(Vec3(18.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c4 = new Wall(Vec3(14.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c5 = new Wall(Vec3(12.0f, 0.0f, -16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c6 = new Wall(Vec3(12.0f, 0.0f, -12.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c7 = new Wall(Vec3(12.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c8 = new Wall(Vec3(12.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c9 = new Wall(Vec3(12.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c10 = new Wall(Vec3(12.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c11 = new Wall(Vec3(12.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//d room

	Wall* wall_d1 = new Wall(Vec3(6.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d2 = new Wall(Vec3(2.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d3 = new Wall(Vec3(-2.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d4 = new Wall(Vec3(-6.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d5 = new Wall(Vec3(6.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d6 = new Wall(Vec3(2.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d7 = new Wall(Vec3(-2.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d8 = new Wall(Vec3(-6.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d9 = new Wall(Vec3(8.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d10 = new Wall(Vec3(8.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d11 = new Wall(Vec3(8.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d12 = new Wall(Vec3(8.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d13 = new Wall(Vec3(8.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d14 = new Wall(Vec3(-8.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d15 = new Wall(Vec3(-8.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d16 = new Wall(Vec3(-8.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d17 = new Wall(Vec3(-8.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d18 = new Wall(Vec3(-8.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//f room

	Wall* wall_f1 = new Wall(Vec3(6.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f2 = new Wall(Vec3(2.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f3 = new Wall(Vec3(-2.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f4 = new Wall(Vec3(-6.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f5 = new Wall(Vec3(8.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_f6 = new Wall(Vec3(8.0f, 0.0f, 20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_f7 = new Wall(Vec3(-8.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_f8 = new Wall(Vec3(-8.0f, 0.0f, 20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	theWalls.push_back(wall_o1);
	theWalls.push_back(wall_o2);
	theWalls.push_back(wall_o3);
	theWalls.push_back(wall_o4);
	theWalls.push_back(wall_o5);
	theWalls.push_back(wall_o6);
	theWalls.push_back(wall_o7);
	theWalls.push_back(wall_o8);
	theWalls.push_back(wall_o9);
	theWalls.push_back(wall_o10);
	theWalls.push_back(wall_o11);
	theWalls.push_back(wall_o12);
	theWalls.push_back(wall_o13);
	theWalls.push_back(wall_o14);
	theWalls.push_back(wall_o15);
	theWalls.push_back(wall_o16);
	theWalls.push_back(wall_o17);
	theWalls.push_back(wall_o18);
	theWalls.push_back(wall_o19);
	theWalls.push_back(wall_o20);
	theWalls.push_back(wall_o21);
	theWalls.push_back(wall_o22);
	theWalls.push_back(wall_o23);
	theWalls.push_back(wall_o24);
	theWalls.push_back(wall_o25);
	theWalls.push_back(wall_o26);
	theWalls.push_back(wall_o27);
	theWalls.push_back(wall_o28);
	theWalls.push_back(wall_o29);
	theWalls.push_back(wall_o30);
	theWalls.push_back(wall_o31);
	theWalls.push_back(wall_o32);
	theWalls.push_back(wall_o33);
	theWalls.push_back(wall_o34);
	theWalls.push_back(wall_o35);
	theWalls.push_back(wall_o36);
	theWalls.push_back(wall_o37);
	theWalls.push_back(wall_38);
	theWalls.push_back(wall_39);
	theWalls.push_back(wall_40);
	theWalls.push_back(wall_41);
	theWalls.push_back(wall_42);
	theWalls.push_back(wall_43);
	theWalls.push_back(wall_44);
	theWalls.push_back(wall_45);
	theWalls.push_back(wall_46);
	theWalls.push_back(wall_47);
	theWalls.push_back(wall_48);
		theWalls.push_back(wall_a1);
		theWalls.push_back(wall_a2);
		theWalls.push_back(wall_a3);
		theWalls.push_back(wall_a4);
		theWalls.push_back(wall_a5);
		theWalls.push_back(wall_a6);
		theWalls.push_back(wall_a7);
		theWalls.push_back(wall_a8);
		theWalls.push_back(wall_a9);
		theWalls.push_back(wall_b0);
		theWalls.push_back(wall_b1);
		theWalls.push_back(wall_b2);
		theWalls.push_back(wall_b3);
		theWalls.push_back(wall_b4);
		theWalls.push_back(wall_b5);
		theWalls.push_back(wall_b6);
		theWalls.push_back(wall_b7);
		theWalls.push_back(wall_b8);
		theWalls.push_back(wall_b9);
		theWalls.push_back(wall_b10);
		theWalls.push_back(wall_b11);
		theWalls.push_back(wall_b12);
		theWalls.push_back(wall_b13);
		theWalls.push_back(wall_b14);
		theWalls.push_back(wall_b15);
		theWalls.push_back(wall_b16);
		theWalls.push_back(wall_b17);
		theWalls.push_back(wall_b18);
		theWalls.push_back(wall_b19);
		theWalls.push_back(wall_b20);
		theWalls.push_back(wall_b21);
		theWalls.push_back(wall_b22);
		theWalls.push_back(wall_c1 );
		theWalls.push_back(wall_c2 );
		theWalls.push_back(wall_c3 );
		theWalls.push_back(wall_c4 );
		theWalls.push_back(wall_c5 );
		theWalls.push_back(wall_c6);
		theWalls.push_back(wall_c7); 
		theWalls.push_back(wall_c8); 
		theWalls.push_back(wall_c9); 
		theWalls.push_back(wall_c10 );
		theWalls.push_back(wall_c11);
		theWalls.push_back(wall_d1);
		theWalls.push_back(wall_d2);
		theWalls.push_back(wall_d3);
				theWalls.push_back(wall_d4);
		theWalls.push_back(wall_d5);
		theWalls.push_back(wall_d6);
		theWalls.push_back(wall_d7);
		theWalls.push_back(wall_d8);
		theWalls.push_back(wall_d9);
		theWalls.push_back(wall_d10);
		theWalls.push_back(wall_d11);
		theWalls.push_back(wall_d12);
		theWalls.push_back(wall_d13);
		theWalls.push_back(wall_d14);
		theWalls.push_back(wall_d15);
		theWalls.push_back(wall_d16);
		theWalls.push_back(wall_d17);
		theWalls.push_back(wall_d18);
		theWalls.push_back(wall_f1);
		theWalls.push_back(wall_f2);
		theWalls.push_back(wall_f3);
		theWalls.push_back(wall_f4);
		theWalls.push_back(wall_f5);
		theWalls.push_back(wall_f6);
		theWalls.push_back(wall_f7);
		theWalls.push_back(wall_f8);
		


}

Scene0::~Scene0()
{
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
	if (trackball) delete trackball;
}

bool Scene0::OnCreate()
{

	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);

	camera = new CameraActor(Vec3(0.0f, 10.0f, 0.0f), nullptr);
	camera->OnCreate();
	skull = new Actor(nullptr);
	skull->SetMesh(new Mesh(nullptr, "meshes/wallTest3.obj"));
	skull->GetMesh()->OnCreate();
	skull->SetTexture(new Texture());
	skull->GetTexture()->LoadImage("textures/white_sphere.png");
	skull->OnCreate();

	for (Wall* wall : theWalls) {
		wall->OnCreate();
	}

	shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}


	lightPos[0] = Vec3(3.0f, 0.0f, -6.5f);
	lightPos[1] = Vec3(-3.0f, 0.0f, -6.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -6.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -6.5f);
	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.0f, 0.6f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.0f, 0.0f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];
	return true;
}

void Scene0::OnDestroy() {
	Debug::Info("Deleting assets Scene2: ", __FILE__, __LINE__);

	if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}

	skull->OnDestroy();
	delete skull;

	shader->OnDestroy();
	delete shader;

}
void Scene0::HandleEvents(const SDL_Event& sdlEvent) {

	camera->HandleEvents(sdlEvent);

	switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_F) {//LEFT
				//skull->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, 0.0f)));
				//->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));
				//skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(-90, Vec3(0.0f, 0.0f, -1.0f)));
				//skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));
			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_H) {//RIGHT
				skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f,1.0f)));

			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_T) {//UP
				skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 1.0f, 0.0f)));

			//skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 1.0f, 0.0f)));

			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_G) {//DOWN
				skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, -1.0f, 0.0f)));

			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Y) {//BEHIND
				skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, -1.0f)));

			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_U) {//FRONT
				skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));

			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_K) {//CENTER OBJECT
				skull->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, 0.0f)));
			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_L) {//ROTATE OBJECT 10 DEGREES
			
				skull->SetModelMatrix(skull->GetModelMatrix() *=
					MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)));

			//skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(10.0f,Vec3(0.0f,0.0f, 1.0f)));

			}
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_O) {//MOVE 10 UNITS
				skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));

			}
			
			break;
	}
}

void Scene0::Update(const float deltaTime) {
	totalTime += deltaTime;
	skull->GetPosition().print("Testing walls pos");
	//theWalls[0]->GetPosition().print("Wall");
	bool isTouching = false;
	//theWalls[26]->GetPosition().print("Wall 027 pos");
}

void Scene0::Render() const {

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->Render();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//-----------------------
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());
	//-----------------------
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, skull->GetTexture()->getTextureID());
	//skull->GetMesh()->Render(GL_TRIANGLES);
	for (Wall* wall : theWalls) {
		wall->Render();
	}
	theWalls[26]->Render();
	glUseProgram(0);
}




