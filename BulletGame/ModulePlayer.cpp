#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Color.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn1 = acceleration1 = brake1 = 0.0f;
	turn2 = acceleration2 = brake2 = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	p1time.Start();
	p2time.Start();

	LOG("Loading player");

	VehicleInfo car1;
	VehicleInfo car2;

	car1.color = Red;
	car2.color = Green;

	// Car properties ----------------------------------------
	car1.chassis_size.Set(2, 2, 4);
	car1.chassis_offset.Set(0, 1.5, 0);
	car1.mass = 500.0f;
	car1.suspensionStiffness = 5.88f;
	car1.suspensionCompression = 0.83f;
	car1.suspensionDamping = 0.88f;
	car1.maxSuspensionTravelCm = 1000.0f;
	car1.frictionSlip = 50.5;
	car1.maxSuspensionForce = 6000.0f;
	car2.chassis_size.Set(2, 2, 4);
	car2.chassis_offset.Set(0, 1.5, 0);
	car2.mass = 500.0f;
	car2.suspensionStiffness = 5.88f;
	car2.suspensionCompression = 0.83f;
	car2.suspensionDamping = 0.88f;
	car2.maxSuspensionTravelCm = 1000.0f;
	car2.frictionSlip = 50.5;
	car2.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width1 = car1.chassis_size.x*0.5f;
	float half_length1 = car1.chassis_size.z*0.5f;

	float half_width2 = car2.chassis_size.x*0.5f;
	float half_length2 = car2.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car1.num_wheels = 4;
	car1.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car1.wheels[0].connection.Set(half_width1 - 0.3f * wheel_width, connection_height, half_length1 - wheel_radius);
	car1.wheels[0].direction = direction;
	car1.wheels[0].axis = axis;
	car1.wheels[0].suspensionRestLength = suspensionRestLength;
	car1.wheels[0].radius = wheel_radius;
	car1.wheels[0].width = wheel_width;
	car1.wheels[0].front = true;
	car1.wheels[0].drive = true;
	car1.wheels[0].brake = false;
	car1.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car1.wheels[1].connection.Set(-half_width1 + 0.3f * wheel_width, connection_height, half_length1 - wheel_radius);
	car1.wheels[1].direction = direction;
	car1.wheels[1].axis = axis;
	car1.wheels[1].suspensionRestLength = suspensionRestLength;
	car1.wheels[1].radius = wheel_radius;
	car1.wheels[1].width = wheel_width;
	car1.wheels[1].front = true;
	car1.wheels[1].drive = true;
	car1.wheels[1].brake = false;
	car1.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car1.wheels[2].connection.Set(half_width1 - 0.3f * wheel_width, connection_height, -half_length1 + wheel_radius);
	car1.wheels[2].direction = direction;
	car1.wheels[2].axis = axis;
	car1.wheels[2].suspensionRestLength = suspensionRestLength;
	car1.wheels[2].radius = wheel_radius;
	car1.wheels[2].width = wheel_width;
	car1.wheels[2].front = false;
	car1.wheels[2].drive = false;
	car1.wheels[2].brake = true;
	car1.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car1.wheels[3].connection.Set(-half_width1 + 0.3f * wheel_width, connection_height, -half_length1 + wheel_radius);
	car1.wheels[3].direction = direction;
	car1.wheels[3].axis = axis;
	car1.wheels[3].suspensionRestLength = suspensionRestLength;
	car1.wheels[3].radius = wheel_radius;
	car1.wheels[3].width = wheel_width;
	car1.wheels[3].front = false;
	car1.wheels[3].drive = false;
	car1.wheels[3].brake = true;
	car1.wheels[3].steering = false;

	car2.num_wheels = 4;
	car2.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car2.wheels[0].connection.Set(half_width2 - 0.3f * wheel_width, connection_height, half_length2 - wheel_radius);
	car2.wheels[0].direction = direction;
	car2.wheels[0].axis = axis;
	car2.wheels[0].suspensionRestLength = suspensionRestLength;
	car2.wheels[0].radius = wheel_radius;
	car2.wheels[0].width = wheel_width;
	car2.wheels[0].front = true;
	car2.wheels[0].drive = true;
	car2.wheels[0].brake = false;
	car2.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car2.wheels[1].connection.Set(-half_width2 + 0.3f * wheel_width, connection_height, half_length2 - wheel_radius);
	car2.wheels[1].direction = direction;
	car2.wheels[1].axis = axis;
	car2.wheels[1].suspensionRestLength = suspensionRestLength;
	car2.wheels[1].radius = wheel_radius;
	car2.wheels[1].width = wheel_width;
	car2.wheels[1].front = true;
	car2.wheels[1].drive = true;
	car2.wheels[1].brake = false;
	car2.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car2.wheels[2].connection.Set(half_width2 - 0.3f * wheel_width, connection_height, -half_length2 + wheel_radius);
	car2.wheels[2].direction = direction;
	car2.wheels[2].axis = axis;
	car2.wheels[2].suspensionRestLength = suspensionRestLength;
	car2.wheels[2].radius = wheel_radius;
	car2.wheels[2].width = wheel_width;
	car2.wheels[2].front = false;
	car2.wheels[2].drive = false;
	car2.wheels[2].brake = true;
	car2.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car2.wheels[3].connection.Set(-half_width2 + 0.3f * wheel_width, connection_height, -half_length2 + wheel_radius);
	car2.wheels[3].direction = direction;
	car2.wheels[3].axis = axis;
	car2.wheels[3].suspensionRestLength = suspensionRestLength;
	car2.wheels[3].radius = wheel_radius;
	car2.wheels[3].width = wheel_width;
	car2.wheels[3].front = false;
	car2.wheels[3].drive = false;
	car2.wheels[3].brake = true;
	car2.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car1);
	vehicle->SetPos(5, 0, 10);
	vehicle2 = App->physics->AddVehicle(car2);
	vehicle2->SetPos(-5, 0, 10);
	vehicle2->collision_listeners.add(this);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}



// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (winner == true) {

		return UPDATE_CONTINUE;
	}
	else {
	turn1 = acceleration1 = brake1 = 0.0f;
	turn2 = acceleration2 = brake2 = 0.0f;

	mat4x4 Starting_mat = mat4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f);

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration1 = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn1 < TURN_DEGREES)
			turn1 +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn1 > -TURN_DEGREES)
			turn1 -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		brake1 = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration2 = MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn2 < TURN_DEGREES)
			turn2 += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn2 > -TURN_DEGREES)
			turn2 -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake2 = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		if (p1time.Read() > 10 * 1000) {

			App->audio->PlayFx(1);

			vehicle->vehicle->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
			vehicle->SetTransform(Starting_mat.M);
			vehicle->SetPos(5, 0, 10);

			p1time.Start();
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
	{
		if (p2time.Read() > 10 * 1000) {

			App->audio->PlayFx(1);

			vehicle2->vehicle->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
			vehicle2->SetTransform(Starting_mat.M);
			vehicle2->SetPos(-5, 0, 10);

			p2time.Start();
		}

	}

	vehicle->ApplyEngineForce(acceleration1);
	vehicle->Turn(turn1);
	vehicle->Brake(brake1);

	vehicle2->ApplyEngineForce(acceleration2);
	vehicle2->Turn(turn2);
	vehicle2->Brake(brake2);

	CheckWinner();

	vehicle->Render();
	vehicle2->Render();

	char title[100];
	sprintf_s(title, "Vehicle1: %.1f Km/h, Vehicle2: %.1f Km/h", vehicle->GetKmh(), vehicle2->GetKmh());
	App->window->SetTitle(title);
	

	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::Restart()
{
	winner = false;
	mat4x4 Starting_mat = mat4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f);

	vehicle->vehicle->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
	vehicle->SetTransform(Starting_mat.M);
	vehicle->SetPos(5, 0, 10);

	vehicle2->vehicle->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
	vehicle2->SetTransform(Starting_mat.M);
	vehicle2->SetPos(-5, 0, 10);

	App->scene_intro->goal.SetPos(35, 3, 138);
	App->scene_intro->pb_goal->SetPos(35, 3, 138);
	App->scene_intro->goal.color = Blue;

	App->scene_intro->wall10.color = White;
	App->scene_intro->wall11.color = White;
	App->scene_intro->wall12.color = White;
}


int ModulePlayer::CheckWinner()
{
	int ret = 0;


	vec3 posCar1 = vehicle->GetPos();
	vec3 posCar2 = vehicle2->GetPos();

	if (posCar1.z >= 134)
	{
		LOG("Red Player Wins");
		ret = 1;
		return ret;
		
	}
	if (posCar2.z >= 134) 
	{
		LOG("Green Player Wins");
		ret = 2;
		return ret;
	}
	
	return ret;
	
}






