#include <executable.hxx>
#include <system/pipe.hxx>

#include <iostream>
#include <sys/wait.h>

void test_result(const std::string& expected, const std::string& real) {
	if (expected == real)
		std::cout << "OK";
	else
		std::cout << "ERROR (expected: " << expected << ", got: " << real << ")";
	std::cout << std::endl;
}

void test_result(const std::string& expected, const std::optional<std::string>& real) {
	test_result(expected, real.value_or("<EMPTY>"));
}

void test1() {
	std::cout << "Test 1: " << std::flush;
	Alchemist::Executable exec1("/usr/bin/sort", {"-"});
	const std::string expected = "1\n2\n3\n";
	std::optional<std::string> returned;
	exec1 << "3\n" << "2\n" << "1\n" << Alchemist::Executable::EoF;
	exec1.wait();
	exec1 >> returned;
	test_result(expected, returned);
}

void test2() {
	std::cout << "Test 2: " << std::flush;
	Alchemist::Executable exec2("/usr/bin/tr", {"-d", "\n"});
	const std::string expected = "321";
	std::optional<std::string> returned;
	
	exec2 << "3\n" << "2\n" << "1\n" << Alchemist::Executable::EoF;

	exec2.wait();
	exec2 >> returned;
	test_result(expected, returned);
}

void test3() {
	std::cout << "Test 3: " << std::flush;
	Alchemist::Executable tr("/usr/bin/tr", {"-d", "\n"});
	Alchemist::Executable sort("/usr/bin/sort", {"-"});
	const std::string expected = "123";
	std::optional<std::string> returned;
	sort >> tr;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::Executable::EoF;

	sort.wait();
	tr.wait();
	tr >> returned;
	test_result(expected, returned);
}

void test4() {
	std::cout << "Test 4: " << std::flush;
	Alchemist::Executable tr("/usr/bin/tr", {"-d", "\n"});
	Alchemist::Executable sort("/usr/bin/sort", {"-"});
	Alchemist::Executable sed("/usr/bin/sed", {"-e", "s/3/9/"});
	const std::string expected = "129";
	std::optional<std::string> returned;
	sort >> tr >> sed;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::Executable::EoF;
	
	sort.wait();
	tr.wait();
	sed.wait();

	sed >> returned;
	test_result(expected, returned);
}

void testpipe() {
	int p[2];
	pipe(p);

	if (fork() == 0) {
		close(p[0]);
		write(p[1], "Test", sizeof(char) * 5);
		close(p[1]);
		exit(0);
	}
	else {
		int status;
		std::optional<std::string> read;
		close(p[1]);
		char buffer[100];
		auto bytes = ::read(p[0], buffer, 100);
		const std::string red_data(buffer, bytes);
		wait(&status);
		close(p[0]);
	}
}

void testpipeobj() {
	std::cout << "Test PipeOBJ: " << std::flush;
	Alchemist::System::Pipe p;

	if (fork() == 0) {
		p.close_read();
		p.bind_write(STDOUT_FILENO);
		std::cout << "Test";
		exit(0);
	}
	else {
		int status;
		std::optional<std::string> read;
		p.close_write();
		p >> read;
		p.close_read();
		wait(&status);
		test_result("Test", read.value_or("<EMPTY>"));
	}
}

void testpipeobj2() {
	std::cout << "Test PipeOBJ 2: " << std::flush;
	Alchemist::System::Pipe p_in, p_out;

	if (fork() == 0) {
		p_in.close_write();
		p_in.bind_read(STDIN_FILENO);
		p_out.close_read();
		p_out.bind_write(STDOUT_FILENO);

		std::string received;
		std::cin >> received;

		std::cout << "R: " << received << std::flush;
		exit(0);
	}
	else {
		p_in.close_read();
		p_out.close_write();
		p_in << "Test";
		p_in.close_write();
		int status;
		std::optional<std::string> read;
		p_out >> read;

		wait(&status);
		test_result("R: Test", read.value_or("<EMPTY>"));
	}
}

void testpipeobj3() {
	std::cout << "Test PipeOBJ 2: " << std::flush;
	Alchemist::System::Pipe p_in, p_out;

	if (fork() == 0) {
		p_in.close_write();
		p_in.bind_read(STDIN_FILENO);
		p_out.close_read();
		p_out.bind_write(STDOUT_FILENO);

		char* argv[] = {const_cast<char*>("sort"), const_cast<char*>("-"), NULL};
		execvp("/usr/bin/sort", argv);
		exit(0);
	}
	else {
		p_in.close_read();
		p_out.close_write();
		p_in << "3\n" << "2\n" << "1\n";
		p_in.close_write();
		int status;
		std::optional<std::string> read;
		p_out >> read;

		wait(&status);
		test_result("1\n2\n3\n", read.value_or("<EMPTY>"));
	}
}

int main() {
	test1();
	test2();
	test3();
	//test4();
	testpipe();
	testpipeobj();
	testpipeobj2();
	testpipeobj3();

	return 0;
}
