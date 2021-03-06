/*
 * fall_detection.h
 *
 *  Created on: Sep 28, 2017
 *      Author: Station13
 */

#ifndef FALL_DETECTION_H_
#define FALL_DETECTION_H_

#include <math.h>
#include "buffer.h"
#include "lsm6ds3.h"

#define DELTA_T 1 //derived from sampling rate (ms)
#define EXCEED 0x01
#define SUPER_EXCEED	0x02
#define BELOW 0x00
#define NOT_A_FALL 0x00
#define FALL 0x01
// 2.27 1.74
//2.27 1.14
//1.74 1.14 ->Working
#define FT1_S 1.5 /*old = 1.5 angular velocity threshold rad/s at sternum level 2.27*/
#define FT1_W 1.14 /*old = 1.74 angular velocity threshold rad/s at waist level 1.1?*/



float magnitude(float x, float y, float z);

int detection_angular_velocity_sternum(triplet angular_v_sternum);
int detection_angular_velocity_waist(triplet angular_v_waist);

void calculate_angular_acceleration(triplet v_f,triplet v_i, float DTime,triplet* angular_ac);
void average_velocity(triplet* angular_velocity1, triplet* angular_velocity2);
int compare_angular_threshold(triplet* angular_velocity, triplet InitAngle, float DTime, triplet velocity);



/*Compute an angle using complementary filter, result stores in angle_f in rad*/
void compute_angle(triplet angular_velocity, triplet* angle_f, triplet acc_data, float DTime);
void compute_angle_v2(triplet angular_velocity, triplet* angle_f, float DTime);
int single_fall_detection(float magA, float angle);//all accelerations have the unit with g
int multi_fall_detection(float magA, triplet angle1);
float calculate_SMA(triplet acc, float DTime);


#endif /* FALL_DETECTION_H_ */
