#ifndef MAPPING_HPP
#define MAPPING_HPP

#include <map>
#include <set>

namespace mtrn4110 {

template <typename GraphType = std::map<std::pair<int, int>, std::set<int, std::pair<int, int>>>>
class Mapping {
   public:
    virtual ~Mapping() = 0;

    auto getGraph() const noexcept -> GraphType { return graph_; }

   private:
    GraphType graph_;
};
}  // namespace mtrn4110

#endif  // MAPPING_HPP