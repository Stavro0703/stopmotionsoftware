#include "gtest/gtest.h"
#include <wx/filefn.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}