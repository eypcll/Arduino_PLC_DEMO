#ifndef PLC_h   /* Include guard */
#define PLC_h
#include <Arduino.h>
#include <inttypes.h>

#define OUT_1 12
#define OUT_2 11
#define OUT_3 10
#define OUT_4 9
#define IN_1 8
#define IN_2 7
#define IN_3 6
#define IN_4 5
#define CLK 3//Pins for TM1637       
#define DIO 4
#define BuzzerPin 2

class PLC
{
  public:
    int entry = 4321;
    // bool pin_value = false;
    uint32_t last_relay;
    uint32_t last_data;
    uint32_t current_relay;
    uint32_t current_data;
    unsigned long StartTime = 0;
    unsigned long Timer1 = 0;
    unsigned long Timer2 = 0;
    unsigned long Timer3 = 0;
    unsigned long Timer4 = 0;


    uint32_t last_load = 0;


    int inputs[4][4] = {{0,8,0,0},{1,7,0,0},{2,6,0,0},{3,5,0,0}};
    int func_relays[1] = {147};
    uint32_t timers[4][3] = {{100,0,0},{101,0,0},{102,0,0},{103,0,0}};
    int output_relays[4][4] = {{200,12,0,0},{201,11,0,0},{202,10,0,0},{203,9,0,0}};
    int internal_relays[4][3] = {{400,0,0},{401,0,0},{402,0,0},{403,0,0}};
    uint32_t data_register[4][3] = {{800,0,0},{801,0,0},{802,0,0},{803,0,0}};
    uint32_t counters[4][3] = {{900,0,0},{901,0,0},{902,0,0},{903,0,0}};

    PLC(void);
    void init(void);
    void reset(void);
    unsigned long get_timer_ts(uint32_t timer_number);
    void set_timer_ts(uint32_t timer_number , unsigned long ts);
    void print_debug(void);
    void timer(uint32_t timer_number , uint32_t preset_value);
    void counter(int counter_relay_number , uint32_t preset_value,bool latch=true);
    void func(uint32_t func_relay,int func_number);
    void ornotload(uint32_t select_relay);
    void andnotload(uint32_t select_relay);
    void andload(uint32_t select_relay);
    void orload(uint32_t select_relay);
    void loadnot(uint32_t select_relay);
    void load(uint32_t select_relay);
    uint32_t __not(uint32_t f);
    uint32_t __or(uint32_t f,uint32_t s);
    uint32_t __and(uint32_t f,uint32_t s);
    void out(uint32_t relay_number);
    void display(uint32_t value);
    void set_data(uint32_t relay_number);
    uint32_t get_data(uint32_t relay_number,bool old=false);
    int* get_digits(uint32_t value);

};




#endif //