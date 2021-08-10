#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic mapper.
template<typename InputType, typename GraphType = defaultType::GraphType>
class Mapper {
   public:
    // Automate any simple and periodic behaviours.
    virtual auto tick() -> void = 0;

    auto getGraph() const noexcept -> GraphType {
        return graph_;
    }

    // Operator overload for <<.
    friend operator<<(std::ostream& os, PathPlanner const& pathPlanner) noexcept->std::ostream& {
        pathPlanner.print(os);
        return os;
    }

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;

    GraphType graph_;
};
} // namespace mtrn4110

#endif // MAPPER_HPP