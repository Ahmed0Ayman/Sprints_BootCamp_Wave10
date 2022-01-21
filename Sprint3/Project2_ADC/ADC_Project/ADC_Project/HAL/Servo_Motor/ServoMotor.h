/*
 * ServoMotor.h
 *
 * Created: 1/17/2022 9:17:40 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#define SERVO_MOTOR_CON_
#define SERVO_MOTOR_180_
#define SERVO_MOTOR_360_


typedef enum {SERVO_MO_OK ,SERVO_MO_PARAM_ERROR , SERVO_MO_CONFIG_ERROR }Servo_status_t;

void ServoMotor_Init(void); 


void ServoMotor_Set(void);






#endif /* SERVOMOTOR_H_ */