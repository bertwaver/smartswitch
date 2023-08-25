#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#include <Blinker.h>
#include <Servo.h>


Servo myservo;//定义舵机

char auth[] = "";  //点灯Key
char ssid[] = "";      //wifi名称
char pswd[] = "";     //wifi密码

// 新建组件对象
BlinkerButton Button1("test");
BlinkerButton Button2("resetc");
BlinkerButton Button3("tjdw");


int counter = 0;
int light_state=-1;


void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        myservo.write(140);
        delay(110);
        myservo.write(90);
       light_state=1;

        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
       myservo.write(45);
       delay(100);
       myservo.write(90);
        light_state=0;

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}


void miotColor(int32_t color)
{
    BLINKER_LOG("need set color: ", color);

    if(light_state==-1 or light_state==1)
    {
          BlinkerMIOT.print();
        myservo.write(45);
       delay(100);
       myservo.write(90);
       light_state=0;

       delay(350);

        myservo.write(140);
        delay(110);
        myservo.write(90);
        light_state=1;
    }
    else if(light_state==0)
    {
          BlinkerMIOT.print();
        myservo.write(140);
        delay(110);
        myservo.write(90);
       light_state=1;
    }

    BlinkerMIOT.color(color);
}


void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    if (state=="on") 
    {
      if(light_state==-1 or light_state==0)
      {
        myservo.write(140);
        delay(110);
        myservo.write(90);
       light_state=1;
       Blinker.print("命令已经执行。");
      }
      else if(light_state==1)
      {
       Blinker.print("命令没有执行，因为处于锁定状态。");
      }

    } else if(state=="tap")
    {
      if(light_state==-1 or light_state==1)
      {
       myservo.write(35);
       delay(100);
       myservo.write(90);
        light_state=0;
        Blinker.print("命令已经执行。");
      }
      else if(light_state==0)
      {
       Blinker.print("命令没有执行，因为处于锁定状态。");
      }
    }
        
}

void button2_callback(const String & state)
{
      BLINKER_LOG("get button state: ", state);
      light_state=-1;
      Blinker.print("执行了一次解除锁定操作。");
}

void button3_callback(const String & state)
{
      BLINKER_LOG("get button state: ", state);

    if(light_state==-1 or light_state==1)
    {
        myservo.write(45);
       delay(100);
       myservo.write(90);
       light_state=0;

       delay(350);

        myservo.write(140);
        delay(110);
        myservo.write(90);
        light_state=1;
    }
    else if(light_state==0)
    {
        myservo.write(140);
        delay(110);
        myservo.write(90);
       light_state=1;
    }

      Blinker.print("执行了一次调节灯温操作。");
}

void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
 
}

void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, HIGH);

    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    myservo.attach(2);
    myservo.write(90);
  
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);

    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachColor(miotColor);

}

void loop() {
     digitalWrite(LED_BUILTIN, HIGH);
     Blinker.run();
     digitalWrite(LED_BUILTIN, HIGH);

}
