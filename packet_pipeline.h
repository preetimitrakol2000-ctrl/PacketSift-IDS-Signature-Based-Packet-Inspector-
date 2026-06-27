#ifndef PACKET_PIPELINE_H
#define PACKET_PIPELINE_H

#include <stdbool.h>

#define BUFFER_SIZE 16
#define MAX_PAYLOAD_SIZE 512

typedef struct {
    char buffer[BUFFER_SIZE][MAX_PAYLOAD_SIZE];
    int head;
    int tail;
    int count;
} PacketRingBuffer;

void compute_lps_array(const char* pat, int M, int* lps);
bool kmp_search(const char* txt, const char* pat);

#endif // PACKET_PIPELINE_H
