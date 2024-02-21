/**
 * @file MachineTest.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "gtest/gtest.h"

#include <miniaudio.h>
#include <MachineSystemFactory.h>
#include <MachineSystem.h>

// Test fixture that creates an audio engine to use
class MachineTest : public ::testing::Test {
protected:
    // The audio engine to use
    ma_engine mAudioEngine;

    void SetUp() override
    {
        auto result = ma_engine_init(NULL, &mAudioEngine);
        ASSERT_EQ(result, MA_SUCCESS);
    }

    void TearDown() override
    {
        ma_engine_uninit(&mAudioEngine);
    }

};

TEST_F(MachineTest, Constructor)
{
    MachineSystemFactory factory(L".", &mAudioEngine);
    auto machine = factory.CreateMachineSystem();

    ASSERT_NE(nullptr, machine);
}

TEST_F(MachineTest, Location)
{
    MachineSystemFactory factory(L".", &mAudioEngine);
    auto machine = factory.CreateMachineSystem();

    machine->SetLocation(wxPoint(123, 456));
    auto position = machine->GetLocation();
    ASSERT_EQ(123, position.x);
    ASSERT_EQ(456, position.y);
}

TEST_F(MachineTest, MachineTime)
{
    MachineSystemFactory factory(L".", &mAudioEngine);
    auto machine = factory.CreateMachineSystem();

    machine->SetFrameRate(30);
    machine->SetMachineFrame(123);

    ASSERT_NEAR(123.0 / 30.0, machine->GetMachineTime(), 0.001);

    // Different frame rate
    machine->SetFrameRate(15);
    machine->SetMachineFrame(201);
    ASSERT_NEAR(201.0 / 15.0, machine->GetMachineTime(), 0.001);
}


TEST_F(MachineTest, MachineNumber)
{
    MachineSystemFactory factory(L".", &mAudioEngine);
    auto machine = factory.CreateMachineSystem();

    // Try machine number 1
    machine->SetMachineNumber(1);
    ASSERT_EQ(1, machine->GetMachineNumber());

    // Try machine number 2
    machine->SetMachineNumber(2);
    ASSERT_EQ(2, machine->GetMachineNumber());

    // Ensure we can go back to machine number 1
    machine->SetMachineNumber(1);
    ASSERT_EQ(1, machine->GetMachineNumber());
}