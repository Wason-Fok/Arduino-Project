#include <OSCMessage.h>
#include <OSCBoards.h>

#ifdef BOARD_HAS_USB_SERIAL
  #include <SLIPEncodedUSBSerial.h>
  SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
  #include <SLIPEncodedSerial.h>
  SLIPEncodedSerial SLIPSerial(Serial); // 对于没有串行端口的或有多个串行端口，请更改为Serial1或Serial2等
#endif


/*
Arduino OSC Controll Resolume

V1.0
By Wason Fok
*/

// 定义输出引脚
#define B1 7
#define B2 8
#define B3 9

// 声明判断当前按键状态变量
int b1, b2, b3;

// 声明上一次循环按键状态并定义初始值
int b1s = 2;
int b2s = 2;
int b3s = 2;

///////////////////////// 清空指定图层播放 /////////////////////////
void layerClear(int layer) {
  if (layer == 1) {
    OSCMessage msg("/composition/layers/1/clear");
    msg.add((int)1);
    msg.send(SLIPSerial);
    msg.empty();
  }
  if (layer == 2) {
    OSCMessage msg("/composition/layers/2/clear");
    msg.add((int)1);
    msg.send(SLIPSerial);
    msg.empty();
  }
  if (layer == 3) {
    OSCMessage msg("/composition/layers/3/clear");
    msg.add((int)1);
    msg.send(SLIPSerial);
    msg.empty();
  }
}
//////////////////////////////////////////////////////////////////


///////////////////////// 播放指定图层 /////////////////////////
void layerPlay(int layer) {
  if (layer == 1) {
    OSCMessage msg("/composition/layers/1/clips/1/connect");
    msg.add((int)1);
    msg.send(SLIPSerial);
    msg.empty();
  }
  if (layer == 2) {
    OSCMessage msg("/composition/layers/2/clips/1/connect");
    msg.add((int)1);
    msg.send(SLIPSerial);
    msg.empty();
  }
  if (layer == 3) {
    OSCMessage msg("/composition/layers/3/clips/1/connect");
    msg.add((int)1);
    msg.send(SLIPSerial);
    msg.empty();
  }
}
//////////////////////////////////////////////////////////////


void setup() {
  // 打开串口
  SLIPSerial.begin(9600);   // 此波特率设置为平台上稳定运行的最高值

  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  
  digitalWrite(B1, HIGH);
  digitalWrite(B2, HIGH);
  digitalWrite(B3, HIGH);
}


void loop(){
  // 保存当前按键状态
  b1 = digitalRead(B1); b2 = digitalRead(B2); b3 = digitalRead(B3);

  // 判断第一个按键
  if (digitalRead(B1) == LOW) {
    delay(20);
    if (digitalRead(B1) == LOW){
      if (b1s == LOW){
        // 如果按键上一次循环状态为按下，那么跳过此次触发 
      } else {
        layerPlay(1);
      }
    }
  } else {
    layerClear(1);
  }
  delay(100);

  // 判断第二个按键
  if (digitalRead(B2) == LOW) {
    delay(20);
    if (digitalRead(B2) == LOW){
      if (b2s == LOW){
        // 如果按键上一次循环状态为按下，那么跳过此次触发 
      } else {
        layerPlay(2);
      }
    }
  } else {
    layerClear(2);
  }
  delay(100);

  // 判断第三个按键
  if (digitalRead(B3) == LOW) {
    delay(20);
    if (digitalRead(B3) == LOW){
      if (b3s == LOW){
        // 如果按键上一次循环状态为按下，那么跳过此次触发 
      } else {
        layerPlay(3);
      }
    }
  } else {
    layerClear(3);
  }

  // 将当前循环的按键状态保存
  b1s = digitalRead(B1); b2s = digitalRead(B2); b3s = digitalRead(B3);
  // 循环中断，直到按键组合变更才会跳出循环
  while (b1 == digitalRead(B1) && b2 == digitalRead(B2) && b3 == digitalRead(B3)) {}
}
