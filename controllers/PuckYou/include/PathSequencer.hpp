#ifndef PATH_SEQUENCER_HPP
#define PATH_SEQUENCER_HPP

#include <stdexcept>

#include "Util.hpp"

namespace mtrn4110 {
// Class which takes in some path with valid motion types
template<typename MotionType = defaultTypes::MotionType, typename PathType = defaultTypes::PathType>
class PathSequencer {
   public:
    // Default constructor.
    PathSequencer() = default;

    // Constructor for path sequencer to initialise the path.
    PathSequencer(PathType path)
    : path_(path) {}

    // Renew the motion sequence.
    auto updatePath(PathType const& path) noexcept -> void {
        path_ = path;
    }

    // Gets the next motion of the motion sequence.
    auto nextMotion() -> MotionType {
        try {
            return path_.at(pathIndex_++);
        } catch (std::out_of_range const& e) {
            return '\0';
        }
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, PathSequencer const& pathSequencer) noexcept
        -> std::ostream& {
        pathSequencer.print(os);
        return os;
    }

   private:
    auto print(std::ostream& os) const noexcept -> void {
        std::for_each (path_.at(pathIndex_), path_.end(), [&os](auto const& i) { os << i; });
    }

    PathType path_;
    int pathIndex_ = 0;
};
}  // namespace mtrn4110

#endif  // PATH_SEQUENCER_HPP