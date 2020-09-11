#include "Filter.h"
#include <iostream>

int main( int argc, char **argv )
{
#if SIMPLE_PULSE
    Filter f;

    float sr = 48000;
    f.setSampleRate( 48000 );
    f.setResonance( 0.2 );
    f.setMultimode( 0.3 );
    
    auto freq0 = 1008.0;
    auto sps = sr / freq0;

    const float ln2 = 0.69314718056f;
    const float mult = ln2 / 12.0;
    float cof = 440.0 * exp( 50 * mult );
    
    for( int i=0; i< sr + sps*10; ++i )
    {
        auto phase = ( 1.f * i / sps );
        phase = phase - (int)phase;
        float pw = phase < 0.3 ? 1 : -1;
        float fpw = f.Apply4Pole( pw, cof );
        if( i > sr )
            std::cout << 1.f * (i-sr) / sr << "," << pw << "," << fpw << std::endl;
    }
#endif

#define SPECTRUM 1
#if SPECTRUM
    Filter f;

    float sr = 48000;
    f.setSampleRate( 48000 );
    f.setResonance( 0.6 );
    // f.setMultimode( 0.0 );

    float cof = 440.0 * exp( 60 * mult );
    
    for( float freq0 = 10; freq0 < 25000; freq0 = freq0 * 1.05 )
    {
        auto sps = sr / freq0;

        std::cout << freq0;
        for( float mm=0; mm <=5; mm += 1.0 )
        {
            f.setMultimode( mm );
            // f.setResonance( mm );
            double rms = 0.0;
            for( int i=0; i< 2 * sr; ++i )
            {
                double phase = 1.0 * i / sps;
                phase = phase - (int)phase;
                auto wf = sin( 2.0 * M_PI * phase );
                float fpw = f.Apply4Pole( wf, cof );
                // float fpw = f.Apply( wf, cof );
                rms += fpw * fpw;
            }
            rms = sqrt( rms ) / ( 2 * sr );
            std::cout << ", " << rms;
        }
        std::cout << std::endl;
    }
#endif    
}
