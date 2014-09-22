// 
// 
// 

#include "LightingControl.h"

std::list<LightingControl::LightSequence> LightingControl::m_queue;
ILighting* LightingControl::m_pLights;
ITimer* LightingControl::m_timer;
LightingControl::LightSequence LightingControl::m_currentSequence;
LightingControl::SequenceState LightingControl::m_currentSequenceState;
int8_t LightingControl::eventHandle = -1;

LightingControl::LightingControl( )
{
}

LightingControl::LightSequence LightingControl::getCurrentSequence()
{
    return m_currentSequence;
}

void LightingControl::lightSystemCheck()
{
    const uint32_t checkColor[] =
    {
        COLOR_RGB( 255, 0, 0 )
    };
    static uint8_t maxPixelIndex;
    static uint8_t armCnt;

    static int8_t incrementer = 1;
    static uint8_t lastPixel = 0;
    static uint8_t currentPixel = 0;
    static uint8_t cnt = 0;
    static int8_t localEventHandle = -1;

    uint8_t iPixel = 0;
    uint8_t iArms = 0;

    switch ( m_currentSequenceState )
    {
    case SequenceStateBegin:
        incrementer = 1;
        lastPixel = 0;
        currentPixel = 0;
        cnt = 0;
        m_pLights->off();
        m_currentSequenceState = SequenceStateInProgress;
        maxPixelIndex = m_pLights->length( ILighting::ARM_1 ) - 1;
        armCnt = m_pLights->cnt();
        localEventHandle = m_timer->every( 100,
                                            LightingControl::lightSystemCheck );
        break;
    case SequenceStateInProgress:
        if ( cnt < (sizeof( checkColor ) / sizeof( uint32_t )) )
        {
            if ( currentPixel == 0 )
            {
                incrementer = 1;
                for ( iArms = 0; iArms < armCnt; iArms++ )
                {
                    m_pLights->setColor( static_cast<ILighting::ARM>(iArms),
                        checkColor[cnt] );
                }
            }

            for ( iArms = 0; iArms < armCnt; iArms++ )
            {
                m_pLights->off( static_cast<ILighting::ARM>(iArms),
                    lastPixel );
                m_pLights->on( static_cast<ILighting::ARM>(iArms),
                    currentPixel );
            }
            lastPixel = currentPixel;
            if ( currentPixel == maxPixelIndex )
            {
                incrementer = -1;
            }

            currentPixel += incrementer;

            // We've come back to the first pixel
            if ( currentPixel == 0 )
            {
                cnt++;
            }
        }
        else
        {
            m_currentSequenceState = SequenceStateEnd;
        }
        break;
    case SequenceStateEnd:
        m_pLights->off();
        m_timer->stop( localEventHandle );
        localEventHandle = -1;
        m_currentSequence = LightSequence_Idle;
        break;
    };

}

void LightingControl::lightModeStabilize()
{
    static int8_t localEventHandle = -1;

    switch ( m_currentSequenceState )
    {
    case SequenceStateBegin:
        m_currentSequenceState = SequenceStateInProgress;
        localEventHandle = m_timer->every( 100,
                                           LightingControl::lightModeStabilize );
        break;
    case SequenceStateInProgress:
        m_currentSequenceState = SequenceStateEnd;
        break;
    case SequenceStateEnd:
        m_pLights->off();
        m_timer->stop( localEventHandle );
        localEventHandle = -1;
        m_currentSequence = LightSequence_Idle;
        break;
    };
}

void LightingControl::initialize( ILighting* lighting,
                                  ITimer* timer )
{
    if ( eventHandle == -1 )
    {
        m_currentSequence = LightSequence_Idle;
        m_pLights = lighting;
        m_timer = timer;

        m_pLights->initialize();
        m_pLights->off();
        eventHandle = m_timer->every( 10,
                                      LightingControl::display );
    }
}

void LightingControl::shutdown()
{
    if ( eventHandle != -1 )
    {
        m_currentSequence = LightSequence_Idle;
        m_timer->stop( eventHandle );
        m_pLights->off();

        m_pLights = NULL;
        m_timer = NULL;
        eventHandle = -1;
        m_queue.clear();
    }
}

void LightingControl::display()
{
    if ( m_currentSequence == LightSequence_Idle )
    { 
        m_currentSequenceState = SequenceStateBegin;
        m_currentSequence = m_queue.front();
        m_queue.pop_front();

        switch ( m_currentSequence )
        {
        case LightSequence_SystemCheck:
            lightSystemCheck();
            break;
        }
    }
}

void LightingControl::queueLightSequence( LightSequence seq )
{
    m_queue.push_back( seq );
}
