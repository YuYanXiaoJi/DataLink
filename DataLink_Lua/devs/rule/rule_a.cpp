#include "rule_a.hpp"

devs::core::ju_component::RuleA::RuleA(Digraph & _digraph , Ju & _ju)
  :JuComponent(_digraph,_ju,"RuleA")
{
  BindInLT();
  BindInSTS();
}

void devs::core::ju_component::RuleA::Input(const devs::IO_Type & x)
{

  if(x.port == sigi_sts) {
    is_recv_ts = true;
  }

  if(x.port == sigi_lt) {
    const auto& msg = x.value->get<msg::LocalTrack>();
    std::string track_name = handler::TrackNumberHandler::GetName(msg.track_number);
    local_track_name_set.insert(track_name);
  }
}

void devs::core::ju_component::RuleA::Internal()
{
  is_recv_ts = false;
  local_track_name_set.clear();
}

void devs::core::ju_component::RuleA::Output(devs::IO_Bag & yb)
{
  for(auto& track_name : local_track_name_set) {
    auto[is_exist_at , is_exist_rt , is_exist_r2] = ju.GetExist(track_name);
    if(( is_exist_r2 == false ) && ( is_exist_rt == false ) && ( is_exist_at == true ))
    {
      auto sptr_blob=  util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2 , track_name.c_str()));
      this->InsertInteriorBroadcast(sptr_blob,yb);
    }
  }
}

devs::TimeType devs::core::ju_component::RuleA::Ta()
{
  if(is_recv_ts == true)
    return 0;
  else
    return TIME_MAX;
}
