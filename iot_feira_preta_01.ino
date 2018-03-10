#include <UIPEthernet.h>
#include <RestClient.h>
const int luz_verde = 2;
const int luz_amarela = 4;
const int luz_vermelha = 7;
int intervalo_atualizacao = 1000;

// Enter a MAC address for your controller below.
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x77};

EthernetClient client;
RestClient restClient("192.168.2.36", 3000, client);

void setup() {
  // put your setup code here, to run once:
  pinMode(luz_verde, OUTPUT);
  pinMode(luz_amarela, OUTPUT);
  pinMode(luz_vermelha, OUTPUT);
  Serial.begin(9600);

  if (Ethernet.begin(mac)) {
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println(F("Falha na inicialização Ethernet"));
  }
}

void loop() {
  char resposta[16] = {};
  int statusCode = restClient.get("/", resposta, 16);
  if (statusCode == 200) {
    Serial.println(F("Recebi resposta"));
    char voto = resposta[0];
    Serial.println(resposta);
    atualizarLampadas(voto);
  } else {
    Serial.println(F("Falhou!"));
    Serial.println(statusCode);
  }

  resposta[0] = 0;

  delay(intervalo_atualizacao);
}

void atualizarLampadas(int voto) {
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

