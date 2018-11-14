int state = 0; //valor que bluetooth 
int habilitar = 0;

int ocupadoled = 0;
int ocupadocooler = 0;

int pinbomba=12;
int tiempo=0;
int bombaEstado=0;

int luz=0;
int luzEstado=0;
int rangoluz=100;
int pinled=8;


int calor=0;
int calorEstado=0;
int pincooler=4;
int rangocalor=4;

//declarando entradas y salidas 
void setup() {  
pinMode(pinled,OUTPUT);
pinMode(pincooler,OUTPUT);
pinMode(pinbomba,OUTPUT);  
 Serial.begin(9600);
}
void loop() {
//_________________+-________________________________blutooth 
 
   if(Serial.available() > 0){ 
   state = Serial.read();}
    if (state == '0') {APAGAR();}
    if (state == '1') {ENCENDER();}
    if (habilitar == 1){
    if (state == '2') {LED_ON();}
    if (state == '3') {LED_OFF();}
    if (state == '4') {COOLER_ON();}
    if (state == '5') {COOLER_OFF();}
    Serial.println(calor);
    delay (100);
    }}

//_________________________________________________ declaracion para etiquetas 

void LED_ON(){    //etiqueta
  digitalWrite(pinled, HIGH);
  ocupadoled = 1;
  ENCENDER();}
  
void LED_OFF(){    //etiqueta
  //digitalWrite(pinled, LOW);
  ocupadoled = 0;
  ENCENDER();}
  
void COOLER_ON(){
  digitalWrite(pincooler, HIGH);
  ocupadocooler = 1;
  ENCENDER();}
  
  void COOLER_OFF(){    //etiqueta
  //digitalWrite(pincooler, LOW);
  ocupadocooler = 0;
  ENCENDER();}


//_________________________________________________programando bomba y filtro

void APAGAR(){
  habilitar = 0;
  digitalWrite(pinbomba, LOW);
  digitalWrite(pinled, LOW);
  digitalWrite(pincooler, LOW);
  tiempo = 0;
 }
void ENCENDER(){
  habilitar = 1;
  delay (875);
  tiempo=tiempo+1;
  
if (bombaEstado==0){ //pregunta si la bomba esta encendida (1) o apagada (0)
    digitalWrite(pinbomba, LOW); // si esta apagada mantiene apagada
    if (tiempo >= 32){
        bombaEstado=1;          // encende la bomba despues del tiempo de vaciado
        tiempo=0;}}
else{
    digitalWrite(pinbomba, HIGH); // si esta encendida mantiene encendida        /// OK 
    if (tiempo >= 15){
        bombaEstado=0; // apaga la bomba despues del tiempo de llenado
        tiempo=0;}}


 // int valorAnalogo = tiempo; //verificar en monitor 
 // Serial.println(tiempo);     //mostrar en monitor 
 //delay(1);      
    
//______________________________________________________________________________leer luz 
if (ocupadoled == 0) {
luz = analogRead(A1);
if  (luzEstado == 0){
    if (luz <= 800 + rangoluz) //850
        {digitalWrite(pinled, LOW);
        luzEstado=0;}
    else {
    digitalWrite(pinled, HIGH);
    luzEstado=1;

}}else{

     if (luz <= 800 - rangoluz) //750
        {digitalWrite(pinled, LOW);
        luzEstado=0;}
    else {
    digitalWrite(pinled, HIGH);
    luzEstado=1;}}}
    
//_____________________________________________________________________________Activacion de cooler 

if (ocupadocooler == 0) {
calor = (analogRead(A0)-30);
if  (calorEstado == 0){
    if (calor <= 30 + rangocalor)  //a  abajo 35ºc cooler apagador
        {digitalWrite(pincooler, LOW);
        calorEstado=0;}
    else {
    digitalWrite(pincooler, HIGH); //encender a 35ºc
    calorEstado=1;

}}else{

     if (calor <= 30 - rangocalor) // bajo 25ºc apagar cooler 
        {digitalWrite(pincooler, LOW);
        calorEstado=0;}
    else {
    digitalWrite(pincooler, HIGH);
    calorEstado=1;}}}
}
