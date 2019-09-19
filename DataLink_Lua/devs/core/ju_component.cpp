#include "ju_component.hpp"

devs::core::JuComponent::JuComponent(Digraph & _digraph , Ju & _ju , const std::string & _name)
  :AbstractAtomic(_digraph,_name),ju(_ju)
{
  BindOutInterior();
  BindOutSecureBroadcast();
  BindOutImmediateBroadcast();
}
