#pragma once
#include"devs.hpp"
#include"generator.hpp"
#include<list>
namespace cc {
  class Component :
    public devs::AtomicAbstract {
  public:
    Component(devs::Digraph &digrapg, Generator &parent):parent(parent), digrapg(digrapg){/* pass */}

    inline void BindOdd() {
      digrapg.couple(&parent, parent.odd, this, odd);
    }

    inline void BindEven() {
      digrapg.couple(&parent, parent.even, this, even);
    }

    inline void BindPrint() {
      digrapg.couple(&parent, parent.print, this, print);
    }

    inline void BindSend() {
      digrapg.couple(this, send,&parent,parent.recv);
    }

  public:
    const devs::PortType odd  = devs::PortType("Odd");
    const devs::PortType even = devs::PortType("Even");
    const devs::PortType print = devs::PortType("Print");
    const devs::PortType send = devs::PortType("Send");
  private:
    Generator       &parent;
    devs::Digraph   &digrapg;
  public:
    std::list<SptrBlob> buffer_list;


  };

}