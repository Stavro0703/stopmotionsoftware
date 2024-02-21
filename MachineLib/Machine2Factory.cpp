/**
 * @file Machine2Factory.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Machine2Factory.h"
#include "Machine.h"
#include "Shape.h"
#include "CardReader.h"
#include "StruckInstrument.h"
#include "Cylinder.h"
#include "Tubing.h"
#include "Pipe.h"
#include "AirSource.h"

/**
 *Constructor for Machine2Factory
 * @param resourcesDir
 * @param audioEngine
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir, ma_engine *audioEngine) :
		mResourcesDir(resourcesDir), mAudioEngine(audioEngine)
{

}


/**
 * Creates machine #2
 * @return
 */
std::shared_ptr<Machine> Machine2Factory::Create()
{
	// Sizes
	const int BackgroundWidth = 550;

	// Locations of stuff
	const int BaseWidth = 700;
	const int BaseHeight = 10;

	// All of the centers (X)
	const int BackgroundCenter = 80;
	const int CardReaderCenter = -275;
	const int CymbalAndDrumCenter = 295;
	const int ClampingPostCenter = -182;

	const int NumPipes = 5;
	const int PipesCenter = 100;
	const int PipeSpacing = 40;
	const int PipeY = -100;

	// The machine itself
	// In this solution the machine number is passed
	// to the working machine constructor, so it knows
	// its number.
	auto machine = std::make_shared<Machine>(1);

	// The base, just a flat to sit things on
	auto base = std::make_shared<Shape>();
	base->Rectangle(-BaseWidth /2, BaseHeight, BaseWidth, BaseHeight);
	base->SetColor(wxColour(100, 100, 100));
	machine->AddComponent(base);

	//
	// The background image
	//
	auto background = std::make_shared<Shape>();
	background->SetImage(mResourcesDir + L"/images/mortier.png");
	background->Rectangle(-BackgroundWidth /2, 0, BackgroundWidth, 0);
	background->SetPosition(BackgroundCenter, 0);
	machine->AddComponent(background);

	//
	// The card reader
	//
	auto reader = std::make_shared<CardReader>(mResourcesDir);
	reader->SetCard(mResourcesDir + L"/images/cards/mary.png");
	reader->SetPosition(CardReaderCenter, 0);
	machine->AddComponent(reader);

	//
	// Pipes
	//
	int PipeLength[] = { 400, 350, 310, 260, 220 };
	std::wstring sounds[] = {L"/audio/organC4.wav",
		L"/audio/organD4.wav",
		L"/audio/organE4.wav",
		L"/audio/organG4.wav",
		L"/audio/organA4.wav"};

	// Vector to collect the pipes so we can
	// run hoses to them later.
	std::vector<std::shared_ptr<Pipe>> pipes;

	//
	// The pipes
	//
	int pipeX = -PipeSpacing * NumPipes / 2 + PipesCenter;
	for (int i = 0; i < NumPipes; i++) {
		//
		// The pipes
		//
		auto pipe = std::make_shared<Pipe>(mResourcesDir, mAudioEngine, sounds[i], PipeLength[i]);
		pipe->SetPosition(pipeX, PipeY);
		machine->AddComponent(pipe);
		pipes.push_back(pipe);

		pipeX += PipeSpacing;
	}

	//
	// The cymbal
	//
	auto cymbal = std::make_shared<StruckInstrument>(mResourcesDir, mAudioEngine, L"/audio/cymbal.wav");
	cymbal->SetImage(mResourcesDir + L"/images/cymbal-all.png");
	cymbal->Rectangle(-cymbal->GetImageWidth()/2, 0);
	cymbal->SetPosition(CymbalAndDrumCenter, 0);
	machine->AddComponent(cymbal);

	auto cymbalCylinder = std::make_shared<Cylinder>(mResourcesDir);
	cymbalCylinder->SetPosition(CymbalAndDrumCenter - 25, -350);
	cymbalCylinder->SetRotation(0.5);
	machine->AddComponent(cymbalCylinder);

	cymbalCylinder->SetMotionSink(cymbal);

	//
	// The drum
	//
	auto drum = std::make_shared<StruckInstrument>(mResourcesDir, mAudioEngine, L"/audio/kick.wav");
	drum->SetImage(mResourcesDir + L"/images/drum.png");
	drum->Rectangle(-drum->GetImageWidth() / 2, 0);
	drum->SetPosition(CymbalAndDrumCenter, 0);
	machine->AddComponent(drum);

	// Block to hold the cylinder
	auto block = std::make_shared<Shape>();
	block->SetImage(mResourcesDir + L"/images/angle-block.png");
	block->Rectangle(-block->GetImageWidth(), 0);   // 0,0 is lower right corner
	block->SetPosition(110, 0);
	machine->AddComponent(block);

	auto drumCylinder = std::make_shared<Cylinder>(mResourcesDir);
	drumCylinder->SetPosition(110, -30);
	drumCylinder->SetRotation(0.25);
	machine->AddComponent(drumCylinder);

	drumCylinder->SetMotionSink(drum);

	//
	// Clamping post for the tubing
	//
	auto post = std::make_shared<Shape>();
	post->SetImage(mResourcesDir + L"/images/clamping-post.png");
	post->Rectangle(-post->GetImageWidth()/2, 0);
	post->SetPosition(ClampingPostCenter, 0);
	machine->AddComponent(post);

	//
	// Temporary connection from card reader to pipes
	// Use this code to get the system working before you
	// add the Tubing class.
	//
	for (int i = 0; i < 5; i++)
	{
		reader->GetSource(i)->SetSink(pipes[4 - i]->GetSink());
	}

	reader->GetSource(9)->SetSink(cymbalCylinder->GetSink());
	reader->GetSource(8)->SetSink(drumCylinder->GetSink());

	return machine;
}
