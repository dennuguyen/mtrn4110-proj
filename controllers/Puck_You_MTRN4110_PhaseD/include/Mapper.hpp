#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic mapper.
template<typename GraphType = defaultTypes::GraphType>
class Mapper {
   public:
    // Constructor to initialise graph.
    Mapper()
    : graph_() {}

    virtual auto readMap(std::istream& inputStream) -> void = 0;

    virtual auto buildGraph() -> void = 0;

    auto getGraph() const noexcept -> GraphType {
        return graph_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, Mapper const& mapper) noexcept -> std::ostream& {
        mapper.print(os);
        return os;
    }

   protected:
    GraphType graph_;

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // MAPPER_HPP