/**
 * @file MachineSystem.cpp
 * @author Charles Owen
 *
 * You are not allowed to change this class in any way!
 *
 * This is a simple adapter class that routes all of the
 * operations to the class MachineStandin, which is a standin
 * for an actual machine in the system.
 */

#include "pch.h"
#include "MachineSystem.h"
#include "MachineStandin.h"

using namespace std;

MachineSystem::MachineSystem()
{
    mStandin = make_shared<MachineStandin>();
}

void MachineSystem::SetLocation(wxPoint location)
{
    mStandin->SetLocation(location);
}

wxPoint MachineSystem::GetLocation()
{
    return mStandin->GetLocation();
}


void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    mStandin->DrawMachine(graphics);
}


void MachineSystem::SetMachineFrame(int frame)
{
    mStandin->SetMachineFrame(frame);
}


void MachineSystem::SetFrameRate([[maybe_unused]] double rate)
{

}

void MachineSystem::SetMachineNumber(int seed)
{
    mStandin->SetMachine(seed);
}

int MachineSystem::GetMachineNumber()
{
    return mStandin->GetMachine();
}

double MachineSystem::GetMachineTime()
{
    return 0;
}

