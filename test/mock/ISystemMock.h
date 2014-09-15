#include "ISystem.h"

class ISystemMock : public ISystem
{
public:
    virtual ~ISystemMock() {}

    MOCK_METHOD1( sleep, void( uint32_t val ) );

};