/**
 * @file PictureObserver.h
 * @author Charles B. Owen
 *
 * Observer base class for a picture.
 */
#ifndef CANADIANEXPERIENCE_PICTUREOBSERVER_H
#define CANADIANEXPERIENCE_PICTUREOBSERVER_H

class Picture;

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class PictureObserver {
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

protected:
    /// Constructor (protected)
    PictureObserver() {}

public:
    /// Copy constructor (disabled)
    PictureObserver(const PictureObserver &) = delete;

    ~PictureObserver();

    /// Assignment operator
    void operator=(const PictureObserver &) = delete;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    virtual void SetPicture(std::shared_ptr<Picture> picture);

    /**
     * Get the picture we are observing
     * @return Pointer to picture we are observing
     */
    std::shared_ptr<Picture> GetPicture() {return mPicture;}
};


#endif //CANADIANEXPERIENCE_PICTUREOBSERVER_H
