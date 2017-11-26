/*
 * buffer.h
 *
 *  Created on: Sep 26, 2017
 *      Author: spinkoh
 */
#include <stdint.h>

#ifndef BUFFER_H_
#define BUFFER_H_

#define BUFFER_SUCCESS 0x00
#define BUFFER_AVAILABLE BUFFER_SUCCESS
#define BUFFER_FULL 0x01
#define BUFFER_EMPTY 0x02
#define BUFFER_FAILED 0xFF
#define SIZE 200

typedef struct triplet {
	float x;
	float y;
	float z;
} triplet;

typedef struct triple_ring_buffer {
	triplet tripletBuffer[SIZE];
	uint16_t head;
	uint16_t tail;
} triple_ring_buffer;

void init_buffer(triple_ring_buffer* buffer);
int add(triple_ring_buffer* buffer,triplet dat);
int fetch(triple_ring_buffer* buffer, triplet* xyzTriplet);
int peek(triple_ring_buffer* buffer);
int isFull(triple_ring_buffer* buffer);

#endif /* BUFFER_H_ */
