#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic mapper.
template <typename InputType, typename GraphType = defaultType::GraphType>
class Mapper {
   public:
    // Enforce derived classes to implement this method.
    virtual auto tick() -> void = 0;

    auto getGraph() const noexcept -> GraphType { return graph_; }

   private:
    GraphType graph_;
};
}  // namespace mtrn4110

#endif  // MAPPER_HPP