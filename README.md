# Arduino_PLC_DEMO
Demo project for PLC with Arduino Nano
# ÖNSÖZ
PLC'ler (Programmable Logic Controllers), endüstriyel otomasyon süreçlerinde yaygın olarak kullanılan mikroişlemci tabanlı cihazlardır. Fabrika makinelerini, üretim hatlarını ve diğer otomasyon sistemlerini kontrol etmek için tasarlanmışlardır. PLC’ler, programlanabilir oldukları için farklı görevlerde kullanılabilirler ve elektrik devrelerine benzer mantık kontrolü sağlarlar. Dayanıklı yapıları sayesinde zorlu endüstriyel ortamlarda uzun süre çalışabilirler. Sensörlerden gelen verileri toplar, işleyerek motorları, vanaları veya diğer cihazları çalıştırır. Böylece üretim süreçlerini daha güvenli, verimli ve esnek hale getirirler. PLC dersini açan ve bize sunan sayın Y. Doç. Dr. Tuncay UZUN hocamıza teşekkür ederim.

# Abstract

This study involves the design of a PLC system built on the Arduino Nano using the ATmega328p microcontroller. The system includes both hardware and software components. It has been designed to be suitable for industrial use, with customizable software and easily accessible I/O ports. The project has been presented for the benefit of anyone interested in PLCs.
Keywords: PLC, Arduino, ATmega328, Relay

OPERAND NO	OPERAND CONTENTS
0-3	INPUTS	0-3	4 BUTON
100-103	TIMERS	100-103	
200-203	OUTPUTS	200-203	200 -> Motor
400-403	INTERNAL RELAYS	400-403	
800-803	DATA REGISTERS	800-803	
900-904	COUNTERS	900-904	102 INPUT RESET
103 INPUT COUNT
147	FUNCTIONS	18,19,20,25	18 -> increment data
19 -> decrement data
20 -> store data
25 -> display

Demo yazılımın içerdiği operand listesi yukarıdaki tabloda verilmiştir. Buton 1 e basıldığında motor dönmektedir. Buton4 ile 5 e kadar counter saymaktadır sonucunda ise 203 çıkış rölesi aktif olmaktadır. Buton3 ise counter resetlemektedir. Buton 2 ise 201 röle çıkışını aktif etmektedir.
