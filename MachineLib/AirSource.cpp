/**
 * @file AirSource.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "AirSource.h"

/**
 *Sets the sink of this AirSource
 * @param sink the sink to set
 */
void AirSource::SetSink(AirSink *sink)
{
	mSink = sink;
	if(sink != nullptr)
	{
		sink->SetSource(this);
	}

}
