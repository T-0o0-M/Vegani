#include "../include/InertialDriver.h"
#include <iostream>
#include <stdexcept>

InertialDriver::InertialDriver() {
    // Construttore per inizializzazione
    firstFreeIndex = 0;
    oldestMeasureIndex = 0;
    elem_count = 0;
    // Allocazione memoria.
    // Poiché myVector::reserve usa 'new T[]', gli oggetti vengono costruiti immediatamente.
    buffer.reserve(BUFFER_DIM);   
}

// Aggiunge  una misura; se il buffer è pieno, sovrascrive la misura più vecchia
void InertialDriver::push_back(const Measure& m) {
    // Se ill buffer è pieno. Sovrascrive l'elemento più vecchio (oldestMeasureIndex).
    if (elem_count == BUFFER_DIM) {      
        // Dopo la scrittura, l'indice più vecchio deve avanzare per puntare al nuovo elemento più vecchio. (Implementazione con %)
        oldestMeasureIndex = (oldestMeasureIndex + 1) % BUFFER_DIM;
    } 
    //Inserimento
    buffer[firstFreeIndex] = m;

    // Aggiornamento dell'indice di firstFreeIndex (Implementazione con %)
    firstFreeIndex = (firstFreeIndex + 1) % BUFFER_DIM;

        // Aggiornamento del conteggio solo se buffer non e' gia' pieno
    if (elem_count < BUFFER_DIM) {
        elem_count++;
    }
}
// Fornisce e rimuove misura più vecchia
void InertialDriver::pop_front(Reading* output_array) {
    // Controllo buffer vuoto
    if (elem_count == 0) {
        throw std::out_of_range("Errore: Buffer vuoto");
    }
    // Copia dei dati, copia i 17 elementi dall'oggetto Measure interno nel array esterno
    for (int i = 0; i < 17; i++) {
        // buffer[oldest...].sensors è l'array sorgente
        // output_array è l'array di destinazione
        output_array[i] = buffer[oldestMeasureIndex].sensors[i];
    }
    //Avanzamento dell'indice
    oldestMeasureIndex = (oldestMeasureIndex + 1) % BUFFER_DIM;
    
    //Decremento conteggio
    elem_count--;
}

 // Set buffer vuoto
void InertialDriver::clear_buffer() {
     // Resetta tutti gli indici come se si fosse appena creato un oggetto InertialDriver
    firstFreeIndex = 0;
    oldestMeasureIndex = 0;
    elem_count = 0;   
}


// Dalla misura più recente, restituisce una delle 17 letture (composte da i 6 double).
const Reading& InertialDriver::get_reading(int sensor_index) const {
    
    // Controllo validità input
    if (sensor_index < 0 || sensor_index > ( READING_DIM - 1 ) ) {
        throw std::out_of_range("Errore: Indice lettura invalido");
    }

    // Controllo buffer vuoto
    if (elem_count == 0) {
        throw std::out_of_range("Errore: Buffer vuoto");
    }

    // Calcolo dell'indice dell'elemento più recente
    // L'elemento più recente è sempre quello appena prima del primo indice libero (firstFreeIndex).
    int newestIndex = (firstFreeIndex - 1 + BUFFER_DIM) % BUFFER_DIM;

    // Restituzione diretta dal buffer per riferimento
    return buffer[newestIndex].sensors[sensor_index];
}

std::ostream& operator<<(std::ostream& os, const InertialDriver& driver) {
    for (int i = 0; i < READING_DIM; i++) {
        const Reading& temp = driver.get_reading(i);

        os << "[" << temp.pitch_a << "," << temp.pitch_v << "," 
           << temp.roll_a << "," << temp.roll_v << "," 
           << temp.yaw_a << "," << temp.yaw_v << "]";

        // Virgola tra un valore e l'altro
        if (i < ( READING_DIM - 1 ) ) {
            os << ", ";
        }
    }
    return os;
}