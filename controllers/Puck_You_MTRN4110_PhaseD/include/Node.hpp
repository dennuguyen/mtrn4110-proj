#ifndef MAP_HPP
#define MAP_HPP

namespace mtrn4110 {
// ADD ANY OTHER CLASSES HERE

class Node {
    public:
    // ADD PUBLIC STUFF HERE
    bool up;
    bool down;
    bool left;
    bool right;
    int distance;
    int row;
    int col;
    private:
    // ADD PRIVATE STUFF HERE
};
}  // namespace mtrn4110

#endif  // MAP_HPP