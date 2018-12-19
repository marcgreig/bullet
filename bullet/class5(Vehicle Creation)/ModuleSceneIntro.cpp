#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(3, 0, 0));

	//Map Walls
	wall1.size = { 30, 4, 4 };
	wall1.SetPos(0, 2, 0);
	pb_wall1 = App->physics->AddBody(wall1, 0.0f);
	//pb_wall1->collision_listeners.add(this);

	wall2.size = { 4, 4, 60 };
	wall2.SetPos(17, 2, 28);
	pb_wall2 = App->physics->AddBody(wall2, 0.0f);

	wall3.size = { 4,4,100 };
	wall3.SetPos(-17, 2, 48);
	pb_wall3 = App->physics->AddBody(wall3, 0.0f);

	wall4.size = { 30,4,4 };
	wall4.SetPos(0, 2, 96);
	pb_wall4 = App->physics->AddBody(wall4, 0.0f);
	
	wall5.size = { 40,4,4 };
	wall5.SetPos(35, 2, 60);
	pb_wall5 = App->physics->AddBody(wall5, 0.0f);
	
	wall6.size = { 4,4,80 };
	wall6.SetPos(57, 2, 98);
	pb_wall6 = App->physics->AddBody(wall6, 0.0f);
	
	wall7.size = { 4,4,40 };
	wall7.SetPos(17, 2, 114);
	pb_wall7 = App->physics->AddBody(wall7, 0.0f);
	
	wall8.size = { 40,4,4 };
	wall8.SetPos(35, 2, 136);
	pb_wall8 = App->physics->AddBody(wall8, 0.0f);

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
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

