#ifndef INERTIALDRIVER_H
#define INERTIALDRIVER_H

#include "myVector.h"
#include <iostream>

// dimensione buffer arbitraria
const int BUFFER_DIM=9; 

// una lettura è composta da 6 valori
struct Reading {
    double yaw_v;
    double yaw_a;
    double pitch_v;
    double pitch_a;
    double roll_v;
    double roll_a;
};

// una misura sono 17 letture 
// così è un doppio struct, Measure contiene Reading che contiene 6 double
struct Measure {
    // array stile c di 17 letture
    Reading sensors[17]; 
};

class InertialDriver {
private:
    // il buffer lo usiamo con myvector, dimensione fissata da BUFFER_DIM
    myVector<Measure> buffer;
    
    // Index del primo slot libero
    int firstFreeIndex;
    // Indice della misura meno recente
    int oldestMeasureIndex;
    //numero attuale di elementi per doppio controllo
    int elem_count;

public:
    InertialDriver();

    // aggiungi una misura; se il buffer è pieno, sovrascrive la misura più vecchia
    void push_back(const Measure& m);

    // fornisce e rimuove misura più vecchia
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