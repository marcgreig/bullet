#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	//walls
	PhysBody3D* pb_wall1;
	Cube wall1;

	PhysBody3D* pb_wall2;
	Cube wall2;

	PhysBody3D* pb_wall3;
	Cube wall3;

	PhysBody3D* pb_wall4;
	Cube wall4;

	PhysBody3D* pb_wall5;
	Cube wall5;

	PhysBody3D* pb_wall6;
	Cube wall6;

	PhysBody3D* pb_wall7;
	Cube wall7;

	PhysBody3D* pb_wall8;
	Cube wall8;
};
