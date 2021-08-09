#ifndef STATUS_INDICATOR_HPP
#define STATUS_INDICATOR_HPP

namespace mtrn4110 {
class StatusIndicator {
   public:
    template <class object>
    auto print(std::set<std::ostream&> os, object const& obj) -> std::set<std::ostream&> {
        std::for_each(os.begin(), os.end(), [&obj](auto& s) { s << obj; });
        return os;
    }

   private:
};
}  // namespace mtrn4110

#endif  // STATUS_INDICATOR_HPP