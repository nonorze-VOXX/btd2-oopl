#pragma once
#include "BloonFactory.h"
#include "Boomerang.h"
#include "BoomerangMonkey.h"
#include "DartMonkey.h"
#include "NailMachine.h"
#include "Throwable.h"
#include "Cannon.h"
#include "IceTower.h"


namespace Btd
{
    enum UnitTestState
    {
        Bez,
        BoomerangTest,
        BoomerangMonkeyTest,
    };

    class TestEverything
    {
    private:
        UnitTestState _unitTestState = Bez;
        float BezCounter;
        float BezDelta;
        GameObject bezObject;
        Boomerang _boomerang;
        shared_ptr<BoomerangMonkey> bm;

    public:
        TestEverything(TestEverything&&) = default;
        TestEverything() = default;
        void UnitInit();
        void UnitTest();
        void UnitShow();
        void SetState(UnitTestState state) { _unitTestState = state; };
    };
}
