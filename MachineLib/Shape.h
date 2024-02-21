/**
 * @file Shape.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SHAPE_H
#define CANADIANEXPERIENCE_MACHINELIB_SHAPE_H

#include "Component.h"
#include "Polygon.h"

/**
 * Shape base class that our components will use
 */
class Shape : public Component
{
private:
	///Our component
	cse335::Polygon mPolygon;

public:

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

	/**
     * Set an image we will use as a texture for the polygon
     * @param filename Image filename
     */
	void SetImage(std::wstring filename) { mPolygon.SetImage(filename); }

	/**
	 * Create a rectangle
	 * @param x Left side X
	 * @param y Bottom left Y
	 * @param wid Width of the rectangle. If not supplied, use an image width
	 * @param hit Height of the rectangle. If not supplied, use an image height
	 */
	void Rectangle(int x, int y, int wid = 0, int hit = 0) { mPolygon.Rectangle(x, y, wid, hit); }

	/**
 	* Set the color of the polygon. If we set a color, images are not used.
	* @param color A Gdiplus Color object.
 	*/
	void SetColor(wxColour color) { mPolygon.SetColor(color); }

	/**
	 * Gets the image width of our polygon
	 * @return the width
	 */
	int GetImageWidth() { return mPolygon.GetImageWidth(); }

	/**
	 * Gets the Image Height for our polygon
	 * @return the height
	 */
	int GetImageHeight() { return mPolygon.GetImageHeight(); }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_SHAPE_H
