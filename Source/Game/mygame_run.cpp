#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>

#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "BtdClass/TowerFactory.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
    UnitTest();
    button.Update();
}

vector<string> generatePath (string initPath)
{
	vector<string> path;
	for (int i=1; i<=8; i++)
	{
		string tmpPath = initPath + std::to_string(i) + ".bmp";
		path.push_back(tmpPath);
	}
	return path;
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    UnitInit();
	map.InitRoad();
    map.initBackground();
    button.LoadBitmapByString({"resources/button/button_monkey.bmp"}, RGB(0, 0, 0));
    button.SetAttribute(Btd::dart);
    button.SetTopLeft(780, 300);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    if (button.IsCursorFocus())
    {
        button.SetClicked(true);
    }
    if (!Btd::TowerFactory::TowerVector.empty() && Btd::TowerFactory::TowerVector.back().IsMovable())
    {
        Btd::TowerFactory::TowerVector.back().SetIsMove(false);
    }
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    if (!Btd::TowerFactory::TowerVector.empty() && Btd::TowerFactory::TowerVector.back().IsMovable())
    {
        Btd::TowerFactory::TowerVector.back().SetCenter(Btd::GetCursorPosX(), Btd::GetCursorPosY());
    }
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    map.showBackground();
	map.ShowRoad();
    button.ShowBitmap();
    UnitShow();
    if (!Btd::TowerFactory::TowerVector.empty())
    {
        for (auto m : Btd::TowerFactory::TowerVector)
        {
            m.ShowBitmap();
        }
    }
}

void CGameStateRun::UnitInit()
{
    switch (UNIT_TEST_STATE)
    {
    case Throwable:
        THROWABLE.LoadEmptyBitmap(100, 100);
        THROWABLE.SetTopLeft(0, 0);
        THROWABLE.SetSpeed(2);
        THROWABLE.SetMoveDirection(1, 1);
    // break;
    case DartMonkey:
        DART_MONKEY.LoadEmptyBitmap(50, 50);
        DART_MONKEY.SetTopLeft(100, 100);
    // DARTMONKEY.SetThrowableName("dart");
    // break;
    case BalloonMove:
        BALLOON.LoadEmptyBitmap(30, 30);
        BALLOON.SetTopLeft(10, 10);
        BALLOON.SetActive(false);
        BALLOON.SetNowRouteTarget(0);
        BALLOON.Setspeed(3);
    case BalloonVectorMove:
        BALLOONS.push_back(BALLOON);
    default:
        break;
    }
}

void CGameStateRun::UnitTest()
{
    switch (UNIT_TEST_STATE)
    {
    case Throwable:
        THROWABLE.Move();
        if (THROWABLE.GetTop() > 10)
        {
            UNIT_TEST_STATE = BalloonMove;
        }
        break;
    case DartMonkey:
        //shoot test
        break;
    case BalloonMove:

        BALLOON.Move({{500, 500}});
        if (BALLOON.GetTop() > 30)
        {
            UNIT_TEST_STATE = BalloonVectorMove;
        }
        break;
    case BalloonVectorMove:


        BALLOONS[0].Move({{500, 500}});
        if (BALLOONS[0].GetLeft() > 100)
        {
            UNIT_TEST_STATE = BalloonFactory;
        }
        break;
    case BalloonFactory:
        if (BALLOON_FACTORY.BallonVector.size() < 10)
        {
            BALLOON_FACTORY.MakeBallon("a");
        }
        for (auto& ballon : BALLOON_FACTORY.BallonVector)
        {
            ballon.Move({{500, 500}});
        }

        break;
    default: ;
    }
}

void CGameStateRun::UnitShow()
{
    switch (UNIT_TEST_STATE)
    {
    case Throwable:
        THROWABLE.ShowBitmap();
        break;
    case DartMonkey:
        DART_MONKEY.ShowBitmap();
        break;
    case BalloonMove:
        BALLOON.ShowBitmap();
        break;
    case BalloonVectorMove:
        BALLOONS[0].ShowBitmap();
        break;
    case BalloonFactory:
        for (auto& ballon : BALLOON_FACTORY.BallonVector)
        {
            ballon.ShowBitmap();
        }

        break;
    default:
        break;
    }
}
