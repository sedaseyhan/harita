#include "SoftwareSerial.h"
//RX-TX PINLERI AYARLA
SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00
# define ACTIVATED LOW
int buttonNiksar = 2;
int buttonTurhal = 3;
int buttonZile = 5;
int buttonErbag = 6;
boolean isPlaying = false;
void setup () {
pinMode(buttonNiksar, INPUT);
digitalWrite(buttonNiksar, HIGH);
pinMode(buttonTurhal, INPUT);
digitalWrite(buttonTurhal, HIGH);
pinMode(buttonZile, INPUT);
digitalWrite(buttonZile, HIGH);
pinMode(buttonErbag, INPUT);
digitalWrite(buttonErbag, HIGH);
mySerial.begin (9600);
delay(1000);
//playFirst();
isPlaying = true;
}
void loop () {



if (digitalRead(buttonNiksar) == ACTIVATED) //
{
if (isPlaying)
{
playFirst();
}
}



if (digitalRead(buttonTurhal) == ACTIVATED) //
{
if (isPlaying)
{
playFirst();
playNext();
}
}
if (digitalRead(buttonZile) == ACTIVATED) //
{
if (isPlaying)
{
playFirst();
playNext();
playNext();
}
}

if (digitalRead(buttonErbag) == ACTIVATED) //
{
if (isPlaying)
{
playFirst();
playNext();
playNext();
playNext();
}
}
}

void playFirst() // İlk mp3 sırası kodu
{
execute_CMD(0x3F, 0, 0);
delay(100);
setVolume(20);
delay(100);
execute_CMD(0x11, 0, 1);
delay(100);
}

void play() // çalma kodu
{
execute_CMD(0x0D, 0, 1);
delay(100);
}
void playNext() // sonraki mp3 kodu
{
execute_CMD(0x01, 0, 1);
delay(500);
}
void setVolume(int volume)
{
execute_CMD(0x06, 0, volume); // ses şiddeti
delay(2000);
}
void execute_CMD(byte CMD, byte Par1, byte Par2)
// kod doğrulunu kontrol ve kod gönderimi
{
// doğrulama byte hesabı (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
};
//Send the command line to the module
for (byte k = 0; k < 10; k++)
{
mySerial.write( Command_line[k]);
}
}
