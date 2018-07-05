/*
 Copyright (c) 2018 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#ifndef GADAPTER_H_
#define GADAPTER_H_

#include <gimxpoll/include/gpoll.h>

#include <stdint.h>
#include <limits.h>

#ifdef WIN32
#define GA_PACKED __attribute__((gcc_struct, packed))
#else
#define GA_PACKED __attribute__((packed))
#endif

#define GA_USART_BAUDRATE 500000

// the atmega32u4 has 2.5Kbytes SRAM
#define GA_MAX_DESCRIPTORS_SIZE 1024

#define GA_MAX_DESCRIPTORS 32 // should not exceed 255

// the atmega32u4 supports up to 6 non-control endpoints
#define GA_MAX_ENDPOINTS 6

#define GA_MAX_PACKET_SIZE_EP0 64

#define GA_MAX_PAYLOAD_SIZE_EP 64 // for non-control endpoints

typedef struct GA_PACKED {
  uint16_t offset;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} s_ga_descriptorIndex;

typedef struct GA_PACKED {
  uint8_t number; // 0 means end of table
  uint8_t type;
  uint8_t size;
} s_ga_endpointConfig;

typedef struct GA_PACKED {
  uint8_t endpoint; // 0 means nothing to send
  uint8_t data[GA_MAX_PAYLOAD_SIZE_EP];
} s_ga_endpointPacket; // should not exceed 255 bytes

typedef enum {
  E_TYPE_DESCRIPTORS,
  E_TYPE_INDEX,
  E_TYPE_ENDPOINTS,
  E_TYPE_RESET,
  E_TYPE_CONTROL,
  E_TYPE_CONTROL_STALL,
  E_TYPE_IN,
  E_TYPE_OUT,
  E_TYPE_DEBUG,
} e_ga_packetType;

// this is the max serial packet size
#define GA_MAX_PACKET_SIZE 256

typedef struct GA_PACKED {
  uint8_t type;
  uint8_t length;
} s_ga_header;

// this should not exceed 255 bytes
#define MAX_PACKET_VALUE_SIZE (GA_MAX_PACKET_SIZE - sizeof(s_ga_header))

typedef struct GA_PACKED
{
  s_ga_header header;
  uint8_t value[MAX_PACKET_VALUE_SIZE];
} s_ga_packet;

struct gadapter_device;

typedef int (* GADAPTER_READ_CALLBACK)(void * user, s_ga_packet * packet);
typedef int (* GADAPTER_WRITE_CALLBACK)(void * user, int transfered);
typedef int (* GADAPTER_CLOSE_CALLBACK)(void * user);
#ifndef WIN32
typedef GPOLL_REGISTER_FD GADAPTER_REGISTER_SOURCE;
typedef GPOLL_REMOVE_FD GADAPTER_REMOVE_SOURCE;
#else
typedef GPOLL_REGISTER_HANDLE GADAPTER_REGISTER_SOURCE;
typedef GPOLL_REMOVE_HANDLE GADAPTER_REMOVE_SOURCE;
#endif

typedef struct {
    GADAPTER_READ_CALLBACK fp_read;       // called on data reception
    GADAPTER_WRITE_CALLBACK fp_write;     // called on write completion
    GADAPTER_CLOSE_CALLBACK fp_close;     // called on failure
    GADAPTER_REGISTER_SOURCE fp_register; // to register device to event sources
    GADAPTER_REMOVE_SOURCE fp_remove;     // to remove device from event sources
} GADAPTER_CALLBACKS;

struct gadapter_device * gadapter_open(const char * port, unsigned int baudrate, const GADAPTER_CALLBACKS * callbacks);
int gadapter_send(void * user, unsigned char type, const unsigned char * data, unsigned int count);
int gadapter_close(void * user);

#endif /* GADAPTER_H_ */
