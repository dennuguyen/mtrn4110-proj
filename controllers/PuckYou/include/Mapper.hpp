#ifndef MAPPER_HPP
#define MAPPER_HPP

namespace mtrn4110 {
template<typename MapType = defaultTypes::MapType>
class Mapper {
   public:
    // Default constructor.
    Mapper() = default;

    // Constructor taking an initial map.
    Mapper(MapType map)
    : map_(map) {}

    auto getMap() const noexcept -> PoseType {
        return map_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, Localiser const& localiser) noexcept -> std::ostream& {
        localiser.print(os);
        return os;
    }

   protected:
    MapType map_;

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // MAPPER_HPP