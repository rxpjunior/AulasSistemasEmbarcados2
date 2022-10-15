int PinoAnalogico = A0; // Define o pino A0 como Pino Analógico do sensor
int EstadoSensor = 0;
int UltimoEstSensor = 0;
int ValAnalogIn; // Valor analógico no código
void setup() {
Serial.begin(115200);
}
void loop() {
ValAnalogIn = analogRead(PinoAnalogico);
int Porcento = map(ValAnalogIn, 200, 260, 0, 100); // Traforma o valor analógico em porcentagem
Serial.print("Leitura: "); // Imprime o símbolo no valor
Serial.println(Porcento); // Imprime o valor em Porcentagem no monitor Serial
delay(2000);
}
