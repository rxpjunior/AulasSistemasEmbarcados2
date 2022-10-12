void tiraNum(String comando)
{
 int valor = 0;
 String numero = "";
 int inicio = 17;
 int i = inicio;
 int acumula = 0;
 while (!isWhitespace(comando[i]))
 {
 if (isAlpha(comando[i])) return;
 numero += comando[i];
 i++;
 }
 int tamanho = i - inicio - 1;
 for (int j = 0; j <= tamanho; j++)
 {
 valor = numero[tamanho - j] - '0';
 acumula = acumula + valor * pow(10, j);
 }
 Serial.print("valor analogico: ");
 Serial.println(acumula);
 acumula0 = acumula;
 analogWrite(D7, acumula0);
}
