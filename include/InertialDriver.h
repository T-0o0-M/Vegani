#ifndef INERTIALDRIVER_H
#define INERTIALDRIVER_H

#include "myVector.h"
#include <iostream>

// Dimensione buffer arbitraria
const int BUFFER_DIM=9;
const int MEASURE_DIM = 17;

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
    Reading sensors[MEASURE_DIM]; 
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

    // Restituisce e rimuove dal buffer la misura meno recente
    Measure pop_front();

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