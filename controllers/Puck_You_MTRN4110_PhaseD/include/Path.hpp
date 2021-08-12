#ifndef PATH_HPP
#define PATH_HPP

namespace mtrn4110 {
// ADD ANY OTHER CLASSES HERE

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NIL
};

class Step {
   public:
    // ADD PUBLIC STUFF HERE
    int row;
    int col;
    int distance;
    Direction inDirection;
    Direction outDirection;
   private:
    // ADD PRIVATE STUFF HERE
};

class Path {
   public:
    // ADD PUBLIC STUFF HERE
    std::vector<Step> route;
    int numSteps;
    int numTurns;
    std::string pathString;
   private:
    // ADD PRIVATE STUFF HERE
};

}  // namespace mtrn4110

#endif  // PATH_HPP