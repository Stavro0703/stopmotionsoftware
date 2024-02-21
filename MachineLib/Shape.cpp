/**
 * @file Shape.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Shape.h"

/**
 *
 * @param graphics the graphics context to be drawn to
 * @param x X coordinate of our machine
 * @param y Y coordinate of our machine
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
	mPolygon.DrawPolygon(graphics, x + GetX(), y + GetY());
}

