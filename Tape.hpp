#pragma once

#include <list>
#include <array>

class Tape
{
  public:
    Tape();

    void operator++();
    void operator--();
    const char& operator*() const;
    char& operator*();

  private:
    using StorageBlock = std::array<char, 4096>;
    using BlockList = std::list<StorageBlock>;

    BlockList storage_;
    BlockList::iterator block_it_;
    StorageBlock::iterator data_it_;

    BlockList::iterator addFront();
    BlockList::iterator addBack();
};
