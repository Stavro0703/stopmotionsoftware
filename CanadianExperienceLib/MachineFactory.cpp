/**
 * @file MachineFactory.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "MachineFactory.h"
#include "MachineDrawable.h"

using namespace std;

/**
 * Responsible for creating our machine drawable
 * @param resourcesDir the resources directory
 * @param audioEngine the audio engine
 * @param machineNum the number of the machine we want to create
 * @return A MachineDrawable actor
 */
std::shared_ptr<Actor> MachineFactory::Create(std::wstring resourcesDir, ma_engine *audioEngine, int machineNum)
{
	shared_ptr<Actor> actor = make_shared<Actor>(L"Machine");

	auto machine = make_shared<MachineDrawable>(resourcesDir, audioEngine, L"machine", machineNum);
	SetMachineDrawable(machine);
	actor->SetRoot(machine);

	actor->AddDrawable(machine);

	return actor;
}
