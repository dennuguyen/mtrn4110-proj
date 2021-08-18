#ifndef CV_PROCESSOR_HPP
#define CV_PROCESSOR_HPP

#include <Python.h>

#include "CVPuckYou.h"
#include "Util.hpp"

namespace mtrn4110 {

class CVProcessor /*final : public Localiser<>, public Deliberator<>*/ {
   public:
    CVProcessor() {
        init();
    }

    auto localise(std::string const& mazeImage, std::string const& robotImage) const noexcept
        -> void {
        auto const pose = getPose(mazeImage, robotImage);
        auto const heading = getHeading(mazeImage, mtrn4110::files::robotImage);
        std::cout << pose.first << " " << pose.second << " " << cardinalPoints[heading] << std::endl;
    }

    auto waypoint(std::string const& mazeImage, std::string const& ladybugImage) const noexcept
        -> void {
        auto const destination = getDestination(mazeImage, ladybugImage);
        std::cout << destination.first << " " << destination.second << std::endl;
    }

    auto map(std::string const& mazeImage) const noexcept -> void {
        auto const map = getMap(mazeImage);
        for (auto const& i : map)
            std::cout << i;
        std::cout << std::endl;
    }

   private:
   auto init() const -> void {
        // Add a built-in module, before Py_Initialize
        if (PyImport_AppendInittab("CVPuckYou", PyInit_CVPuckYou) == -1) {
            throw std::runtime_error("Could not extend built-in modules table.");
        }

        // Initialize the Python interpreter. If this step fails, it will be a fatal error.
        Py_Initialize();

        // Import CVPuckYou into the Python interpretter.
        auto module = PyImport_ImportModule("CVPuckYou");
        if (module == nullptr) {
            PyErr_Print();
            throw std::runtime_error("Could not import CVPuckYou.");
        }
    }

    auto cleanup() const -> void {
        // Clean up after using CPython.
        Py_Finalize();
    }
};
}  // namespace mtrn4110

#endif  // CV_PROCESS_HPP