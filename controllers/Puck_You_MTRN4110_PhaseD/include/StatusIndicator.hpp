#ifndef STATUS_INDICATOR_HPP
#    define STATUS_INDICATOR_HPP

namespace mtrn4110 {
class StatusIndicator {
   public:
    template<class object>
    auto print(std::set<std::ostream&> os, object const& obj) -> std::set<std::ostream&> {
        std::for_each (os.begin(), os.end(), [&obj](auto& s) { s << obj; });
        return os;
    }

   private:
};
}  // namespace mtrn4110

#endif  // STATUS_INDICATOR_HPP

/*

auto TaskControl::displayMessage() const noexcept -> void {
    auto ss = std::stringstream();
    auto const &msg = getMessage();
    for (auto const &cell : msg) {
        ss << cell.first << ": " << cell.second;
        if (&cell != &msg.back()) {
            ss << ", ";
        }
    }
    print(ss.str());
}

auto TaskControl::initcsv() const -> void {
    auto csv = std::ofstream(csvPath, std::ios::trunc);
    if (csv.good() == false) {
        throw std::runtime_error("Could not open file.");
    }

    auto const &msg = getMessage();

    // Overwrite file with headers.
    for (auto const &cell : msg) {
        csv << cell.first << ", ";
    }
    csv << std::endl;

    if (csv.bad() == true) {
        throw std::runtime_error("I/O error while reading.");
    }
}

auto TaskControl::writeMessage2csv() const -> void {
    auto csv = std::ofstream(csvPath, std::ios::app);
    if (csv.good() == false) {
        throw std::runtime_error("Could not open file.");
    }

    auto const &msg = getMessage();

    // Append message to CSV.
    for (auto const &cell : msg) {
        csv << cell.second << ", ";
    }
    csv << std::endl;

    if (csv.bad() == true) {
        throw std::runtime_error("I/O error while reading.");
    }
}

auto TaskControl::getMessage() const noexcept -> std::vector<std::pair<std::string, std::string>> {
    auto msg = std::vector<std::pair<std::string, std::string>>();
    auto ss = std::stringstream();
    ss << std::setw(3) << std::setfill('0') << step_;
    msg.push_back({"Step", ss.str()});
    msg.push_back({"Row", std::to_string(localisation.getRow())});
    msg.push_back({"Column", std::to_string(localisation.getColumn())});
    msg.push_back({"Heading", std::to_string(localisation.getHeading())});
    msg.push_back({"Left Wall", std::to_string(wallPerception.getLeftWall())});
    msg.push_back({"Front Wall", std::to_string(wallPerception.getFrontWall())});
    msg.push_back({"Right Wall", std::to_string(wallPerception.getRightWall())});
    return msg;
}
*/