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
using ::testing::InSequence;

class LightingControl_shutdown : public ::testing::Test
{
public:
    LightingControl_shutdown() {}
    void SetUp()
    {
    }
    void TearDown()
    {
    }

private:
    ILighting* m_pReal;
    NiceMock<ILightingMock> m_lightMock;
    Timer m_timer;
    NiceMock<ITimerMock> m_timerMock;
};

TEST_F( LightingControl_shutdown, BAT )
{
    {
        InSequence s;
        EXPECT_CALL( m_lightMock, initialize() )
            .Times( 1 );
        EXPECT_CALL( m_lightMock, off() )
            .Times( 1 );
        EXPECT_CALL( m_timerMock, every( Eq( 10 ), Eq( LightingControl::display ) ) )
            .WillOnce( Return( 1 ) );
        EXPECT_CALL( m_timerMock, stop( Eq( 1 ) ) )
            .Times( 1 );
        EXPECT_CALL( m_lightMock, off() )
            .Times( 1 );
    }

    //---------------------------------------------------
    LightingControl::initialize( &m_lightMock,
                                 &m_timerMock );
    LightingControl::shutdown();
    //---------------------------------------------------
}


TEST_F( LightingControl_shutdown, NoInitialize_ShutdownIsNoop_Positive )
{
    EXPECT_CALL( m_timerMock, stop( Eq( 1 ) ) )
        .Times( 0 );
    EXPECT_CALL( m_lightMock, off() )
        .Times( 0 );

    //---------------------------------------------------
    LightingControl::shutdown();
    //---------------------------------------------------
}

TEST_F( LightingControl_shutdown, MultipleShutdown_IsIgnored_Positive )
{
    {
        InSequence s;
        EXPECT_CALL( m_lightMock, initialize() )
            .Times( 1 );
        EXPECT_CALL( m_lightMock, off() )
            .Times( 1 );
        EXPECT_CALL( m_timerMock, every( Eq( 10 ), Eq( LightingControl::display ) ) )
            .WillOnce( Return( 1 ) );
        EXPECT_CALL( m_timerMock, stop( Eq( 1 ) ) )
            .Times( 1 );
        EXPECT_CALL( m_lightMock, off() )
            .Times( 1 );
    }

    //---------------------------------------------------
    LightingControl::initialize( &m_lightMock,
        &m_timerMock );
    LightingControl::shutdown();
    LightingControl::shutdown();
    //---------------------------------------------------
}