#include "contiki.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include "net/rime.h"

//#include "ds1722.h"
#include "lib/sensors.h"
#include "temperature.h"

void temperature_sensor_wsn430 () {

        int16_t value_0, value_1;
  //      value_0 = ds1722_read_MSB();
    //    value_1 = ds1722_read_LSB();
        value_1 >>= 5;
        value_1 *= 125;
        printf("Temperature measure: %i.%i\n", value_0, value_1);
}
