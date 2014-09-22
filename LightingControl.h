#include "ILighting.h"
#include "ISystem.h"

#ifndef _IRISLIGHTINGCONTROL_h
#define _IRISLIGHTINGCONTROL_h

#include <list>
#include "ITimer.h"

class LightingControl
{
public:
    enum LightSequence
    {

        // Non-Repeat sequences will return to IDLE
        LightSequence_Idle,

        LightSequence_SystemCheck,
        LightSequence_Orientation,
        LightSequence_ModeLoiter,
        LightSequence_ModeStabilize,
        LightSequence_ModeAltHold,
        LightSequence_ModeMission,

        // Stop Repeating Sequence.
        LightSequence_Cancel
    };

    enum SequenceState
    {
        SequenceStateBegin,
        SequenceStateInProgress,
        SequenceStateEnd,
    };

    static void initialize( ILighting* lighting,
                            ITimer* timer );
    static void shutdown( );
    static void display();
    static void queueLightSequence( LightSequence seq );
    static LightingControl::LightSequence getCurrentSequence();

private:
    LightingControl( );
    static void lightSystemCheck();
    static void lightModeStabilize();

private:
    static std::list<LightSequence> m_queue;
    static ILighting* m_pLights;
    static ITimer* m_timer;
    static LightingControl::LightSequence m_currentSequence;
    static LightingControl::SequenceState m_currentSequenceState;
    static int8_t eventHandle;
};

#endif

