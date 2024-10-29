#include "executable.hxx"
#include "worker.hxx"

using namespace Alchemist::System;

Worker::Worker(std::unique_ptr<Executable>&& exec):m_executable(std::move(exec)) {}