#include "../include/InertialDriver.h"
#include <iostream>
#include <stdexcept>

InertialDriver::InertialDriver() {
    // Construttore per inizializzazione
    firstFreeIndex = 0;
    oldestMeasureIndex = 0;
    elem_count = 0;
}

//incrementa gli indici dinamicamente attorno alla max size di 9
 void InertialDriver::index_Increment(){

    if(firstFreeIndex < 8){firstFreeIndex++;}
    if(oldestMeasureIndex < 8){oldestMeasureIndex++;}

    if(firstFreeIndex == 8){firstFreeIndex == 0;}
    if(oldestMeasureIndex == 8){oldestMeasureIndex == 0;}
 }

// aggiungi una misura; se il buffer è pieno, sovrascrive la misura più vecchia
void InertialDriver::push_back(const Measure& m) {
    //dato che myvector è una classe di gestione dinamica
    //lasciamo il buffer crescere fino alla sua dimensione massima consentita
    //e solo dopo che sono stati salvati i primi 9 valori utilizziamo gli index circolari

    //caso in cui il buffer non abbai ancora ricevuto i primi 9 valori
    if (buffer.size() < BUFFER_DIM){
    buffer.push_back(m);

    elem_count++;
    //semplice implementazione utilizzando la classe myVector
    //eleem_count è provvisiorio nel caso sia inutile lo tolgo
  }
  //caso in cui siamo arrivati ai primi 9
  //iniziamo ad utilizziare gli index
   if (buffer.size() == BUFFER_DIM){
    //siamo nel caso in cui NON possiamo più permettere al buffer di crescere in size
    //allora utiliziamo gli index
    buffer[firstFreeIndex] = m;
    index_Increment();
   }
}

// fornisce e rimuove misura più vecchia
Measure InertialDriver::pop_front() {
   Measure rtrn = buffer[oldestMeasureIndex];
   if(oldestMeasureIndex == 0){oldestMeasureIndex = 8;}
   if(oldestMeasureIndex > 0){oldestMeasureIndex--;}
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
Reading InertialDriver::get_reading(int sensor_index) const {
    Measure newest;
    if (elem_count != BUFFER_DIM){
        newest = buffer[firstFreeIndex-1];
    }
    else if (oldestMeasureIndex != 0) {
        newest = buffer[oldestMeasureIndex-1];
    }
    else {
        newest = buffer[BUFFER_DIM];
    }
    Reading rtrn = newest[sensor_index];
    
    return rtrn;
}

//overloead operatore <<
std::ostream& operator<<(std::ostream& os, const InertialDriver& driver) {
  
}
