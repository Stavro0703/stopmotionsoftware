/**
 * @file PictureFactory.h
 * @author Charles Owen
 *
 * A factory class that builds our picture.
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;
struct ma_engine;

/**
 * A factory class that builds our picture.
 */
class PictureFactory {
private:


public:
    std::shared_ptr<Picture> Create(std::wstring resourcesDir, ma_engine* audioEngine);
};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
