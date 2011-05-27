#ifndef TCPR_TYPES_H
#define TCPR_TYPES_H

#include <stdint.h>

struct tcpr_saved {
	uint32_t ack;
	struct {
		uint16_t mss;
		uint8_t ws;
		uint8_t sack_permitted;
	} peer;
	uint8_t done_reading;
	uint8_t done_writing;
};

struct tcpr {
	struct tcpr_saved saved;
	uint32_t delta;
	uint32_t ack;
	uint32_t fin;
	uint32_t seq;
	uint32_t win;
	struct {
		uint32_t ack;
		uint32_t fin;
		uint32_t win;
		uint8_t have_fin;
		uint8_t have_ack;
	} peer;
	uint8_t have_fin;
	uint8_t done;
};

#endif
