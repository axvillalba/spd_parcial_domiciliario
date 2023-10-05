//Definimos las variables que seran las correspondientes a los led de 7 segmentos.
#define A 12
#define B 13
#define C 7
#define D 8
#define E 9
#define F 11
#define G 10

//Definimos las variables que corresponderan a los pulsadores
#define SUBE 4
#define BAJA 3
#define RESET 5

//Definimos el resto de las variables que controlaran la energia para el funcionamiento
//de los leds
#define UNIDAD A4
#define DECENA A5

#define APAGADOS 0
#define TIMEDISPLAYON 10

int countDigit = 0;
int sube = 1;
int subePrevia = 1;
int baja = 1;
int bajaPrevia = 1;
int reset = 1; 
int resetPrevia = 1;

void setup()
{
  pinMode(BAJA, INPUT_PULLUP); 
  pinMode(SUBE, INPUT_PULLUP); 
  pinMode(RESET, INPUT_PULLUP);
  
  pinMode(2, OUTPUT);
  
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);

  /* defino A4 como salida, porque aca quiero decidir si pongo 5V o si pongo 0v, 
  porque cuando ponga 5v se va a apagar y cuando ponga 0v se va a prender */
  pinMode(UNIDAD, OUTPUT); 

  /* defino A5 como salida, porque aca quiero decidir si pongo 5V o si pongo 0v, 
  porque cuando ponga 5v se va a apagar y cuando ponga 0v se va a prender */
  pinMode(DECENA, OUTPUT); 

  digitalWrite(UNIDAD, 0);
  digitalWrite(DECENA, 0);

  imprimeDigito(0);
  
}

void loop()
{

  int presionado = tecla_presionada(); 
  
  if( presionado == SUBE){ 
    countDigit++;
    if(countDigit > 99 )
    	countDigit = 0;
  
  } else if(presionado == BAJA) { 
    countDigit--;
    if(countDigit < 0 )
    	countDigit = 99;
  
  } else if (presionado == RESET) { 
        countDigit = 0;
  }
  
  imprimir_contador(countDigit);
}


void imprimeDigito(int digito){
  
  /*Se encarga de imprimir un digito en el led.
    Recibe un int (el digito)
    devuelve la señal de los led a prender. 
  */
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  
  switch(digito){
  	case 1:
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
    	break;	
    case 2:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    case 3:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    case 4:
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    case 5:
        digitalWrite(A, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    case 6:
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
    	break;	
    case 8:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    case 9:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
    	break;	
    default:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
    	break;	
  }
  
}

void prendeDigito(int digito){
    /*Prende las luces del led de 7 segmentos
        recibe un numero (digito)
        va a devolver cual segmento de la luz led devuelve segun 
        si es la decena o la unidad
    */
  if(digito == UNIDAD) {

  	digitalWrite(UNIDAD, LOW); 
    
    digitalWrite(DECENA, HIGH);
    
    delay(TIMEDISPLAYON);

  } else if(digito == DECENA){

  	digitalWrite(UNIDAD, HIGH);
    
    digitalWrite(DECENA, LOW); 
    
    delay(TIMEDISPLAYON);  

  } else {

    digitalWrite(UNIDAD, HIGH); 

    digitalWrite(DECENA, HIGH); 

  }

}

void imprimir_contador(int contar) {
    /*funcion que interactua para apagar y prender las luces segun corresponda
    recibe un contador (entero) 
    */  
    prendeDigito(APAGADOS); 
    imprimeDigito(contar/10); 
    prendeDigito(DECENA); 
    prendeDigito(APAGADOS); 
    imprimeDigito(contar - 10*((int)contar/10));
    prendeDigito(UNIDAD); 
}

int tecla_presionada() {
  
    /*Interactua con los pulsadores para cambiar la actividad 
    los leds
    */

    sube = digitalRead(SUBE); 
    baja = digitalRead(BAJA); 
    reset = digitalRead(RESET); 
  
    if(sube)
        subePrevia = 1;

    if(baja) 
        bajaPrevia = 1; 
  
    if(reset) 
        resetPrevia = 1;
  
    if(sube == 0 && sube != subePrevia) { 
      
        subePrevia = sube; 
        return SUBE; 
      
    }
  
    if(baja == 0 && baja != bajaPrevia) {     
        bajaPrevia = baja;
        return BAJA;
    }
  
    if(reset == 0 && reset != resetPrevia) { 
        resetPrevia = reset;
        return RESET;
    }
  
    return 0;
}