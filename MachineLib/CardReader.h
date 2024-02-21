/**
 * @file CardReader.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H
#define CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H

#include "Component.h"
#include "Polygon.h"

class AirSource;

/**
 * Class that handles CardReader things
 */
class CardReader : public Component
{
private:

	///The back of the card reader
	cse335::Polygon mBack;

	///The front of the card reader
	cse335::Polygon mFront;

	///The punch card
	cse335::Polygon mCard;

	/// The air sources to drive things
	std::vector<std::shared_ptr<AirSource>> mSources;

	///The beats per minute
	double mBeatsPerMinute = 180.0;

	///The resource directory
	std::wstring mResourcesDir;

	/// The current column
	int mColumn = 0;

public:
	/// Default constructor (disabled)
	CardReader() = delete;

	/// Copy constructor (disabled)
	CardReader(const CardReader &) = delete;

	/// Assignment operator
	void operator=(const CardReader &) = delete;

	/**
     * Get an air source.
     * @param i Source index 0-9
     * @return Pointer to AirSource object.
    */
	std::shared_ptr<AirSource> GetSource(int i) { return mSources[i]; }

	CardReader(std::wstring resourcesDir);

	bool IsPunched(int column, int row);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

	void SetCard(std::wstring path);

	void SetTime(double time) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H
