#ifndef INERTIALDRIVER_H
#define INERTIALDRIVER_H

#include "myVector.h"
#include <iostream>

// Dimensione buffer arbitraria
const int BUFFER_DIM=9; 
// Dimensione array da consegna
const int READING_DIM=17;

// Reading e' una singola lettura composta da 6 valori come double 
struct Reading {
    double yaw_v;
    double yaw_a;
    double pitch_v;
    double pitch_a;
    double roll_v;
    double roll_a;
};

// Measure contiene un array stile C composto da 17 letture
struct Measure {
    Reading sensors[READING_DIM]; 
};

class InertialDriver {
private:
    // Buffer implementato attraverso classe myVector
    myVector<Measure> buffer;
    
    // Indice del primo slot libero nel buffer
    int firstFreeIndex;
    // Indice della misura meno recente
    int oldestMeasureIndex;
    // Numero attuale di elementi nel Buffer
    int elem_count;

public:
    InertialDriver();

    // Aggiunge una misura. Se il buffer è pieno, sovrascrive la misura più vecchia
    void push_back(const Measure& m);

    // Richiede un puntatore ad un array creato dall'utente,
    // da cui copia dati della lettua meno recente e la rimuove dal buffer.
    // L'utente finale ha il compito di allocare e gestire la memoria attraverso la costante READING_DIM
    void pop_front(Reading* output_array);

    // setta il buffer vuoto
    void clear_buffer();

    // Dalla misura più recente, restituisce una delle 17 letture (composte da i 6 double).
    // Se sensor_index è fuori dall'intervallo [0,16], il comportamento dipende dall'implementazione:
    // può generare un'eccezione, restituire una lettura di default, o causare un errore di runtime.
    const Reading& get_reading(int sensor_index) const;

    //funzione utilizzata per rapidamente incrementare gli indici
    //void indexes_Increment();

    // Overload operator<< print misura più recente (non testato)
    friend std::ostream& operator<<(std::ostream& os, const InertialDriver& driver);
};

#endif