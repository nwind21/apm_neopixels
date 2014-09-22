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

class LightingControl_initialize : public ::testing::Test
{
public:
    LightingControl_initialize() {}
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

TEST_F( LightingControl_initialize, BAT )
{
    EXPECT_CALL( m_lightMock, initialize() )
        .Times( 1 );
    EXPECT_CALL( m_lightMock, off( ) )
        .Times( 2 );
    EXPECT_CALL( m_timerMock, every( Eq( 10 ), Eq( LightingControl::display ) ) )
        .WillOnce( Return( 1 ) );

    //---------------------------------------------------
    LightingControl::initialize( &m_lightMock,
                                 &m_timerMock );
    ASSERT_EQ( LightingControl::getCurrentSequence(),
               LightingControl::LightSequence_Idle );
    //---------------------------------------------------
}

TEST_F( LightingControl_initialize, MultipleCalls_DoNotReinitialize_Positive )
{
    EXPECT_CALL( m_lightMock, initialize() )
        .Times( 1 );
    EXPECT_CALL( m_lightMock, off() )
        .Times( 2 );
    EXPECT_CALL( m_timerMock, every( Eq( 10 ), Eq( LightingControl::display ) ) )
        .WillOnce( Return( 1 ) );

    //---------------------------------------------------
    LightingControl::initialize( &m_lightMock,
                                 &m_timerMock );
    LightingControl::initialize( &m_lightMock,
                                 &m_timerMock );
    ASSERT_EQ( LightingControl::getCurrentSequence(),
               LightingControl::LightSequence_Idle );
    //---------------------------------------------------
}
