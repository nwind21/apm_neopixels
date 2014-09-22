#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include "LightingControl.h"
#include "ILightingMock.h"
#include "ISystemMock.h"
#include "Timer.h"
#include "ITimerMock.h"

using ::testing::Eq;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class LightingControl_queueLightSequence : public ::testing::Test
{
public:
    LightingControl_queueLightSequence() {}
    void SetUp()
    {
        m_timerMock.setReal( &m_timer );
        ON_CALL( m_lightMock, initialize() )
            .WillByDefault( Return() );
        ON_CALL( m_timerMock, stop( _ ) )
            .WillByDefault( Return() );
        ON_CALL( m_lightMock, off() )
            .WillByDefault( Return() );
    }
    void TearDown()
    {
        LightingControl::shutdown();
    }

private:
    ILighting* m_pReal;
    NiceMock<ILightingMock> m_lightMock;
    Timer m_timer;
    NiceMock<ITimerMock> m_timerMock;
};

TEST_F( LightingControl_queueLightSequence, SystemLightCheck_Positive )
{
    int numColors = 1;

    EXPECT_CALL( m_timerMock, every( Eq( 10 ), _ ) );
    EXPECT_CALL( m_timerMock, every( Eq( 100 ), _ ) );

    EXPECT_CALL( m_lightMock, length( _ ) )
        .WillOnce( Return( 5 ) );
    EXPECT_CALL( m_lightMock, cnt() )
        .WillOnce( Return( 4 ) );

    EXPECT_CALL( m_lightMock, setColor( _, _ ) )
        .Times( 4 * numColors );
    EXPECT_CALL( m_lightMock, off( _, _ ) )
        .Times( 32 * numColors );
    EXPECT_CALL( m_lightMock, on( _, _ ) )
        .Times( 32 * numColors );


    m_timerMock.setReal( &m_timer );

    //---------------------------------------------------
    LightingControl::initialize( &m_lightMock,
                                 &m_timerMock );
    LightingControl::queueLightSequence( LightingControl::LightSequence_SystemCheck );

    // Force the queue into the system
    LightingControl::display();
    while ( LightingControl::getCurrentSequence() != LightingControl::LightSequence_Idle )
    {
        m_timer.update();
    }
    //---------------------------------------------------
}