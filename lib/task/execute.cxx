#include "execute.hxx"
#include "utils/display.hxx"

#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>

#include <vector>
#include <string>
#include <boost/process.hpp>
#include <boost/asio.hpp>

using namespace StormByte::VideoConvert;

Task::Execute::Execute(const Types::path_t& program):Base(), m_program(program) {
	m_require_logger = true;
}

int Task::Execute::run_wait(std::optional<pid_t>& worker) {
	using namespace boost;

	asio::io_service ios;

	// stdout setup
	//
	std::vector<char> vOut(128 << 10);           // that worked well for my decoding app.
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
	//
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
	//
	auto inBuffer{ asio::buffer("") };
	process::async_pipe pipeIn(ios);

	process::child c(
		m_program.string() + " " + m_arguments,
		process::std_out > pipeOut, 
		process::std_err > pipeErr, 
		process::std_in < pipeIn
	);

	
	asio::async_write(pipeIn, inBuffer, 
		[&](const system::error_code&, std::size_t) {
			pipeIn.async_close();                     //  tells the child we have no more data
		});

	asio::async_read(pipeOut, outBuffer, onStdOut);
	asio::async_read(pipeErr, errBuffer, onStdErr);
	
	// We update worker BEFORE this is run as this is a blocking call
	worker = c.id();
	ios.run();
	c.wait();
	worker.reset();

	return c.exit_code();
}

Task::STATUS Task::Execute::run(Types::config_t config, std::optional<pid_t>& worker) noexcept {
	if (Base::run(config) == RUNNING) {
		set_arguments();

		// Clear output so run can be called more than once
		m_stdout = "";
		m_stderr = "";

		try {
			int status = run_wait(worker);
			if (status == 0) m_status = HALT_OK; else m_status = HALT_ERROR;
		}
		catch (const std::exception&) {
			m_status = HALT_ERROR;
		}
	}
	return m_status;
}

Task::STATUS Task::Execute::run(Types::config_t config) noexcept {
	std::optional<pid_t> useless;
	STATUS status = run(config, useless);
	return status;
}
