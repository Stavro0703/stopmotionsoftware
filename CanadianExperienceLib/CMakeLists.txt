project(CanadianExperienceLib)

set(SOURCE_FILES
        pch.h
        Picture.h Picture.cpp
        MainFrame.cpp MainFrame.h
        ViewEdit.cpp ViewEdit.h ViewTimeline.cpp ViewTimeline.h PictureObserver.cpp PictureObserver.h
        Actor.cpp Actor.h Drawable.cpp Drawable.h PolyDrawable.cpp PolyDrawable.h PictureFactory.cpp
        PictureFactory.h HaroldFactory.cpp HaroldFactory.h ImageDrawable.cpp ImageDrawable.h
        HeadTop.cpp HeadTop.h SpartyFactory.cpp SpartyFactory.h RotatedBitmap.cpp RotatedBitmap.h
        Timeline.cpp Timeline.h TimelineDlg.cpp TimelineDlg.h AnimChannel.cpp AnimChannel.h
        AnimChannelAngle.cpp AnimChannelAngle.h AnimChannelPoint.cpp AnimChannelPoint.h
        MachineDrawable.cpp MachineDrawable.h MachineFactory.cpp MachineFactory.h MachineFrameDlg.cpp
        MachineFrameDlg.h)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

include_directories("../${MACHINE_LIBRARY}/include")

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${MACHINE_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)