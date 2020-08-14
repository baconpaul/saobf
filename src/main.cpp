#include "Filter.h"
#include <iostream>

int main( int argc, char **argv )
{
    Filter f;

    float sr = 48000;
    f.setSampleRate( 48000 );
    f.setResonance( 0.2 );
    f.setMultimode( .2 );
    
    auto freq0 = 1008.0;
    auto sps = sr / freq0;

    const float ln2 = 0.69314718056f;
    const float mult = ln2 / 12.0;
    float cof = 440.0 * exp( 90 * mult );
    
    for( int i=0; i< sr + sps*10; ++i )
    {
        auto phase = ( 1.f * i / sps );
        phase = phase - (int)phase;
        float pw = phase < 0.3 ? 1 : -1;
        float fpw = f.Apply4Pole( pw, cof );
        if( i > sr )
            std::cout << 1.f * (i-sr) / sr << "," << pw << "," << fpw << std::endl;
    }
}
