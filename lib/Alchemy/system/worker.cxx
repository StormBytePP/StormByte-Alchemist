#include <Alchemy/system/executable.hxx>
#include <Alchemy/system/worker.hxx>

using namespace Alchemist::System;

Worker::Worker(std::unique_ptr<Executable>&& exec):m_executable(std::move(exec)) {}