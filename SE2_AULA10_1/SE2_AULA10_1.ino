#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "REDETESTE"
#define STAPSK  "REDETESTE"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

String newHostname = "TB-G1"; // Substitua X pela letra da sua turma e Y pelo número do seu grupo

// Criar uma instancia do servidor e qual porta será usada
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Prepara o LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Conecta a rede WIFI
  Serial.println();
  Serial.println();
  Serial.print(F("Conectando a  "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi conectado"));

  // Inicia o servidor
  server.begin();
  Serial.println(F("Servidor Inciado"));

  // Exibe o endereco IP
  Serial.println(WiFi.localIP());
}

void loop() {
  // Verifica se o cliente esta conectado
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("Novo cliente"));

  client.setTimeout(5000); // padrao e 1000

  // Le a primiera linha da requisicao
  String req = client.readStringUntil('\r');
  Serial.println(F("Requisicao: "));
  Serial.println(req);

  // Responde o pedido
  int val;
  if (req.indexOf(F("?Desliga=")) != -1) {
    val = 1;
  } else if (req.indexOf(F("?Liga=")) != -1) {
    val = 0;
  } else {
    Serial.println(F("Requisicao invalida"));
    val = digitalRead(LED_BUILTIN);
  }

  // Configura o LED de acordo com a requisicao
  digitalWrite(LED_BUILTIN, val);

  // Le e ignora o resto da requisicao
  while (client.available()) {
    // Byte a byte não é muito eficiente
    client.read();
  }

  // Envia a resposta ao cliente
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n "));
  client.print(F("<h1><html style=\"font-size:14px\"> Menu ESP8266 \n</h1>"));
  client.print(F("<body>\n"));
  client.print(F("<form action=\"http://"));
  
  client.print(WiFi.localIP());
  
  client.print(F("\" method=\"get\">\n"));
  client.print(F("<b><br></br><html style=\"font-size:14px\"> Ligar LED da placa do ESP8266\n</b>"));
  client.print(F("<p></p><button input name=\"Desliga\"style=\"height:20px;width:150px;font-size:13px\" >Desligar</button>"));//<br></br>
  client.print(F("<button input name=\"Liga\" style=\"height:20px;width:150px;font-size:13px\" >Ligar</button>"));
  client.print(F("<p></p>"));
  client.print(F("</form>\n"));
  client.print(F("<br><br><b>Integrantes: </b>Josicleide, Kaua, Larissa, Sergio e Roberto")); // Integrantes do grupo
  client.print(F("</body>\n"));
  client.print(F("</html>"));

  // O cliente será realmente *limpo* e desconectado
  // quando a função retorna e o objeto 'cliente' é destruído (fora do escopo)
  // flush = garante que os dados escritos sejam recebidos pelo outro lado
  Serial.println(F("Desconectando do cliente"));
}
