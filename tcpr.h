#ifndef TCPR_H
#define TCPR_H

#include <stdint.h>
#include <stdlib.h>
#include <netinet/tcp.h>

enum tcpr_flags {
	TCPR_CLOSED = 0x1,
	TCPR_NO_STATE = 0x2,
	TCPR_PEER_ACK = 0x4,
	TCPR_RECOVERY = 0x8,
	TCPR_SPURIOUS_FIN = 0x10,
	TCPR_SPURIOUS_RST = 0x20,
	TCPR_DUPLICATE_ACK = 0x40,
	TCPR_UPDATE_ACK = 0x80,
};

struct tcpr_state {
	uint16_t peer_port;
	uint16_t port;
	uint32_t peer_ack;
	uint32_t peer_fin;
	uint32_t peer_win;
	uint32_t raw_ack;
	uint32_t ack;
	uint32_t fin;
	uint32_t seq;
	uint32_t win;
	uint32_t delta;
	uint8_t have_peer_fin;
	uint8_t have_peer_ack;
	uint8_t have_fin;
	uint8_t have_ack;
	uint8_t done_reading;
	uint8_t done_writing;
};

struct tcpr_update {
	uint16_t peer_port;
	uint16_t port;
	uint32_t peer_ack;
	uint32_t ack;
	uint32_t delta;
	uint8_t have_peer_ack;
	uint8_t have_ack;
	uint8_t time_wait;
	uint8_t done_reading;
	uint8_t done_writing;
};

int tcpr_handle_segment_from_peer(struct tcpr_state *state, struct tcphdr *tcp,
					size_t size);
int tcpr_handle_segment(struct tcpr_state *state, struct tcphdr *tcp,
					size_t size);

void tcpr_make_acknowledgment(struct tcphdr *tcp, struct tcpr_state *state);
void tcpr_make_handshake(struct tcphdr *tcp, struct tcpr_state *state);
void tcpr_make_reset(struct tcphdr *tcp, struct tcpr_state *state);

int tcpr_handle_update(struct tcpr_state *state, struct tcpr_update *update);
void tcpr_make_update(struct tcpr_update *update, struct tcpr_state *state);

#endif