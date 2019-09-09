#pragma once
#include<string>
namespace devs {
  class Port {
  public:
    explicit Port(const std::string name = "")
      :name(name) {
      hash = std::hash<std::string>{}(name);
    }

    inline constexpr size_t operator () () const {
      return hash;
    }

    inline constexpr const std::string& Name() const {
      return name;
    }

  public: //compare

    inline  bool operator < (const Port& r) const { return Name() <  r.Name(); }
    inline  bool operator > (const Port& r) const { return Name() >  r.Name(); }
    inline  bool operator ==(const Port& r) const { return Name() == r.Name(); }
    inline  bool operator <=(const Port& r) const { return Name() <= r.Name(); }
    inline  bool operator >=(const Port& r) const { return Name() >= r.Name(); }
    inline  bool operator !=(const Port& r) const { return Name() != r.Name(); }
  private:
    std::string name;
    std::size_t hash;
  };
}