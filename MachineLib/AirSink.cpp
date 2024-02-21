/**
 * @file AirSink.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "AirSink.h"
#include "AirReceiver.h"

/**
 * Receives air and send it to component
 * @param pressure the presure to send
 */
void AirSink::ReceiveAir(double pressure)
{
	mComponent->ReceivePressure(pressure);
}
