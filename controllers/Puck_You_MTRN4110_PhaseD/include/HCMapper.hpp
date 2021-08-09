#ifndef HC_MAPPER
#define HC_MAPPER

#include "Mapper.hpp"
#include "Util.hpp"

namespace mtrn4110 {
// Implementation of mapper interface using a hard-coded algorithm.
template <typename GraphType = defaultTypes::GraphType>
class HCMapper : public Mapper<GraphType> {
   public:
    HCMapper();  // EDIT CONSTRUCTOR PARAMETERS AS REQUIRED

    auto tick() -> void override final;

    // ADD ANY PUBLIC METHODS BELOW HERE

   private:
    // ADD ANY PRIVATE MEMBERS BELOW HERE
};
}  // namespace mtrn4110

#endif  // HC_MAPPER