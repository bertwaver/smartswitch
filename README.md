## SmartSwitch
-----------------------
基于esp8266的自动开关灯系统-单片机主程序
-----------------------
**实现原理 **

通过控制连接在单片机上的舵机的旋转角度/速度/方向以实现控制电灯等家用电器的开关。
本实现原理相较于使用继电器控制而言，无需改造家庭电路，更安全，维护更方便。
-----------------------
**使用方法 **

1.安装 arduinoide
2.打开smartswitch.ino文件并修改代码。
3.安装blinker库/esp8266库【同时也安装一下esp8266的驱动，不然有可能识别不到串口】
4.修改代码以满足需求
5.编译通过后就可以上传到单片机主板了qwq
-----------------------
**小爱音响控制 **

本项目代码中已经添加了小爱音箱控制的相关代码，如不需要使用改功能，请将下面的代码注释掉。
```cpp
#define BLINKER_MIOT_LIGHT
```
```cpp
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
```
-----------------------
**注意事项 **

单片机控制代码由c++编写，相较于其它语言在执行速度上已经有不小的优势。但是由于esp8266(以nodemcu为例)性能较鸡肋。当代码过多/定义变量过多时，仍然有可能出现指令延迟/死机等问题。
另外，在使用的过程中，要注意供电问题。【有时候舵机按不动开关可能不是代码的问题，而可能是接入单片机的电池/充电宝没电了】
在接入舵机时，一定要注意，不要将正负极反接，修改io口请更改下方的代码：
```cpp
myservo.attach(2);
```
-----------------------
**客户端 **

手机控制客户端请使用点灯blinker的手机版客户端。
电脑控制可以使用我编写的blinker电脑版客户端，本客户端支持自动登录。
https://github.com/bertwaver/blinker_Win
-----------------------
**鸣谢 **

arduino(https://www.arduino.cc/en/software)
点灯(https://www.diandeng.tech/home)

