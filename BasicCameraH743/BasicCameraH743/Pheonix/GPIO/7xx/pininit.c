#include "configure.h"

void Init_GPIO(void)
{
//	pinInit(X_DIR_PIN);
//	pinInit(X_STEP_PIN);
//	pinInit(X_HOME_PIN);
////
//	pinInit(Y_DIR_PIN);
//	pinInit(Y_STEP_PIN);
//	pinInit(Y_HOME_PIN);
////
//	pinInit(Z_DIR_PIN);
//	pinInit(Z_STEP_PIN);
//	pinInit(Z_HOME_PIN);
//
//	pinInit(A_DIR_PIN);
//	pinInit(A_STEP_PIN);
//	pinInit(A_HOME_PIN);
//
//	pinInit(B_DIR_PIN);
//	pinInit(B_STEP_PIN);
//	pinInit(B_HOME_PIN);
//
	pinInit(HEARTBEAT_PIN);
//
//	pinInit(CAN1_RX);
//	pinInit(CAN1_TX);
//
//	pinInit(PNP_ENABLE);
//	pinInit(PNP_RCLK);
//
	pinInit(USERKEY1_PIN);
//	pinInit(USERKEY2_PIN);
//	//this is for FK750 V1.1
//	pinInit(SPI4_LCD_BLK);
//	pinSet(SPI4_LCD_BLK);

}

void Update_Home_Status(void)
{//reads the pins from a list and updates the variables
	X_HOME_READ;
	Y_HOME_READ;
	Z_HOME_READ;
	A_HOME_READ;
	B_HOME_READ;
}

