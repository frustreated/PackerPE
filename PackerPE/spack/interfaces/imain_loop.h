#pragma once

#include "ipacker_base.h"
#include "iloader_packer.h"
#include "istub_packer.h"
#include "isections_packer.h"
#include "iimport_packer.h"
#include <forward_list>

class IMainLoop
{
public:
  IMainLoop(const std::string& srcFilePath, const std::string& destFilePath) :
    srcFilePath_(srcFilePath),
    destFilePath_(destFilePath)
  {}
  IMainLoop(const std::string& srcFilePath, const std::string& destFilePath, std::forward_list<IPackerBasePtr>&& packersVt) :
    IMainLoop(srcFilePath, destFilePath)
  {
    packersVt_ = std::move(packersVt);
  }

  void AddPacker(IPackerBasePtr&& packer)
  {
    packersVt_.push_front(packer);
  }

protected:
  virtual bool PackerIsReady(PackerType packerType, const std::set<PackerType>& readyPackersVt) const = 0;
  virtual ErrorCode PackFile() = 0;

  std::forward_list<IPackerBasePtr> packersVt_;
  const std::string srcFilePath_;
  const std::string destFilePath_;
};