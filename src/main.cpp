#include "../include/InertialDriver.h"
#include <iostream>

int main(){
    InertialDriver d = InertialDriver();

    Reading r1;
    r1.pitch_a = 1.2;
    r1.pitch_v = 2.2;
    r1.roll_a = -1.2;
    r1.roll_v = 9.99;
    r1.yaw_a = -10;
    r1.yaw_v = 0;

    Reading r2 = r1;
    r2.pitch_v = 99.9;

    Reading r3 = r1;
    r3.roll_a = 99.9;

    Reading r4 = r1;
    r4.roll_v = 99.9;

    Measure m1;
    Measure m2;
    Measure m3;
    Measure m4;
    Measure m5;
    
    for( int i = 0; i < MEASURE_DIM; i ++ ){
        m1.sensors[ i ] = r1;
        m2.sensors[ i ] = r2;
        m3.sensors[ i ] = r3;
        m4.sensors[ i ] = r4;
        m5.sensors[ i ] = r1;
    }

    m5.sensors[ 1 ] = r2;
    m5.sensors[ 2 ] = r3;
    m5.sensors[ 3 ] = r4;

    d.push_back( m1 );
    Measure temp = d.pop_front();

    std::cout << "first cout" << std::endl;
    std::cout << temp.sensors[ 0 ].pitch_a << ", " << temp.sensors[ 0 ].pitch_v << ", " 
            << temp.sensors[ 0 ].yaw_a << ", " << temp.sensors[ 0 ].yaw_v << ", " 
            << temp.sensors[ 0 ].roll_a << ", " <<  temp.sensors[ 0 ].roll_v << std::endl;

    d.push_back( m1 );
    d.push_back( m2 );
    d.push_back( m3 );
    d.push_back( m4 );
    d.push_back( m5 );
    d.push_back( m1 );
    d.push_back( m2 );
    d.push_back( m3 );
    d.push_back( m4 );

    temp = d.pop_front();

    d.push_back( m5 );
    d.push_back( m5 );
    d.push_back( m5 );

    std::cout << "second cout" << std::endl;
    std::cout << d << std::endl;

    d.push_back( m3 );
    std::cout << "test cout" << std::endl;
    std::cout << d << std::endl;

    std::cout << "third cout" << std::endl;
    std::cout << temp.sensors[ 1 ].pitch_a << ", " << temp.sensors[ 1 ].pitch_v << ", " 
            << temp.sensors[ 1 ].yaw_a << ", " << temp.sensors[ 1 ].yaw_v << ", " 
            << temp.sensors[ 1 ].roll_a << ", " <<  temp.sensors[ 1 ].roll_v << std::endl;

    d.push_back( m1 );
    d.push_back( m2 );

    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();

    d.push_back( m1 );
    d.push_back( m2 );
    d.push_back( m3 );

    std::cout << "fourth cout" << std::endl;
    std::cout << d << std::endl;

    d.clear_buffer();
    d.pop_front();

    return 0;
}