#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic mapper.
template <typename GraphType = defaultTypes::GraphType>
class Mapper {
   public:
    // Constructor to initialise required members.
    Mapper(GraphType graph) : graph_(graph) {}

    // Enforce derived classes to implement this method.
    virtual auto tick() -> void = 0;

    auto getGraph() const noexcept -> GraphType { return graph_; }

   private:
    GraphType graph_;
};
}  // namespace mtrn4110

#endif  // MAPPER_HPP