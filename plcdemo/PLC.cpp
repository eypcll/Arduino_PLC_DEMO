#include "PLC.h"
#include "TM1637.h"

static int digits[4] ;
TM1637 tm1637(CLK,DIO);

PLC::PLC(){};

void PLC::init()
{
  
pinMode(OUT_1, OUTPUT);
pinMode(OUT_2, OUTPUT);
pinMode(OUT_3, OUTPUT);
pinMode(OUT_4, OUTPUT);
digitalWrite(OUT_1,HIGH);
digitalWrite(OUT_2,HIGH);
digitalWrite(OUT_3,HIGH);
digitalWrite(OUT_4,HIGH);
pinMode(IN_1, INPUT_PULLUP);
pinMode(IN_2, INPUT_PULLUP);
pinMode(IN_3, INPUT_PULLUP);
pinMode(IN_4, INPUT_PULLUP);

tone(BuzzerPin,262);

tm1637.init();
tm1637.set(BRIGHT_TYPICAL); 
}


void PLC::reset()
{
  
  last_relay = 0;
  last_data = 0;
  current_relay = 0;
  current_data = 0;


  last_load = 0;
}


int* PLC::get_digits(uint32_t value)
{
  
  digits[0] = value/1000;
  digits[1] = value/100 - digits[0]*10;
  digits[2] = value/10 - digits[0]*100 - digits[1]*10;
  digits[3] = value - digits[0]*1000 - digits[1]*100 - digits[2]*10;
  return digits;
}

uint32_t PLC::get_data(uint32_t relay_number,bool old=false)
{
  int *res = get_digits(relay_number);

  last_relay = current_relay;
  current_relay = relay_number;
  switch(res[1])
  {
    case 0:
    if (old == true){return inputs[res[3]][3];}
    current_data = !digitalRead(inputs[res[3]][1]);
    set_data(relay_number);
    return current_data;
    break;
    case 1:
    if (old == true){return timers[res[3]][2];}
    return timers[res[3]][1];
    break;
    case 2:
    if (old == true){return output_relays[res[3]][3];}
    return output_relays[res[3]][2];
    break;
    case 3:
    break;
    case 4:
    if (old == true){return internal_relays[res[3]][2];}
    return internal_relays[res[3]][1];
    break;
    case 8:
    if (old == true){return data_register[res[3]][2];}
    return data_register[res[3]][1];
    break;
    case 9:
    if (old == true){return counters[res[3]][2];}
    return counters[res[3]][1];
    break;
  }

  return 1;
}

void PLC::set_data(uint32_t relay_number)
{
  int *res = get_digits(relay_number);

  switch(res[1])
  {
    case 0:
    if (current_data != inputs[res[3]][2]) {
      inputs[res[3]][3] = inputs[res[3]][2];
      inputs[res[3]][2] = current_data;
      }
    break;
    case 1:
    if (current_data != timers[res[3]][1]) {
      timers[res[3]][2] = timers[res[3]][1];
      timers[res[3]][1] = current_data;
      }
    break;
    case 2:
    if (current_data==1) {digitalWrite(output_relays[res[3]][1],LOW);} 
    else {digitalWrite(output_relays[res[3]][1],HIGH);}
    if (current_data != output_relays[res[3]][2]) {
      output_relays[res[3]][3] = output_relays[res[3]][2];
      output_relays[res[3]][2] = current_data;
      }
    break;
    case 3:
    break;
    case 4:
    if (current_data != internal_relays[res[3]][1]) {
      internal_relays[res[3]][2] = internal_relays[res[3]][1];
      internal_relays[res[3]][1] = current_data;
      }
    break;
    case 8:
    if (current_data != data_register[res[3]][1]) {
      data_register[res[3]][2] = data_register[res[3]][1];
      data_register[res[3]][1] = current_data;
      }
    break;
    case 9:
    if (current_data != counters[res[3]][1]) {
      counters[res[3]][2] = counters[res[3]][1];
      counters[res[3]][1] = current_data;
      }
    break;
  }

}

void PLC::display(uint32_t value)
{
  int *res = get_digits(value);
  tm1637.display(0,res[0]);
  tm1637.display(1,res[1]);
  tm1637.display(2,res[2]);
  tm1637.display(3,res[3]);
}

void PLC::out(uint32_t relay_number)
{
  set_data(relay_number);
}

uint32_t PLC::__and(uint32_t f,uint32_t s)
{
  if ((f == 1) && (s == 1)){return 1;}
  else{return 0;}
}

uint32_t PLC::__or(uint32_t f,uint32_t s)
{
  if ((f == 1) || (s == 1)){return 1;}
  else{return 0;}
}

uint32_t PLC::__not(uint32_t f) {return !f;}

void PLC::load(uint32_t select_relay)
{
  last_data = current_data;
  current_data = get_data(select_relay);
  last_load = current_data;
}
void PLC::loadnot(uint32_t select_relay)
{
  load(select_relay);
  last_load = __not(last_load);
  current_data = last_load;
}


void PLC::orload(uint32_t select_relay)
{
  uint32_t temp_load = last_load;
  load(select_relay);
  last_load = __or(temp_load,last_load);
  current_data = last_load;
}

void PLC::andload(uint32_t select_relay)
{
  uint32_t temp_load = last_load;
  load(select_relay);
  last_load = __and(temp_load,last_load);
  current_data = last_load;
}

void PLC::andnotload(uint32_t select_relay)
{
  uint32_t temp_load = last_load;
  loadnot(select_relay);
  last_load = __and(temp_load,last_load);
  current_data = last_load;
}

void PLC::ornotload(uint32_t select_relay)
{
  uint32_t temp_load = last_load;
  loadnot(select_relay);
  last_load = __or(temp_load,last_load);
  current_data = last_load;
}


void PLC::func(uint32_t func_relay,int func_number)
{

  switch(func_relay)
  {
    case 147:
      switch(func_number)
      {
          case 18: // increment
          current_data = get_data(current_relay);
          current_data +=1;
          if ((current_data <0) || (current_data>9999)) {current_data = 0;}
          set_data(current_relay);
          break;
          case 19: // decrement
          current_data = get_data(current_relay);
          current_data -=1;
          if ((current_data <0) || (current_data>9999)) {current_data = 0;}
          set_data(current_relay);
          break; 
          case 20: // store data
          set_data(current_relay);
          break; 
          case 25: // display
          display(current_data);
          break; 
      }

    
    break;
    default:
    break;
  }
}

void PLC::counter(int counter_relay_number , uint32_t preset_value,bool latch=true)
{
  int reset = last_data;
  int pulse = current_data;
  int old_pulse =0;
  if (latch == true) {old_pulse = get_data(current_relay,true);}
  
  load(counter_relay_number);
  if (reset == 1) {current_data = 0 ;func(147,20);}
  else if ((pulse == 1)&&(old_pulse == 0)) {func(147,18);func(147,20);}

  load(counter_relay_number);
  if (current_data == preset_value) {current_data = 1;}
  else if (current_data > preset_value) {current_data = 0 ;func(147,20);}
  else {current_data=0;}


}


unsigned long PLC::get_timer_ts(uint32_t timer_number)
{
  if (timer_number == 100) return Timer1;
  else if (timer_number == 101) return Timer2;
  else if (timer_number == 102) return Timer3;
  else if (timer_number == 103) return Timer4;
}
void PLC::set_timer_ts(uint32_t timer_number , unsigned long ts)
{
  if (timer_number == 100) Timer1 = ts;
  else if (timer_number == 101) Timer2 = ts;
  else if (timer_number == 102) Timer3 = ts;
  else if (timer_number == 103) Timer4 = ts;
}

void PLC::timer(uint32_t timer_number , uint32_t preset_value)
{
  
  // int reset = get_data(current_relay,true);
  int pulse = last_load;
  // Serial.println(pulse);

  load(timer_number);
  if (pulse == 0) {current_data = 0 ;func(147,20);}
  else if ((pulse == 1)) {
    unsigned long timer_ts = get_timer_ts(timer_number);
    if (millis()- timer_ts>100){
      func(147,18);func(147,20);
      set_timer_ts(timer_number,millis());
    }}

  load(timer_number);
  if (current_data >= preset_value) {current_data = 1;}
  else {current_data=0;}


}

void PLC::print_debug()
{
  // Serial.println("====");
  // Serial.print("RELAY -> ");
  // Serial.print(current_relay);
  // Serial.print(" BOOL -> ");
  // Serial.print(current_data);
  // Serial.println("\n----");
  Serial.print("inputs -> ");
  load(0);
  Serial.print(current_data);
  load(1);
  Serial.print(current_data);
  load(2);
  Serial.print(current_data);
  load(3);
  Serial.println(current_data);
  Serial.print("outputs -> ");
  load(200);
  Serial.print(current_data);
  load(201);
  Serial.print(current_data);
  load(202);
  Serial.print(current_data);
  load(203);
  Serial.println(current_data);
}