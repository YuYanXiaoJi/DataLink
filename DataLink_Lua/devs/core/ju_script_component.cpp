#include "ju.hpp"
#include "ju_script_component.hpp"
#include "../handler/lua_inject_handler.hpp"
using namespace devs::core;
using namespace devs;
devs::core::JuScriptComponent::JuScriptComponent(Digraph &digraph , Ju &ju , const std::string lua_file , const std::string &name)
  :JuComponent(digraph , ju , name)
{
  this->plua = luaL_newstate();
  luaL_openlibs(plua);
  InjectTheSoul();

  luabridge::setGlobal(plua , &( *this ) , "this");

  luaL_dofile(plua , lua_file.c_str()); //load lua file


    //get  func;
  auto m_luaRefInit = luabridge::getGlobal(plua , "Init");

  if(m_luaRefInit.isFunction())
    m_luaRefInit();
  else
    assert(false);

}
void devs::core::JuScriptComponent::Input(const devs::IO_Type &x)
{
  auto m_luaRefInput = luabridge::getGlobal(plua , "Input");
  if(m_luaRefInput.isFunction()) {
    if(x.port == sigi_broadcast_buffer) {
      m_luaRefInput(*x.value);
    }

    if(x.port == sigi_cmd) {
      m_luaRefInput(x.value->get<msg::LocalCmd>());
    }

    if(x.port == sigi_j2) {
      m_luaRefInput(x.value->get<msg::JointMsg2I>());
    }

    if(x.port == sigi_j3) {
      m_luaRefInput(x.value->get<msg::JointMsg3I>());
    }

    if(x.port == sigi_lt) {
      m_luaRefInput(x.value->get<msg::LocalTrack>());
    }

    if(x.port == sigi_sts) {
      m_luaRefInput(x.value->get<msg::SubTimeSlice>());
    }

    if(x.port == sigi_ts) {
      m_luaRefInput(x.value->get<msg::TimeSlice>());
    }

  }
  else
  {
    assert(false);
  }

    
}

void devs::core::JuScriptComponent::Internal()
{
  auto m_luaRefInternal = luabridge::getGlobal(plua , "Internal");
  if(m_luaRefInternal.isFunction())
    m_luaRefInternal();
  else
    assert(false);
}

void devs::core::JuScriptComponent::Output(devs::IO_Bag &yb)
{
  pyb = &yb;

  auto m_luaRefOutput = luabridge::getGlobal(plua , "Output");
  if(m_luaRefOutput.isFunction())
    m_luaRefOutput();
  else
    assert(false);

  pyb = nullptr;
}

devs::TimeType devs::core::JuScriptComponent::Ta()
{
  auto m_luaRefTa = luabridge::getGlobal(plua , "Ta");
  if(m_luaRefTa.isFunction()) {
    auto ret_ref = m_luaRefTa();
    return  ret_ref.cast<devs::TimeType>();
  }
  else
  {
    assert(false);
  }
  return devs::TIME_MAX;
}

void devs::core::JuScriptComponent::SecureBroadcast(luabridge::LuaRef msg)
{
  assert(pyb != nullptr);
  InsertSecureBroadcast(LuaRefToBlob(msg) , *pyb);
}

void devs::core::JuScriptComponent::ImmediateBroadcast(luabridge::LuaRef msg)
{
  assert(pyb != nullptr);
  InsertImmediateBroadcast(LuaRefToBlob(msg) , *pyb);
}

void devs::core::JuScriptComponent::InteriorBroadcast(luabridge::LuaRef msg)
{
  assert(pyb != nullptr);
  InsertInteriorBroadcast(LuaRefToBlob(msg) , *pyb);
}

msg::TimeSlice devs::core::JuScriptComponent::GetTS(){
  return this->ju.time_slice;
}

handler::TrackInformation devs::core::JuScriptComponent::GetLocalTrackInfo(std::string track_name)
{
  return ju.dict_local_track[track_name];
}

handler::TrackInformation devs::core::JuScriptComponent::GetRecvTrackInfo(std::string track_name)
{
  return ju.dict_recv_track[track_name];
}

int64_t devs::core::JuScriptComponent::GetR2(std::string track_name)
{
  return ju.dict_r2[track_name];
}

bool devs::core::JuScriptComponent::ExistLocalTrackInfo(std::string track_name)
{
  return ju.dict_local_track.exist(track_name);
}

bool devs::core::JuScriptComponent::ExistRecvTrackInfo(std::string track_name)
{
  return ju.dict_recv_track.exist(track_name);
}

bool devs::core::JuScriptComponent::ExistR2(std::string track_name)
{
  return ju.dict_r2.exist(track_name);
}

bool devs::core::JuScriptComponent::CorrelationTest(std::string track_name)
{
  return true;
}

luabridge::LuaRef devs::core::JuScriptComponent::ViewLocalTrackDict()
{
  luabridge::LuaRef view(plua , luabridge::newTable(plua));
  for(auto[key , value] : ju.dict_local_track) {
    view[key] = value;
  }
  return view;
}

luabridge::LuaRef devs::core::JuScriptComponent::ViewRecvTrackDict()
{
  luabridge::LuaRef view(plua , luabridge::newTable(plua));
  for(auto[key , value] : ju.dict_recv_track) {
    view[key] = value;
  }
  return view;
}

luabridge::LuaRef devs::core::JuScriptComponent::ViewR2Dict()
{
  luabridge::LuaRef view(plua , luabridge::newTable(plua));
  for(auto[key , value] : ju.dict_r2) {
    view[key] = value;
  }
  return view;
}

void devs::core::JuScriptComponent::SetR2(std::string track_name , int64_t time)
{
  ju.dict_r2[track_name] = time;
}

void devs::core::JuScriptComponent::InjectTheSoul()
{


  lua_handler::LuaInject<handler::EnumWrapper>(plua);
  lua_handler::LuaInject<msg::TimeSlice>(plua);
  lua_handler::LuaInject<msg::SubTimeSlice>(plua);
  lua_handler::LuaInject<msg::JointMsg2I>(plua);
  lua_handler::LuaInject<msg::JointMsg3I>(plua);
  lua_handler::LuaInject<msg::JointMsg7I>(plua);
  lua_handler::LuaInject<msg::LocalTrack>(plua);
  lua_handler::LuaInject<msg::LocalCmd>(plua);
  lua_handler::LuaInject<handler::TrackInformation>(plua);
  lua_handler::LuaInject<JuScriptComponent>(plua);
}

util::SptrBlob devs::core::JuScriptComponent::LuaRefToBlob(luabridge::LuaRef& luaref)
{
  auto type = static_cast<msg::MsgType>(luaref["type"].cast<int32_t>());
  switch(type)
  {
  case devs::message::Msg_JointMsgBase:
    //未注册:2019年9月24日 21:40
    assert(false);
    break;
  case devs::message::Msg_JointMsg2I:
    return util::CreateSptrBlob(luaref.cast<msg::JointMsg2I>());
    break;
  case devs::message::Msg_JointMsg3I:
    return util::CreateSptrBlob(luaref.cast<msg::JointMsg3I>());
    break;
  case devs::message::Msg_JointMsg7I:
    return util::CreateSptrBlob(luaref.cast<msg::JointMsg7I>());
    break;
  case devs::message::Msg_LocalTrack:
    return util::CreateSptrBlob(luaref.cast<msg::LocalTrack>());
    break;
  case devs::message::Msg_MissingTrack:
    //未注册:2019年9月24日 21:40
    assert(false);
    break;
  case devs::message::Msg_TimeSlice:
    return util::CreateSptrBlob(luaref.cast<msg::TimeSlice>());
    break;
  case devs::message::Msg_SubTimeSlice:
    return util::CreateSptrBlob(luaref.cast<msg::SubTimeSlice>());
    break;
  case devs::message::Msg_LocalCmd:
    return util::CreateSptrBlob(luaref.cast<msg::LocalCmd>());
    break;
  default:
    break;
  }

  assert(false);
  return nullptr;
}
