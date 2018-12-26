#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(95,95,-50));
	App->camera->LookAt(vec3(15, -8, 57));
	
	
	//Goal
	goal.radius = 5.0f;
	goal.SetPos(35, 3 , 100);
	goal.color = Blue;
	pb_goal = App->physics->AddBody(goal, 1.0f);

	pb_goal->collision_listeners.add(this);

	//Map Door

	pivot.radius = 2.0f;
	pivot.height = 4.0f;
	pivot.SetPos(17,2,78);
	pb_pivot = App->physics->AddBody(pivot, 0.0f);

	door1.size = { 12, 4, 4 };
	door1.SetPos(17, 2, 69);
	pb_door1 = App->physics->AddBody(door1, 99999.0f);

	door2.size = { 12, 4, 4 };
	door2.SetPos(17, 2, 87);
	pb_door2 = App->physics->AddBody(door2, 99999.0f);

	App->physics->AddConstraintHinge(*pb_door1, *pb_pivot, vec3(-9, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 1, 0));

	App->physics->AddConstraintHinge(*pb_door2, *pb_pivot, vec3(9, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 1, 0));

	//Map Walls
	wall1.size = { 30, 8, 4 };
	wall1.SetPos(0, 4, 0);
	pb_wall1 = App->physics->AddBody(wall1, 0.0f);

	wall2.size = { 4, 8, 60 };
	wall2.SetPos(17, 4, 28);
	pb_wall2 = App->physics->AddBody(wall2, 0.0f);

	wall3.size = { 4,8,100 };
	wall3.SetPos(-17, 4, 48);
	pb_wall3 = App->physics->AddBody(wall3, 0.0f);

	wall4.size = { 30,8,4 };
	wall4.SetPos(0, 4, 96);
	pb_wall4 = App->physics->AddBody(wall4, 0.0f);
	
	wall5.size = { 40,8,4 };
	wall5.SetPos(35, 4, 60);
	pb_wall5 = App->physics->AddBody(wall5, 0.0f);
	
	wall6.size = { 4,8,80 };
	wall6.SetPos(57, 4, 98);
	pb_wall6 = App->physics->AddBody(wall6, 0.0f);
	
	wall7.size = { 4,8,40 };
	wall7.SetPos(17, 4, 114);
	pb_wall7 = App->physics->AddBody(wall7, 0.0f);
	
	wall8.size = { 12,8,4 };
	wall8.SetPos(49, 4, 136);
	pb_wall8 = App->physics->AddBody(wall8, 0.0f);

	wall9.size = { 12,8,4 };
	wall9.SetPos(21, 4, 136);
	pb_wall9 = App->physics->AddBody(wall9, 0.0f);

	wall10.size = { 4,8,8 };
	wall10.SetPos(25,4,142);
	pb_wall10 = App->physics->AddBody(wall10, 0.0f);

	wall11.size = { 4,8,8 };
	wall11.SetPos(45, 4, 142);
	pb_wall11 = App->physics->AddBody(wall11, 0.0f);

	wall12.size = { 24,8,4 };
	wall12.SetPos(35, 4, 148);
	pb_wall12 = App->physics->AddBody(wall12, 0.0f);



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	pb_goal->GetTransform(&goal.transform);
	goal.Render();

	pb_pivot->GetTransform(&pivot.transform);
	pivot.Render();

	pb_door1->GetTransform(&door1.transform);
	door1.Render();

	pb_door2->GetTransform(&door2.transform);
	door2.Render();


	pb_wall1->GetTransform(&wall1.transform);
	wall1.Render();

	pb_wall2->GetTransform(&wall2.transform);
	wall2.Render();

	pb_wall3->GetTransform(&wall3.transform);
	wall3.Render();

	pb_wall4->GetTransform(&wall4.transform);
	wall4.Render();

	pb_wall5->GetTransform(&wall5.transform);
	wall5.Render();
	
	pb_wall6->GetTransform(&wall6.transform);
	wall6.Render();
	
	pb_wall7->GetTransform(&wall7.transform);
	wall7.Render();
	
	pb_wall8->GetTransform(&wall8.transform);
	wall8.Render();

	pb_wall9->GetTransform(&wall9.transform);
	wall9.Render();

	pb_wall10->GetTransform(&wall10.transform);
	wall10.Render();

	pb_wall11->GetTransform(&wall11.transform);
	wall11.Render();

	pb_wall12->GetTransform(&wall12.transform);
	wall12.Render();


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int winner = App->player->CheckWinner();
	
	if (winner == 1)
	{
		goal.color = Red;
		wall10.color = Red;
		wall11.color = Red;
		wall12.color = Red;
	}

	else if (winner == 2) 
	{
		goal.color = Green;
		wall10.color = Green;
		wall11.color = Green;
		wall12.color = Green;

	}
}

