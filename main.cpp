#include "mbed.h"
//#include <stdio.h>
//#include <string.h>

AnalogIn analog_X(PC_2); // 조이스틱 X 축
AnalogIn analog_Y(PC_3); // 조이스틱 Y 축
Ticker ticker; // 주기적인 작업을 위한 타이머


BufferedSerial pc(USBTX, USBRX); // PC와의 통신
BufferedSerial mp(PA_15, PB_7); // 블루투스 모듈과의 통신

void checkJoystick() {
    double x = analog_X.read(); // X 축 값 읽기
    double y = analog_Y.read(); // Y 축 값 읽기

    // 조이스틱 상태에 따라 문자로 변환하여 블루투스로 전송
    if(x > 0.7) mp.putc('R'); // 오른쪽
    else if(x < 0.3) mp.putc('L'); // 왼쪽
    else if(y > 0.7) mp.putc('G'); // 위
    else if(y < 0.3) mp.putc('B'); // 아래
}

void setup() {
    pc.baud(9600);
    mp.baud(9600);
    ticker.attach(&checkJoystick, 0.5); // 0.5초마다 조이스틱 상태 확인
}

int main() {
    setup();
    checkJoystick();
    while(1) {
    }
}
