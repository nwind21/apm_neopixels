#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include "LightingControl.h"
#include "ILightingMock.h"
#include "ISystemMock.h"

using ::testing::Eq;
using ::testing::_;
using ::testing::Return;

class LightingControl_init : public ::testing::Test
{
public:
    LightingControl_init() {}
    void SetUp()
    {
        m_classUT = new LightingControl( &m_lightMock,
                                         &m_sysMock );
    }
    void TearDown()
    {
        delete m_classUT;
    }

private:
    ILighting* m_pReal;
    LightingControl* m_classUT;
    ILightingMock m_lightMock;
    ISystemMock m_sysMock;
};

TEST_F( LightingControl_init, stub)
{
    int numColors = 1;

    EXPECT_CALL( m_lightMock, initialize() )
        .Times( 1 );
    EXPECT_CALL( m_lightMock, strobe( Eq( 3 ) ) )
        .Times( 1 );
    EXPECT_CALL( m_lightMock, off() )
        .Times( 2 );

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
    EXPECT_CALL( m_sysMock, sleep( Eq( 75 ) ) )
        .Times( 8 * numColors );

    //---------------------------------------------------
    m_classUT->init();
    //---------------------------------------------------
}