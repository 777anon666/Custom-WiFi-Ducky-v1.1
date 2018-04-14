#include <Keyboard.h>
#define BAUD_RATE 57200

#define ExternSerial Serial1

String bufferStr = "";
String last = "";

int defaultDelay = 0;

// ================================================= SHORTCUTS =================================================

void MENU()
{
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F10);
  Keyboard.releaseAll();
}

void CMD()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(600);
  Keyboard.print("cmd");
  delay(50);
  Keyboard.press(KEY_RETURN);
}

void CMDUAC()
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_ESC);
  Keyboard.releaseAll();
  delay(800);
  Keyboard.print("cmd");
  delay(5000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(5000);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
}
void RIBBONS()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(600);
  Keyboard.print("C:/Windows/System32/Ribbons.scr");
  delay(50);
  Keyboard.press(KEY_RETURN);
}

void IPCONFIG()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(600);
  Keyboard.print("CMD");
  delay(50);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.print ("ipconfig");
  delay(500);
  Keyboard.press(KEY_RETURN);
}

// ======================================== SHORTCUTS: ENVIRONMENT VARS ========================================

void DESKTOP() {
  Keyboard.print("cd %userprofile%/Desktop");
  Keyboard.press(KEY_RETURN);
}

void WINDIR() {
  Keyboard.print("cd %windir%");
  Keyboard.press(KEY_RETURN);
}

void TMP() {
  Keyboard.print("cd %windir%");
  Keyboard.press(KEY_RETURN);
}

void USER() {
  Keyboard.print("cd %userprofile%");
  Keyboard.press(KEY_RETURN);
}

void Line(String _line)
{
  int firstSpace = _line.indexOf(" ");
  if(firstSpace == -1) Press(_line);
  else if(_line.substring(0,firstSpace) == "STRING"){
    for(int i=firstSpace+1;i<_line.length();i++) Keyboard.write(_line[i]);
  }
  else if(_line.substring(0,firstSpace) == "DELAY"){
    int delaytime = _line.substring(firstSpace + 1).toInt();
    delay(delaytime);
  }
  else if(_line.substring(0,firstSpace) == "DEFAULTDELAY") defaultDelay = _line.substring(firstSpace + 1).toInt();
  else if(_line.substring(0,firstSpace) == "REM"){} //nothing :/
  else if(_line.substring(0,firstSpace) == "REPLAY") {
    int replaynum = _line.substring(firstSpace + 1).toInt();
    while(replaynum)
    {
      Line(last);
      --replaynum;
    }
  } else{
      String remain = _line;

      while(remain.length() > 0){
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1){
          Press(remain);
          remain = "";
        }
        else{
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
  delay(defaultDelay);
}

  
void Press(String b){
  if(b.length() == 1) Keyboard.press(char(b[0]));
  else if (b.equals("ENTER")) Keyboard.press(KEY_RETURN);
  else if (b.equals("CTRL")) Keyboard.press(KEY_LEFT_CTRL);
  else if (b.equals("SHIFT")) Keyboard.press(KEY_LEFT_SHIFT);
  else if (b.equals("ALT")) Keyboard.press(KEY_LEFT_ALT);
  else if (b.equals("GUI")) Keyboard.press(KEY_LEFT_GUI);
  else if (b.equals("UP") || b.equals("UPARROW")) Keyboard.press(KEY_UP_ARROW);
  else if (b.equals("DOWN") || b.equals("DOWNARROW")) Keyboard.press(KEY_DOWN_ARROW);
  else if (b.equals("LEFT") || b.equals("LEFTARROW")) Keyboard.press(KEY_LEFT_ARROW);
  else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) Keyboard.press(KEY_RIGHT_ARROW);
  else if (b.equals("DELETE")) Keyboard.press(KEY_DELETE);
  else if (b.equals("PAGEUP")) Keyboard.press(KEY_PAGE_UP);
  else if (b.equals("PAGEDOWN")) Keyboard.press(KEY_PAGE_DOWN);
  else if (b.equals("HOME")) Keyboard.press(KEY_HOME);
  else if (b.equals("ESC")) Keyboard.press(KEY_ESC);
  else if (b.equals("INSERT")) Keyboard.press(KEY_INSERT);
  else if (b.equals("TAB")) Keyboard.press(KEY_TAB);
  else if (b.equals("END")) Keyboard.press(KEY_END);
  else if (b.equals("CAPSLOCK")) Keyboard.press(KEY_CAPS_LOCK);
  else if (b.equals("F1")) Keyboard.press(KEY_F1);
  else if (b.equals("F2")) Keyboard.press(KEY_F2);
  else if (b.equals("F3")) Keyboard.press(KEY_F3);
  else if (b.equals("F4")) Keyboard.press(KEY_F4);
  else if (b.equals("F5")) Keyboard.press(KEY_F5);
  else if (b.equals("F6")) Keyboard.press(KEY_F6);
  else if (b.equals("F7")) Keyboard.press(KEY_F7);
  else if (b.equals("F8")) Keyboard.press(KEY_F8);
  else if (b.equals("F9")) Keyboard.press(KEY_F9);
  else if (b.equals("F10")) Keyboard.press(KEY_F10);
  else if (b.equals("F11")) Keyboard.press(KEY_F11);
  else if (b.equals("F12")) Keyboard.press(KEY_F12);
  else if (b.equals("SPACE")) Keyboard.press(' ');
  //else Serial.println("not found :'"+b+"'("+String(b.length())+")");


 // SHORTCUTS
  
  else if (b.equals("MENU")) MENU();
  else if (b.equals("RIBBONS")) RIBBONS();
  else if (b.equals("CMD")) CMD();
  else if (b.equals("CMDUAC")) CMDUAC();
  else if (b.equals("IPCONFIG")) IPCONFIG();

  // ENVIRONMENT VARIABLES

  else if (b.equals("DESKTOP")) DESKTOP();
  else if (b.equals("WINDIR")) WINDIR();
  else if (b.equals("TMP")) TMP();
  else if (b.equals("USER")) USER();
}
void setup() {
  
  Serial.begin(BAUD_RATE);
  ExternSerial.begin(BAUD_RATE);

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  Keyboard.begin();
}

void loop() {
  if(ExternSerial.available()) {
    bufferStr = ExternSerial.readStringUntil("END");
    Serial.println(bufferStr);
  }
  
  if(bufferStr.length() > 0){
    
    bufferStr.replace("\r","\n");
    bufferStr.replace("\n\n","\n");
    
    while(bufferStr.length() > 0){
      int latest_return = bufferStr.indexOf("\n");
      if(latest_return == -1){
        Serial.println("run: "+bufferStr);
        Line(bufferStr);
        bufferStr = "";
      } else{
        Serial.println("run: '"+bufferStr.substring(0, latest_return)+"'");
        Line(bufferStr.substring(0, latest_return));
        last=bufferStr.substring(0, latest_return);
        bufferStr = bufferStr.substring(latest_return + 1);
      }
    }
    
    bufferStr = "";
    ExternSerial.write(0x99);
    Serial.println("done");
  }
}

