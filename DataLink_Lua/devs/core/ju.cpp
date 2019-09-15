#include "ju.hpp"

namespace devs::core {

  std::shared_ptr<Ju> devs::core::Ju::make_shared(Digraph &_digraph , const std::string &_name , int32_t _uSTN)
  {
    return std::make_shared<Ju>(_digraph, _name, _uSTN);
  }

  devs::core::Ju::Ju(Digraph &_digraph , const std::string &_name , int32_t _uSTN):AbstractAtomic(_digraph,_name),_uSTN(_uSTN){}

  void Ju::Input(const devs::IO_Type &x)
  {
  }

  void Ju::Internal()
  {
  }

  void Ju::Output(devs::IO_Bag &yb)
  {
  }

  devs::TimeType Ju::Ta()
  {
    return devs::TimeType();
  }
}