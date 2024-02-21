/**
 * @file Polygon.h
 *
 * @author Charles Owen
 * @version 1.04
 *
 * Generic polygon class that is used to make shapes we
 * will use in our project.
 *
 * Version history:
 * 1.00 Initial wxWidgets version
 * 1.01 Instrumented to indicate usage errors
 * 1.02 Fixed issue with instrumentation and testing
 * 1.03 Put into cse335 namespace, opacity support
 * 1.04 Added Circle function
 */

#pragma once

#include <vector>
#include <memory>
#include <string>

namespace cse335 {

/**
 * Generic polygon class that is used to make shapes we 
 * will use in our project.
 */
    class Polygon {
    private:
        /// Default number of steps when drawing a circle
        static const int DefaultCircleSteps = 32;

        void DrawColorPolygon(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);
        void DrawImagePolygon(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

        /// Graphics path to use to draw
        wxGraphicsPath mPath;

        /// The points that make up the polygon
        std::vector<wxPoint> mPoints;

        /// A brush to draw the polygon with
        wxBrush mBrush;

        /// The display mode
        enum class Mode {
            Unset, Color, Image
        };

        /// The current mode
        Mode mMode = Mode::Unset;

        /// The basic texture image we load
        std::unique_ptr<wxImage> mImage;

        /// The graphics bitmap we actually draw
        wxGraphicsBitmap mGraphicsBitmap;

        /// The image clip region
        wxRegion mImageClipRegion;

        /// What is the top left point for the clip region?
        wxPoint mImageClipRegionTopLeft;

        /// What is the size of the clip region?
        wxPoint mImageClipRegionSize;

        /// Any amount to rotate the polygon in turns
        /// 0 to 1 is one complete rotation
        double mRotation = 0;

        /// Set true when DrawPolygon is called
        bool mHasDrawn = false;

        /// Opacity of the polygon - value range to 0 to 1
        double mOpacity = 1.0;

        /// Forces the bitmap to be reloaded
        bool mBitmapDirty = true;

        bool Assert(bool condition, wxString msg, const wxString& url = wxEmptyString);

        //<editor-fold desc="Code to support the deferred assertion message box" defaultstate="collapsed">
        /**
         * Class to display an error message dialog box after a delay
         */
        class DelayedMessage : public wxTimer {
        private:
            void Notify() override;

            /// Message to display
            wxString mMessage;

            /// URL to display
            wxString mURL;

            /// We only allow this to fire one time
            bool mFired = false;

        public:
            void Fire(const wxString& msg, const wxString& url = wxEmptyString);
        };

        /// Delayed message object
        std::shared_ptr<DelayedMessage> mDelayedMessage;
        //</editor-fold>

    public:
        Polygon();

        virtual ~Polygon();

        /**
         * @param x X value for point in pixels
         * @param y Y value for point in pixels
         */
        void AddPoint(int x, int y);

        /**
         * Add a point to the polygon. Convenience version that accepts doubles.
         * @param x X value for point in pixels
         * @param y Y value for point in pixels
         */
        void AddPoint(double x, double y) { AddPoint((int) x, (int) y); }

        void Rectangle(int x, int y, int width = 0, int height = 0);

        void CenteredSquare(int size = 0);

        void SetColor(wxColour color);

        void SetImage(std::wstring filename);

        void DrawPolygon(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

        /**
         * Set the rotation of the polygon
         * @param rotation Rotation in turns, where 0-1 is one revolution.
         */
        virtual void SetRotation(double rotation) { mRotation = rotation; }

        /**
         * Get the rotation of the polygon
         * @return rotation Rotation in turns, where 0-1 is one revolution.
         */
        virtual double GetRotation() const { return mRotation; }

        virtual void SetOpacity(double opacity);

        int GetImageWidth();

        int GetImageHeight();

        void BottomCenteredRectangle(int width = 0, int height = 0);

        void
        DrawCrosshair(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, int size = 10, wxColor color = *wxRED);

        void Circle(double radius, int steps=DefaultCircleSteps);
        double AverageLuminance(int x, int y, int wid, int hit);
    };

}
