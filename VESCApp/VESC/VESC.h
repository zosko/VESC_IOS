//
//  VESC.h
//  Pedaless
//
//  Created by Bosko Petreski on 4/19/18.
//  Copyright © 2018 Bosko Petreski. All rights reserved.
//

#import <Foundation/Foundation.h>

#define PACKET_LENGTH_IDENTIFICATION_BYTE_SHORT 2
#define PACKET_LENGTH_IDENTIFICATION_BYTE_LONG 3
#define PACKET_TERMINATION_BYTE 3
#define PACKET_PAYLOAD_MAX_LENGTH 512

// Start byte + packet length bytes + payload + 2 bytes (CRC) + termination byte
#define PACKET_MAX_LENGTH (1 + 2 + PACKET_PAYLOAD_MAX_LENGTH + 2 + 1)

// VESC defines
typedef enum {
    COMM_GET_VALUES = 4,
    COMM_SET_CURRENT = 6
} COMM_PACKET_ID;

typedef enum {
    FAULT_CODE_NONE = 0,
    FAULT_CODE_OVER_VOLTAGE,
    FAULT_CODE_UNDER_VOLTAGE,
    FAULT_CODE_DRV,
    FAULT_CODE_ABS_OVER_CURRENT,
    FAULT_CODE_OVER_TEMP_FET,
    FAULT_CODE_OVER_TEMP_MOTOR
} mc_fault_code;

typedef struct {
    float v_in;
    float temp_mos;
    float temp_motor;
    float current_motor;
    float current_in;
    float id;
    float iq;
    float rpm;
    float duty_now;
    float amp_hours;
    float amp_hours_charged;
    float watt_hours;
    float watt_hours_charged;
    int tachometer;
    int tachometer_abs;
    mc_fault_code fault_code;
    float pid_pos;
    uint8_t vesc_id;
} mc_values;

@interface VESC : NSObject {
    
}

-(NSData *)dataForGetValues;
-(int)process_incoming_bytes:(NSData *)incomingData;
-(mc_values)readPacket;
-(void)resetPacket;
-(NSData *)SetCurrent:(double)val;

@end
