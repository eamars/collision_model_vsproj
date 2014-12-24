#include "ball.h"
#include <cmath>

// Declear a vector type struct to make things easier
typedef struct vt_s Vector;
struct vt_s {
	float x;
	float y;
};


void DrawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2.0f * 3.1415926f / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;//we start at angle = 0
	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}


float distance(Vector v1, Vector v2){
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	return sqrtf(dx * dx + dy * dy);
}

float dot(Vector v1, Vector v2){
	return v1.x * v2.x + v1.y * v2.y;
}

void normalize(Vector *v1){
	float length = sqrtf(v1->x * v1->x + v1->y * v1->y);
	v1->x /= length;
	v1->y /= length;
}




Ball::Ball(){

	px(0);
	py(0);

	vx(0);
	vy(0);

	mass(1);
	radius(1);

	fix_pos = false;
}


Ball::Ball(float init_px, float init_py, float init_vx, float init_vy, float init_radius, float init_mass, bool is_fixed){
	px(init_px);
	py(init_py);

	vx(init_vx);
	vy(init_vy);

	mass(init_mass);
	radius(init_radius);

	fix_pos = is_fixed;

}

void Ball::draw(){
	DrawCircle(px(), py(), radius(), 80);
}

void Ball::advance(){
	if (!fix_pos) {
		vx(vx() + h * (-ax()));
		vy(vy() + h * (-ay()));
		py(py() + h * vy());
		px(px() + h * vx());
	}

}

float Ball::kinetic_energy(){
	return (vx()*vx() + vy()*vy()) / 2;
}

bool Ball::collide_with_boundary(float x_near, float x_rear, float y_near, float y_rear){
	// reach button
	if (py() - radius() <= y_near && vy() < 0){
		vy(-vy() * ENERGY_LOSS_WALL);
		py(y_near + radius());

		radius(radius() * MASS_LOSS_WALL);
		mass(mass() * MASS_LOSS_WALL);

		return true;
	}

	// reach top
	if (py() + radius() >= y_rear && vy() > 0){
		vy(-vy() * ENERGY_LOSS_WALL);
		py(y_rear - radius());

		radius(radius() * MASS_LOSS_WALL);
		mass(mass() * MASS_LOSS_WALL);

		return true;
	}

	// reach left
	if (px() - radius() < x_near  && vx() < 0){
		vx(-vx() * ENERGY_LOSS_WALL);
		px(x_near + radius());

		radius(radius() * MASS_LOSS_WALL);
		mass(mass() * MASS_LOSS_WALL);

		return true;
	}

	// reach right
	if (px() + radius() >= x_rear && vx() > 0){
		vx(-vx() * ENERGY_LOSS_WALL);
		px(x_rear - radius());

		radius(radius() * MASS_LOSS_WALL);
		mass(mass() * MASS_LOSS_WALL);

		return true;
	}
	return false;


}

bool Ball::collide_with_ball(Ball &other){
	if (distance({ px(), py() }, { other.px(), other.py() }) <= (radius() + other.radius())) {
		/* Step1 */

		// find normal vector
		Vector un;
		un = { px() - other.px(), py() - other.py() };

		// normalize it
		normalize(&un);

		// find unit tangent vector
		Vector ut;
		ut = { -un.y, un.x };


		/* Step2 */

		// store original velocity vector
		Vector V1, V2;
		V1 = { vx(), vy() };
		V2 = { other.vx(), other.vy() };

		/* Step3 */

		// find tangent and normal velocity before collision
		float v1n, v2n, v1t, v2t;

		v1n = dot(un, V1);
		v1t = dot(ut, V1);

		v2n = dot(un, V2);
		v2t = dot(ut, V2);

		/* Step4 */

		// find tangent and normal velocity after collision
		float new_v1t, new_v2t;
		new_v1t = v1t;
		new_v2t = v2t;

		/* Step5 */

		// find new normal velocities
		float new_v1n, new_v2n;

		new_v1n = (v1n * (mass() - other.mass()) + 2 * other.mass() * v2n) / (mass() + other.mass());
		new_v2n = (v2n * (other.mass() - mass()) + 2 * mass() * v1n) / (mass() + other.mass());

		/* Step6 */

		// convert scalar normal and tangential velocities into vectors
		Vector V1N, V2N, V1T, V2T;

		V1N = { new_v1n * un.x, new_v1n * un.y };
		V2N = { new_v2n * un.x, new_v2n * un.y };

		V1T = { new_v1t * ut.x, new_v1t * ut.y };
		V2T = { new_v2t * ut.x, new_v2t * ut.y };

		/* finish */
		vx(V1N.x + V1T.x);
		vy(V1N.y + V1T.y);

		other.vx((V2N.x + V2T.x) * ENERGY_LOSS_PARTICLE);
		other.vy((V2N.y + V2T.y) * ENERGY_LOSS_PARTICLE);

		other.radius(other.radius() * MASS_LOSS_PARTICLE);
		other.mass(other.mass() * MASS_LOSS_PARTICLE);

		radius(radius() * MASS_LOSS_PARTICLE);
		mass(mass() * MASS_LOSS_PARTICLE);

		return true;
	}

	return false;
}

void Ball::gravity_with_ball(Ball *others, int current, int num){
	Vector A = { 0, 0 };
	Vector R12;
	float r12;
	float factor;

	for (int i = 0; i < num; i++) {
		if (distance({ px(), py() }, { others[i].px(), others[i].py() }) >= (radius() + others[i].radius())){
			if (i != current) {
				r12 = distance({ others[i].px(), others[i].py() }, { px(), py() });

				factor = G * others[i].mass() / (r12 * r12);

				R12 = { others[i].px() - px(), others[i].py() - py() };

				normalize(&R12);

				A.x -= factor * R12.x;
				A.y -= factor * R12.y;


			}
		}


	}

	ax(A.x);
	ay(A.y);

}

