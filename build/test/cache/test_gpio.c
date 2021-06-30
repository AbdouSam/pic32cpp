#include "build/temp/_test_gpio.c"
#include "src/gpio.h"
#include "test/support/xc_stub.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"










extern volatile uint32_t TRISB;

extern volatile uint32_t LATB;

extern volatile uint32_t PORTB;



void setUp(void)

{

  gpio_init();

}



void tearDown(void)

{

}













void test_gpio_is_input_or_ouput_after_init(void)

{





    do {if ((gpio_isinput(pinB0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(32)));}} while(0);











    do {if ((gpio_isoutput(pinB12))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(38)));}} while(0);







}









void test_gpio_set_b12_opposite_direction_then_read_it(void)

{



    gpio_input_set(pinB12);

    do {if ((gpio_isinput(pinB12))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(51)));}} while(0);









}





void test_gpio_get_state_of_output_at_init_is_clear(void)

{

  do {if (!(gpio_state_get(pinB12))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(61)));}} while(0);

}















void test_gpio_set_state_of_output_then_get_state(void)

{



  uint32_t old_value_portb;

  uint32_t old_value_latb;



  do {if (!(gpio_state_get(pinB12))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(76)));}} while(0);



  old_value_latb = LATB;

  gpio_state_set(pinB12);





  old_value_portb = PORTB;

  PORTB = LATB;

  do {if ((gpio_state_get(pinB12))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(84)));}} while(0);





  PORTB = old_value_portb;

  LATB = old_value_latb;

}



void test_gpio_toggle_output_changes_its_state(void)

{

  uint32_t old_value_portb;

  uint32_t old_value_latb;



  do {if (!(gpio_state_get(pinB12))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(96)));}} while(0);

  old_value_latb = LATB;



  gpio_state_toggle(pinB12);



  old_value_portb = PORTB;

  PORTB = LATB;



  do {if ((gpio_state_get(pinB12))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(104)));}} while(0);





  PORTB = old_value_portb;

  LATB = old_value_latb;

}
