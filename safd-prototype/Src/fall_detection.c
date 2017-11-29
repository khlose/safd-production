/*
 * fall_detection.c
 *
 *  Created on: Sep 28, 2017
 *      Author: Station13
 */

#include "fall_detection.h"
#include <math.h>

float magnitude(float x,float y,float z)
{
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

float calculate_SMA(triplet acc, float DTime){
	float sma = (fabs(acc.x)*DTime + fabs(acc.y)*DTime + fabs(acc.z)*DTime)/DTime;
	return sma;
}


int compare_angular_velocity(triplet* angular_velocity, triplet InitAngle, float DTime, triplet velocity){
	triplet angle;
	angle.x = InitAngle.x + angular_velocity->x*DTime;
	angle.y = InitAngle.y + angular_velocity->y*DTime;
	angle.z = InitAngle.z + angular_velocity->z*DTime;

	float MagA = sqrt(pow(angle.x, 2) + pow(angle.y, 2) + pow(angle.z, 2));

	if(MagA > (9.8*(1.05))){
		return EXCEED;
	}
	else if(MagA < (9.8*(1.05))){
		return BELOW;
	}
	else{
		angle.x = atan(velocity.y/velocity.z);
		angle.y = atan(velocity.x/velocity.z);
		angle.z = atan(velocity.y/velocity.x);
	}
	return 0;
}


/*Compute an angle using complementary filter, result stores in angle_f in rad*/
void compute_angle(triplet angular_velocity, triplet* angle_f, triplet acc_data, float DTime)
{
	float acc_factor_pitch, acc_factor_roll;
	//some people have -= for roll, why?
	angle_f->x += angular_velocity.x * DTime; //pitch
	//angle_f->y += angular_velocity->y * DTime; //don't care
	angle_f->z += angular_velocity.z * DTime; //roll

	acc_factor_pitch = atan2f(acc_data.y,acc_data.z);
	acc_factor_roll = atan2f(acc_data.y,acc_data.x);

	angle_f->x = 0.98 * angle_f->x + acc_factor_pitch * 0.02;
	angle_f->z = 0.98 * angle_f->z + acc_factor_roll * 0.02;

}

void compute_angle_v2(triplet angular_velocity, triplet* angle_f, float DTime)
{
	angle_f->x = angular_velocity.x*DTime;
	angle_f->y = angular_velocity.y*DTime;
	angle_f->z = angular_velocity.z*DTime;
}

void calculate_angular_acceleration(triplet v_f,triplet v_i, float DTime,triplet* angular_ac)
{
	angular_ac->x = (v_f.x - v_i.x)/DTime;
	angular_ac->y = (v_f.y - v_i.y)/DTime;
	angular_ac->z = (v_f.z - v_i.z)/DTime;
	return;
}

int detection_angular_velocity_sternum(triplet angular_v_sternum)
{
	/*Calculate resultant angular velocity*/
	/*z = roll angular velocity*/
	/*x = pitch angular velocity*/
	float resultant_angular_v = sqrt(pow(angular_v_sternum.z,2) + pow(angular_v_sternum.x,2));

	//might have to be angular_v_sternum.x and not resultant angular velocity according to
	//dope_fall_detection.pdf in research article folder
	if(fabs(resultant_angular_v) > FT1_S)
	{
		/*measure FT2 and FT3*/

		return EXCEED;
	}

	return BELOW;
}

int detection_angular_velocity_waist(triplet angular_v_waist)
{
	/*Calculate resultant angular velocity*/
	/*z = roll angular velocity*/
	/*x = pitch angular velocity*/
	float resultant_angular_v = sqrt(pow(angular_v_waist.z,2) + pow(angular_v_waist.x,2));

	//might have to be angular_v_sternum.x and not resultant angular velocity according to
	//dope_fall_detection.pdf in research article folder
	//if(resultant_angular_v > FT1_W)
	if(fabs(resultant_angular_v) > FT1_W)
	{
		/*measure FT2 and FT3*/

		return EXCEED;
	}

	return BELOW;
}


int single_fall_detection(float magA, float angle){
	if(magA > 1.175){
		//static
		if(angle > 45){
			return NOT_A_FALL;//standing
		}
		else{
			return FALL;//sitting/lying
		}
	}
	else{
		//dynamic
		return NOT_A_FALL;
	}
}

int multi_fall_detection(float magA, triplet angle1){
	if(magA < 1.246){
		return NOT_A_FALL;//dynamic
	}
	else{
		//static
		if((angle1.x < 130/3.14159) || (angle1.y < 130/3.14159) || (angle1.z < 130/3.14159)){
			return NOT_A_FALL;//unknown
		}
		if((angle1.x < 50/3.14159) || (angle1.y < 50/3.14159) || (angle1.z < 50/3.14159)){
			return NOT_A_FALL;//upright
		}
		return FALL;
	}
}
