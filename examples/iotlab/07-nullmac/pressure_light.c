#include "contiki.h"
#include "net/rime.h"
#include <stdio.h>
#include <stdlib.h>
#include "dev/light-sensor.h"
#include "dev/pressure-sensor.h"
#include "pressure_light.h"


void config_pressure()
{
 pressure_sensor.configure(PRESSURE_SENSOR_DATARATE,LPS331AP_P_12_5HZ_T_1HZ);
 SENSORS_ACTIVATE(pressure_sensor);
}

/*---------------------------------------------------------------------------*/
void config_light()
{
 light_sensor.configure(LIGHT_SENSOR_SOURCE, ISL29020_LIGHT__AMBIENT);
 light_sensor.configure(LIGHT_SENSOR_RESOLUTION, ISL29020_RESOLUTION__16bit);
 light_sensor.configure(LIGHT_SENSOR_RANGE, ISL29020_RANGE__1000lux);
 SENSORS_ACTIVATE(light_sensor);
}
/*---------------------------------------------------------------------------*/
void process_light_pressure() {

 int light_val = light_sensor.value(0);
 float light = ((float)light_val) / LIGHT_SENSOR_VALUE_SCALE;
 printf(" Light mesure: %f lux ", light);

 int pressure;
 pressure = pressure_sensor.value(0);
 printf("    Pressure measure: %f mbar\n", (float)pressure / PRESSURE_SENSOR_VALUE_SCALE);
}

