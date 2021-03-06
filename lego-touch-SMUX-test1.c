#pragma config(Sensor, S3,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: lego-touch-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * lego-touch.h provides an API for the Lego Touch Sensor.  This program
 * demonstrates how to use that API through a SMUX.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * 08 December 2009
 * version 0.1
 */

#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-touch.h"
#include "drivers/hitechnic-irseeker-v2.h"

  int _dirDC = 0;
  int _dirAC = 0;
	int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor LEGOTOUCH = msensor_S3_1;
const tMUXSensor HTIRS2 = msensor_S3_2;

task main()
{
	    // Read the current non modulated signal direction
    _dirDC = HTIRS2readDCDir(HTIRS2);
    if (_dirDC < 0)

    // read the current modulated signal direction
    _dirAC = HTIRS2readACDir(HTIRS2);
    if (_dirAC < 0)

  nxtDisplayCenteredTextLine(0, "Lego");
  nxtDisplayCenteredBigTextLine(1, "TOUCH");
  nxtDisplayCenteredTextLine(3, "SMUX Test");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and sensor to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  eraseDisplay();

  while (true) {
    // Check if the sensor is pressed or not.
    if (TSreadState(LEGOTOUCH))
    {
      nxtDisplayCenteredTextLine(3, "ACTIVE");
          displayText3(1, "D", _dirDC);
  	}

    else
    {
      nxtDisplayCenteredTextLine(3, "INACTIVE");
          displayText3(1, "D", _dirDC);
    }
    wait1Msec(50);
  }


}

/*
 * $Id: lego-touch-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */
