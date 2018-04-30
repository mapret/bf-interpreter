#include "Tape.hpp"

Tape::Tape()
{
  //Create first storage block
  block_it_ = addBack();
  data_it_ = block_it_->begin();
}

void Tape::operator++()
{
  data_it_++;

  //If current block is being left go to next block
  if (data_it_ == block_it_->end())
  {
    block_it_++;
    //If the current block was the last one, append a new block
    if (block_it_ == storage_.end())
      block_it_ = addBack();
    data_it_ = block_it_->begin();
  }
}

void Tape::operator--()
{
  //If current block os being left go to previous block
  if (data_it_ == block_it_->begin())
  {
    //If the current block is the first one, prepend a new block
    if (block_it_ == storage_.begin())
      block_it_ = addFront();
    else
      block_it_--;
    data_it_ = block_it_->end();
  }
  data_it_--;
}

const char& Tape::operator*() const
{
  return *data_it_;
}

char& Tape::operator*()
{
  return *data_it_;
}

Tape::BlockList::iterator Tape::addFront()
{
  storage_.push_front(StorageBlock{0});
  return storage_.begin();
}

Tape::BlockList::iterator Tape::addBack()
{
  storage_.push_back(StorageBlock{0});
  return --storage_.end();
}
