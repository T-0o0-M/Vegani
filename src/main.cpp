#include <iostream>
#include <vector>
#include "../include/InertialDriver.h"

// --- FUNZIONE DI SUPPORTO ---
// Crea una 'Measure' fittizia riempiendo tutti i sensori con un valore base
Measure createDummyMeasure(double val) {
    Measure m;
    for (int i = 0; i < READING_DIM; i++) {
        // Riempiamo i 6 campi della struct Reading con lo stesso valore 'val'
        m.sensors[i] = {val, val, val, val, val, val}; 
    }
    return m;
}

int main() {
    InertialDriver driver;
    std::cout << "=== test ===" << std::endl;
    // TEST 1: Controllo Errori su Buffer Vuoto
    std::cout << "\n TEST 1: Verifica eccezioni su buffer vuoto" << std::endl;
    try {
        // Proviamo a leggere da un buffer appena creato (vuoto)
        driver.get_reading(0);
    } catch (const std::out_of_range& e) {
        std::cout << "   -> Eccezione catturata correttamente: " << e.what() << std::endl;
    }

    try {
        Reading temp_array[READING_DIM];
        // Proviamo a fare pop da vuoto
        driver.pop_front(temp_array);
    } catch (const std::out_of_range& e) {
        std::cout << "   -> Eccezione catturata correttamente: " << e.what() << std::endl;
    }

    // TEST 2: Inserimento e Lettura Recente (push_back; get_reading)
    std::cout << "\n TEST 2: Inserimento misure..." << std::endl;
    
    Measure m1 = createDummyMeasure(1.1); // Misura "1.1"
    Measure m2 = createDummyMeasure(2.2); // Misura "2.2"
    
    driver.push_back(m1);
    std::cout << "   -> Inserita misura 1 (Valori 1.1)" << std::endl;
    
    driver.push_back(m2);
    std::cout << "   -> Inserita misura 2 (Valori 2.2)" << std::endl;

    // get_reading deve restituire l'ultima inserita (m2)
    const Reading& r = driver.get_reading(0); // Leggiamo il sensore 0
    if (r.pitch_a == 2.2) {
        std::cout << "   -> OK: get_reading ha restituito l'elemento piu' recente (2.2)." << std::endl;
    } else {
        std::cout << "   -> Valore inatteso: " << r.pitch_a << std::endl;
    }

    // TEST 3: Stampa Operator<<
    std::cout << "\n TEST 3: operatore di stampa (ultima misura)..." << std::endl;
    // dovrebe stampare i valori 2.2
    std::cout << driver << std::endl; 


    // TEST 4: Estrazione misura più vecchia (pop_front)
    std::cout << "\n TEST 4: Rimozione misura vecchia (FIFO)..." << std::endl;
    
    // Nel buffer c'è: [Misura 1.1, Misura 2.2]
    // La più vecchia è la 1.1 qundi pop_front deve restituire quella.
    
    Reading dati_estratti[READING_DIM]; // Array di destinazione
    driver.pop_front(dati_estratti);

    std::cout << "   -> Eseguito pop_front." << std::endl;
    
    // il primo sensore dell'array estratto deve essere 1.1
    if (dati_estratti[0].pitch_a == 1.1) {
        std::cout << "   -> Estratta correttamente la misura vecchia 1.1" << std::endl;
    } else {
        std::cout << "   -> Estratto valore errato: " << dati_estratti[0].pitch_a << std::endl;
    }

    // Ora nel buffer rimane solo la 2.2. Se faccio un'altra pop, esce la 2.2.
    driver.pop_front(dati_estratti);
    if (dati_estratti[0].pitch_a == 2.2) {
         std::cout << "   -> Estratta seconda misura (2.2). Buffer ora vuoto." << std::endl;
    }

    // TEST 5: Buffer circolare
    std::cout << "\n[TEST 5] Riempimento e Sovrascrittura (Circular Buffer)..." << std::endl;
    
    // Riempiamo il buffer oltre la capacità (BUFFER_DIM + 5 elementi)
    int num_writes = BUFFER_DIM + 5; 
    std::cout << "   -> Scrivendo " << num_writes << " elementi..." << std::endl;

    for (int i = 0; i < num_writes; i++) {
        // Inseriamo valori crescenti: 100, 101, 102...
        driver.push_back(createDummyMeasure((double)i));
    }

    // Abbiamo scritto indici da 0 a (BUFFER_DIM + 4).
    // I primi 5 elementi (0, 1, 2, 3, 4) dovrebbero essere stati sovrascritti.
    // L'elemento più vecchio disponibile ora dovrebbe essere l'indice 5.
    Reading check_circular[READING_DIM];
    driver.pop_front(check_circular);

    std::cout << "   -> pop_front dopo sovrascrittura. Valore atteso: 5.0" << std::endl;
    std::cout << "   -> Valore ottenuto: " << check_circular[0].pitch_a << std::endl;

    if (check_circular[0].pitch_a == 5.0) {
        std::cout << "   -> OK: La logica circolare funziona. I vecchi dati sono stati sovrascritti." << std::endl;
    } else {
        std::cout << "   -> ERRORE: La logica circolare ha fallito." << std::endl;
    }


    // TEST 6: clear_buffer
    std::cout << "\n TEST 6: Resettiamo il buffer" << std::endl;
    driver.clear_buffer();
    
    try {
        driver.get_reading(0);
        std::cout << "   -> Il buffer dovrebbe essere vuoto!" << std::endl;
    } catch (...) {
        std::cout << "   -> Buffer svuotato correttamente" << std::endl;
    }

    std::cout << "\n FINSIH" << std::endl;
    return 0;
}