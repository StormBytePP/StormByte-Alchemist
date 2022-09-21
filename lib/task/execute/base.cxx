#include "base.hxx"

#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <boost/process.hpp>
#include <boost/asio.hpp>

using namespace StormByte::VideoConvert;

Task::Execute::Base::Base(const Types::path_t& program, const std::string& arguments):Task::Base(), m_executables({ Executable(program, arguments) }) {}

Task::Execute::Base::Base(Types::path_t&& program, std::string&& arguments):Task::Base(), m_executables({ Executable(std::move(program), std::move(arguments)) }) {}

Task::Execute::Base::Base(const std::vector<Executable>& execs):Task::Base(), m_executables(execs) {}

Task::Execute::Base::Base(std::vector<Executable>&& execs):Task::Base(), m_executables(std::move(execs)) {}


Task::STATUS Task::Execute::Base::do_work(std::optional<pid_t>& worker) noexcept {
	using namespace boost;

	STATUS status = STOPPED;
	asio::io_service ios;

	try {
		// stdout setup
		std::vector<char> vOut(128 << 10);
		auto outBuffer{ asio::buffer(vOut) };
		process::async_pipe pipeOut(ios);

		std::function<void(const system::error_code & ec, std::size_t n)> onStdOut;
		onStdOut = [&](const system::error_code & ec, size_t n)
		{
			m_stdout.reserve(m_stdout.size() + n);
			m_stdout.insert(m_stdout.end(), vOut.begin(), vOut.begin() + n);
			if (!ec) {
				asio::async_read(pipeOut, outBuffer, onStdOut);
			}
		};

		// stderr setup
		std::vector<char> vErr(128 << 10);
		auto errBuffer{ asio::buffer(vErr) };
		process::async_pipe pipeErr(ios);

		std::function<void(const system::error_code & ec, std::size_t n)> onStdErr;
		onStdErr = [&](const system::error_code & ec, size_t n) {
			m_stderr.reserve(m_stderr.size() + n);
			m_stderr.insert(m_stderr.end(), vErr.begin(), vErr.begin() + n);
			if (!ec)
			{
				asio::async_read(pipeErr, errBuffer, onStdErr);
			}
		};

		// stdin setup
		auto inBuffer{ asio::buffer(m_stdin) };
		process::async_pipe pipeIn(ios);

		process::child c(
			m_executables[0].m_program.string() + " " + m_executables[0].m_arguments,
			process::std_out > pipeOut, 
			process::std_err > pipeErr, 
			process::std_in < pipeIn
		);

		
		asio::async_write(pipeIn, inBuffer, 
			[&](const system::error_code&, std::size_t) {
				pipeIn.async_close(); //  tells the child we have no more data
			});

		asio::async_read(pipeOut, outBuffer, onStdOut);
		asio::async_read(pipeErr, errBuffer, onStdErr);
		
		// We update worker BEFORE this is run as this is a blocking call
		worker = c.id();
		ios.run();
		c.wait();
		if (c.exit_code() == 0) status = HALT_OK; else status = HALT_ERROR;
	}
	catch (const std::exception&) {
		status = HALT_ERROR;
	}
	worker.reset();

	return status;
}

Task::STATUS Task::Execute::Base::pre_run_actions() noexcept {
	m_stdout = "";
	m_stdin = "";
	return RUNNING;
}
