#ifndef CV_PROCESSOR_HPP
#define CV_PROCESSOR_HPP

#include <Python.h>

#include "CVPuckYou.h"
#include "Deliberator.hpp"
#include "Localiser.hpp"
#include "Mapper.hpp"
#include "Util.hpp"

namespace mtrn4110 {
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename DeliberateType = defaultTypes::PoseType,
         typename MapType = defaultTypes::MapType>
class CVProcessor final
: public Localiser<PoseType, HeadingType, MotionType>
, public Deliberator<DeliberateType>
, public Mapper<MapType> {
   public:
    CVProcessor()
    : Localiser<PoseType, HeadingType, MotionType>()
    , Deliberator<DeliberateType>()
    , Mapper<MapType>() {
        init();
    }

    auto localise(std::string const& mazeImage, std::string const& robotImage) noexcept -> void {
        this->currentPose_ = getPose(mazeImage, robotImage);
        this->currentHeading_ = getHeading(mazeImage, mtrn4110::files::robotImage);
    }

    auto waypoint(std::string const& mazeImage, std::string const& ladybugImage) noexcept -> void {
        this->delib_ = getDestination(mazeImage, ladybugImage);
    }

    auto map(std::string const& mazeImage) noexcept -> void {
        auto const map = getMap(mazeImage);
        this->map_ = util::tokenise(map, '\n');
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {
        os << "Current Location: (" << this->currentPose_.first << ", " << this->currentPose_.second
           << ")" << std::endl;
        os << "Current Heading: " << this->currentHeading_ << std::endl;
        os << "Destination: (" << this->delib_.first << ", " << this->delib_.second << std::endl;
        os << "Map:" << std::endl;
        std::for_each (this->map_.begin(), this->map_.end(), [&os](auto const& i) {
            os << i << std::endl;
        });
    }

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