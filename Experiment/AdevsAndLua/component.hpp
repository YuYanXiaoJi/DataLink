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
    const devs::Port odd  = devs::Port("Odd");
    const devs::Port even = devs::Port("Even");
    const devs::Port print = devs::Port("Print");
    const devs::Port send = devs::Port("Send");
  private:
    Generator       &parent;
    devs::Digraph   &digrapg;
  public:
    std::list<devs::SptrBlob> buffer_list;


  };

}