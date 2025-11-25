#include "../include/InertialDriver.h"
#include <iostream>
#include <stdexcept>

InertialDriver::InertialDriver() {
    // Construttore per inizializzazione
    firstFreeIndex = 0;
    oldestMeasureIndex = 0;
    elem_count = 0;
    buffer.reserve(BUFFER_DIM);
/*utilizzo degli indici:
first e oldest vengono utilizzati per il loro significato letterare
per individuare se buffer è pieno o vuoto è necessario utilizzare elem_count*/    
}


//FUNZIONE USATA PER SEMPLIFICARE PUSH_BACK RIMOSSA
//incrementa gli indici dinamicamente attorno alla max size di 9
/*
 void InertialDriver::indexes_Increment(){
if(firstFreeIndex < (BUFFER_DIM-1)){firstFreeIndex++;}
    if(oldestMeasureIndex < (BUFFER_DIM-1)){oldestMeasureIndex++;}

    if(firstFreeIndex == (BUFFER_DIM-1)){firstFreeIndex == 0;}
    if(oldestMeasureIndex == (BUFFER_DIM-1)){oldestMeasureIndex == 0;
    }
 }*/

// aggiungi una misura; se il buffer è pieno, sovrascrive la misura più vecchia
void InertialDriver::push_back(const Measure& m) {
//CODICE DEPRECATO
//LA SIZE DEL BUFFER VIENE RISERVATA NEL COSTRUTTORE
//CODICE COMMENTATO E' INUTILE MA LO LASCIO PK NON SI SA MAI          
         //dato che myvector è una classe di gestione dinamica
         //lasciamo il buffer crescere fino alla sua dimensione massima consentita
         //e solo dopo che sono stati salvati i primi 9 valori utilizziamo gli index circolari

         //caso in cui il buffer non abbai ancora ricevuto i primi 9 valori
    
               //if (buffer.size() < BUFFER_DIM){
               //buffer.push_back(m);
               //elem_count++;
         //semplice implementazione utilizzando la classe myVector
         //eleem_count è provvisiorio nel caso sia inutile lo tolgo
 // }
         //caso in cui siamo arrivati ai primi 9
         //iniziamo ad utilizziare gli index
  //IF COMMENATTO PK BUFFER SIZE COSTANTE
         //if (buffer.size() == BUFFER_DIM)
         //siamo nel caso in cui NON possiamo più permettere al buffer di crescere in size
         //allora utiliziamo gli index
    

   //implementazione con buffer.reserve e elem_count
   //caso buffer non vuoto
    if(elem_count > 0){
    //CONVENZIONE PRIMA SI USA L'INDICE POI LO SI MODIDICA
    //buffer[firstFreeIndex] = m;
    if (elem_count < BUFFER_DIM){elem_count++;}
    //-----CASO INDICI DIVERSI-----
    if(firstFreeIndex != oldestMeasureIndex){
        buffer[firstFreeIndex] = m;
        if(firstFreeIndex < (BUFFER_DIM-1)){firstFreeIndex++;}
        if(firstFreeIndex == (BUFFER_DIM-1)){firstFreeIndex == 0;}
    }
    //---CASO INDICI UGUALI (SOVRASCRITTURA)
    if(firstFreeIndex == oldestMeasureIndex){
        buffer[oldestMeasureIndex] = m;
        if(firstFreeIndex < (BUFFER_DIM-1)){firstFreeIndex++;oldestMeasureIndex++;}
        if(firstFreeIndex == (BUFFER_DIM-1)){firstFreeIndex = 0;oldestMeasureIndex = 0;}   
    }
    /*if(firstFreeIndex < (BUFFER_DIM-1)){firstFreeIndex++;}
    if(oldestMeasureIndex < (BUFFER_DIM-1)){oldestMeasureIndex++;}

    if(firstFreeIndex == (BUFFER_DIM-1)){firstFreeIndex == 0;}
    if(oldestMeasureIndex == (BUFFER_DIM-1)){oldestMeasureIndex == 0;}
    */
   }
   //caso buffer vuoto
    if(elem_count == 0){
      buffer[0]= m;
      firstFreeIndex++;
      elem_count++;   
    }
}

// fornisce e rimuove misura più vecchia
Measure InertialDriver::pop_front() {
    if(elem_count == 0){
        throw std::out_of_range("Errore: Buffer vuoto");
    }
   Measure rtrn = buffer[oldestMeasureIndex];
  if(oldestMeasureIndex < (BUFFER_DIM-1)){oldestMeasureIndex++;}
  if(oldestMeasureIndex == (BUFFER_DIM-1)){oldestMeasureIndex == 0;}
   elem_count--;
   return rtrn;
}

 // setta il buffer vuoto
void InertialDriver::clear_buffer() {
     // resetta tutti gli indici come se si fosse appena creato un oggetto InertialDriver
    firstFreeIndex = 0;
    oldestMeasureIndex = 0;
    elem_count = 0;   
}


 // dalla misura più recente, restituisce una delle 17 letture (composte da i 6 double)
 //aggiunto & per restituire per valore, const per proteggere il buffer
const Reading& InertialDriver::get_reading(int sensor_index) const {
    // crea una variabile Measure
    if(elem_count == 0){
        throw std::out_of_range("Errore: Buffer vuoto");
    }
    Measure newest;
    // attraverso una serie di if trovo quale è l'ultima misura registrata nell'array
    // se gli elementi nell'array sono meno della massima dimensione, l'ultimo elemento insertio è buffer[firstFreeIndex-1]
    if (elem_count != BUFFER_DIM){
        newest = buffer[firstFreeIndex-1];
    }
    // se l'array contiene il massimo di elementi, e il primo elemento non si trova a buffer[0], l'utlimo elemento inserito è buffer[oldestMeasureIndex-1]
    else if (oldestMeasureIndex != 0) {
        newest = buffer[oldestMeasureIndex-1];
    }
    // se l'array contiene il massimo di elementi, ma l'elemento più vecchio è a buffer[0], l'utlimo elemento inserito è buffer[BUFFER_DIM]
    else {
        newest = buffer[BUFFER_DIM-1];
    }
    // creo un oggetto reading e lo iniziallizzo all'elemento sensor_index dell'oggetto Measure newest
    Reading rtrn = newest.sensors[sensor_index];

    //ritorno la lettura rtrn
    return rtrn;
}

//overloead operatore <<
std::ostream& operator<<(std::ostream& os, const InertialDriver& driver) {
    for ( int i = 0; i < 17; i++ ){
        Reading temp = driver.get_reading( i );

        os << "[" << temp.pitch_a << "," << temp.pitch_v << "," 
            << temp.roll_a << "," << temp.roll_v << "," 
            << temp.yaw_a << "," << temp.yaw_v << "]";

        if ( i < 16 ){
            os << ",";
        }
    }

    return os;
}