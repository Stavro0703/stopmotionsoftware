/**
 * @file SpartyFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"


using namespace std;

/**
 * This is a factory method that creates our Harold actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> SpartyFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Sparty");

    auto torso = make_shared<ImageDrawable>(L"Torso", imagesDir +L"/sparty_torso.png");
    torso->SetCenter(wxPoint(69, 144));
    torso->SetPosition(wxPoint(0, -200));
    actor->SetRoot(torso);

    auto lleg = make_shared<ImageDrawable>(L"Left Leg", imagesDir +L"/sparty_lleg.png");
    lleg->SetCenter(wxPoint(40, 27));
    lleg->SetPosition(wxPoint(102 - 69, 180 - 144));
    torso->AddChild(lleg);

    auto rleg = make_shared<ImageDrawable>(L"Right Leg", imagesDir +L"/sparty_rleg.png");
    rleg->SetCenter(wxPoint(34, 27));
    rleg->SetPosition(wxPoint(36 - 69, 180 - 144));
    torso->AddChild(rleg);

    auto larm = make_shared<ImageDrawable>(L"Left Arm", imagesDir +L"/sparty_larm.png");
    larm->SetCenter(wxPoint(25, 26));
    larm->SetPosition(wxPoint(120 - 69, 22 - 144));
    torso->AddChild(larm);

    auto rarm = make_shared<ImageDrawable>(L"Right Arm", imagesDir +L"/sparty_rarm.png");
    rarm->SetCenter(wxPoint(89, 26));
    rarm->SetPosition(wxPoint(20 - 69, 22 - 144));
    torso->AddChild(rarm);

	auto msuflag = make_shared<ImageDrawable>(L"MSU Flag", imagesDir + L"/msu_flag.png");
	msuflag->SetCenter(wxPoint(128, 260));
	msuflag->SetPosition(wxPoint(-70, 110));
	rarm->AddChild(msuflag);

    auto headb = make_shared<ImageDrawable>(L"Head Bottom", imagesDir +L"/sparty_lhead.png");
    headb->SetCenter(wxPoint(53, 30));
    headb->SetPosition(wxPoint(0, 37 - 144));
    torso->AddChild(headb);

    auto headt = make_shared<HeadTop>(L"Head Top", imagesDir +L"/sparty_head.png");
    headt->SetCenter(wxPoint(59, 143));
    headt->SetPosition(wxPoint(0, -28));
    headb->AddChild(headt);
    headt->SetEyesCenter(wxPoint(54, 110));
    headt->GetLeftEye()->LoadImage(imagesDir +L"/sparty_leye.png");
    headt->GetLeftEye()->SetCenter(wxPoint(14, 14));
    headt->GetRightEye()->LoadImage(imagesDir +L"/sparty_reye.png");
    headt->GetRightEye()->SetCenter(wxPoint(17, 16));
    headt->SetInterocularDistance(30);

    actor->AddDrawable(lleg);
    actor->AddDrawable(rleg);
    actor->AddDrawable(torso);
    actor->AddDrawable(larm);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);
	actor->AddDrawable(msuflag);
	actor->AddDrawable(rarm);

    return actor;
}