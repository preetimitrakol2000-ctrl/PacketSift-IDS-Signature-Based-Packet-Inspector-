#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "packet_pipeline.h"

#ifdef _WIN32
    __declspec(dllexport) PacketRingBuffer* init_ids_buffer();
    __declspec(dllexport) bool enqueue_packet(PacketRingBuffer* rb, const char* payload);
    __declspec(dllexport) bool inspect_next_packet(PacketRingBuffer* rb, const char* signature);
    __declspec(dllexport) void destroy_ids(PacketRingBuffer* rb);
#endif

PacketRingBuffer* init_ids_buffer() {
    PacketRingBuffer* rb = (PacketRingBuffer*)malloc(sizeof(PacketRingBuffer));
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    return rb;
}

bool enqueue_packet(PacketRingBuffer* rb, const char* payload) {
    if (rb->count == BUFFER_SIZE) {
        return false; // Buffer overflow (dropped packet scenario)
    }
    strncpy(rb->buffer[rb->tail], payload, MAX_PAYLOAD_SIZE - 1);
    rb->buffer[rb->tail][MAX_PAYLOAD_SIZE - 1] = '\0';
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    rb->count++;
    return true;
}

bool inspect_next_packet(PacketRingBuffer* rb, const char* signature) {
    if (rb->count == 0) {
        return false; // Buffer is empty
    }

    // Read item from the head of the circular queue
    char* current_payload = rb->buffer[rb->head];
    bool is_malicious = kmp_search(current_payload, signature);

    // Dequeue item from the queue ring mapping
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    rb->count--;

    return is_malicious;
}

void destroy_ids(PacketRingBuffer* rb) {
    free(rb);
}
