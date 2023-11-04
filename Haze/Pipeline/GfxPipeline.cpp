/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** GfxPipeline
*/

#include "GfxPipeline.hpp"

namespace Haze {
    GfxPipeline::GfxPipeline(Engine *engine) : _engine(engine)
    {
        _systems.push_back(ScaleSystem);
        _systems.push_back(AnimateSystem);
        _systems.push_back(PullEvent);
        _systems.push_back(RenderSystem);
        _systems.push_back(DisplaySystem);
        _systems.push_back(ClearSystem);

        // fs::path libpath = "Haze/lib/";
        // for (const auto &entry : fs::directory_iterator(libpath)) {
        //     if (entry.path().extension() == ".so") {
        //         _display.push_back(new DynLib(entry.path()));
        //     }
        // }

        // createDisplay_t createDisplay;
        // for (int i = 0; i < _display.size(); i++) {
        //     createDisplay = (createDisplay_t)_display[i]->sym("createDisplay");
        //     if (createDisplay != nullptr) {
        //         display = (IDisplay*)createDisplay();
        //         std::cout << "Display " << i << " loaded" << i << std::endl;
        //     }
        // }
    }

    GfxPipeline::~GfxPipeline()
    {
    }
}
