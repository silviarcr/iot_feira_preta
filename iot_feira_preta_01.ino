
//
//https://www.mocky.io/
//http://www.mocky.io/v2/5aa0889e3200006511e9fcdd
#include <UIPEthernet.h>
#include <RestClient.h>
const int luz_verde = 2;
const int luz_amarela = 4;
const int luz_vermelha = 7;
int intervalo_atualizacao = 1000;

//Ethernet
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x77};
EthernetClient ethClient;

RestClient client("http://www.mocky.io/v2/5aa0889e3200006511e9fcdd", ethClient);


void setup() {
  // put your setup code here, to run once:
  pinMode(luz_verde, OUTPUT);
  pinMode(luz_amarela, OUTPUT);
  pinMode(luz_vermelha, OUTPUT);
  Serial.begin(9600);

  if(Ethernet.begin(mac)) {
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println(F("Falha na inicialização Ethernet"));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  while (Serial.available()) {

    char voto = Serial.read();

    switch (voto) {
      case '1':
        digitalWrite(luz_verde, HIGH);
        digitalWrite(luz_amarela, LOW);
        digitalWrite(luz_vermelha, LOW);
        Serial.println("verde");
        break;
      case '2':
        digitalWrite(luz_verde, LOW);
        digitalWrite(luz_amarela, HIGH);
        digitalWrite(luz_vermelha, LOW);
        Serial.println("amarela");
        break;
      case '3':
        digitalWrite(luz_verde, LOW);
        digitalWrite(luz_amarela, LOW);
        digitalWrite(luz_vermelha, HIGH);
        Serial.println("vermelha");
        break;
      default:
        digitalWrite(luz_verde, LOW);
        digitalWrite(luz_amarela, LOW);
        digitalWrite(luz_vermelha, LOW);
    }

  }
  delay(intervalo_atualizacao);
}
