#pragma once

#include <iostream>
#include <GL/freeglut.h>


#define ENERGY_LOSS_WALL 0.9f
#define	ENERGY_LOSS_PARTICLE 0.9f
#define MASS_LOSS_WALL 1.0f
#define MASS_LOSS_PARTICLE 1.0f
#define G 6.67f
#define H 0.001f


class Ball
{
	float _px, _py;
	float _vx, _vy;
	float _radius;
	float _mass;
	float _ax = 0;
	float _ay = 0;
	float h = H;

	bool fix_pos;
public:
public:
	Ball();
	~Ball(){}

	Ball(float init_px, float init_py, float init_vx, float init_vy, float init_radius, float init_mass = 1, bool is_fixed = false);

	void draw();
	void advance();

	float kinetic_energy();

	bool collide_with_boundary(float x_rear, float x_far, float y_rear, float y_far);
	bool collide_with_ball(Ball &other);

	void gravity_with_ball(Ball *others, int current, int num);

	/* properties */
	float ax(){
		return _ax;
	}
	void ax(float new_ax){
		_ax = new_ax;
	}

	float ay(){
		return _ay;
	}
	void ay(float new_ay){
		_ay = new_ay;
	}

	float px(){
		return _px;
	}
	void px(float new_px){
		_px = new_px;
	}

	float py(){
		return _py;
	}
	void py(float new_py){
		_py = new_py;
	}

	float vx(){
		return _vx;
	}
	void vx(float new_vx){
		_vx = new_vx;
	}

	float vy(){
		return _vy;
	}
	void vy(float new_vy){
		_vy = new_vy;
	}

	float radius(){
		return _radius;
	}
	void radius(float new_radius){
		_radius = new_radius;
	}

	float mass(){
		return _mass;
	}
	void mass(float new_mass){
		_mass = new_mass;
	}

};

