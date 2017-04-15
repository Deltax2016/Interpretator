#include <LiquidCrystal_I2C.h>

#include <DHT.h>
#include <Wire.h>

#define DHTTYPE DHT11
DHT dht(2, DHTTYPE, 11);
class Inter
{
  public:
    void parse1(String a)
    {
      while (a.length() > 1)
      {
        switch (a[0])
        {
          case 'P':
            {
              do1(a.substring(0, 3));
              a.remove(0, 3);
              break;
            }
          case 'W':
            {
              do1(a.substring(0, 5));
              a.remove(0, 5);
              break;
            }
          case 'A':
            {
              do1(a.substring(0, 5));
              a.remove(0, 5);
              break;
            }
          case 'D':
            {
              do1(a.substring(0, 3));
              a.remove(0, 3);
              break;
            }
          case 'H':
            {
              do1(a.substring(0, 3));
              a.remove(0, 3);
              break;
            }
          case 'I':
            {
              do1(a.substring(0, 2));
              a.remove(0, 2);
              break;
            }
           case 'С':
            {
              c = a[1] - 48;
              do1(a.substring(0, c));
              a.remove(0, c);
              break;
            }
          default:
            {
              return;
            }
        }
      }
    }
    unsigned int toBin(String a)
    {
      unsigned int d = 256, q;
      q += a[1];
      q += a[0] * 256;
      //q+=a[1]*65536;
      //q+=a[0]*16777216;
      return q;
    }
    void do1(String a)
    {
      Serial.println(a);
      switch (a[0])
      {
        case 'P':
          {
            int c = a[1] - 48;
            pinMode(c, OUTPUT);
            switch (a[2])
            {
              case '0':
                {
                  digitalWrite(c, LOW);
                  Serial.println(c);
                  Serial.println("LOW");
                  break;
                }
              case '1':
                {
                  digitalWrite(c, HIGH);
                  Serial.println(c);
                  Serial.println("HIGH");
                  break;
                }
            }
            break;
          }
        case 'W':
          {
            int c = a[1] - 48;
            pinMode(c, OUTPUT);
            analogWrite(c, a.substring(2, 5).toInt());
          }
        case 'A':
          {
            if (a[1] == '1') analogWrite(A0, a.substring(2, 5).toInt());
            if (a[1] == '0') Serial.println(analogRead(A0));
          }
         case 'I':
          {
            Serial.println(a[1]-48, DEC);
          }
        case 'D':
          {
            //Serial.println(toBin(a.substring(1,3)),DEC);
            //ESP.wdtDisable();
            //delay(toBin(a.substring(1,3)));
            //ESP.wdtEnable();
          }
        case 'H':
          {
            if (a[1] == '0')
            {
              char b[5];
              Wire.begin(0,2);
              byte address = 0x5C;
              Wire.beginTransmission(address);
              Wire.write(0);
              Wire.endTransmission();
              Wire.requestFrom(address, 5);
              b[0] = Wire.read();
              b[1] = Wire.read();
              b[2] = Wire.read();
              b[3] = Wire.read();
              b[4] = Wire.read();
              Serial.print(b[0], DEC);
              Serial.print('.');
              Serial.print(b[1], DEC);
              Serial.println('%');
              Serial.print(b[2], DEC);
              Serial.print('.');
              Serial.print(b[3], DEC);
              Serial.println('C');
            }
            else
            {
              Serial.println(dht.readHumidity());
              Serial.println(dht.readTemperature());
            }
          }
      }
    }
};

Inter inte;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello, world!");
  dht.begin();
}

void loop()
{
  if (Serial.available()) inte.parse1((Serial.readString()));

}
