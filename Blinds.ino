#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL41ZJTmHHu"
#define BLYNK_TEMPLATE_NAME "Blinds"
#define BLYNK_AUTH_TOKEN "jsdBf32vz-ygK5tke-F3eHqV_sSC6864"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Stepper.h>

#define STEPS 64

char auth[] = BLYNK_AUTH_TOKEN;

Stepper stepper(STEPS, D1, D3, D2, D4);

char ssid[] = "DMP_13";
char pass[] = "Rufas_240813";

boolean closed = false;
boolean opened = true;

void disable_motor() //Varikliuko išjungimas
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void setup()
{
  pinMode(D0, OUTPUT); 
  digitalWrite(D0, HIGH); 
  Serial.begin(9600);

  stepper.setSpeed(500); //Greičio nustatymas

  Blynk.begin(auth, ssid, pass);

  digitalWrite(D0, LOW); 
  pinMode(LED_BUILTIN, OUTPUT);  
}

BLYNK_WRITE(V1) //Užuolaidų uždarymas
{
  Serial.println("Closing Blinds");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH);  

  if (opened == true)
  {
    for (int c_val = 0; c_val <= 120; c_val++) //Sukimas palei laikrodžio rodyklę
    {
      stepper.step(c_val);
      yield();
    }

    closed = true;
    opened = false;
    disable_motor();
  }
}

BLYNK_WRITE(V2) //Užuolaidų atidarymas
{
  Serial.println("Opening Blinds");
  if (closed == true)
  {
    for (int cc_val = 0; cc_val >= -120; cc_val--) //Sukimas prieš laikrodžio rodyklę
    {
      stepper.step(cc_val);
      yield();
    }
    opened = true;
    closed = false;
  }
  disable_motor();
}

void loop()
{
  Blynk.run();
}