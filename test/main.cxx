#include <system/executable.hxx>
#include <system/pipe.hxx>

#include <iostream>

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

#ifdef LINUX
void test1() {
	std::cout << "Test 1: " << std::flush;
	Alchemist::System::Executable exec1("/usr/bin/sort", {"-"});
	const std::string expected = "1\n2\n3\n";
	std::optional<std::string> returned;
	exec1 << "3\n" << "2\n" << "1\n" << Alchemist::System::Executable::EoF;
	exec1.wait();
	exec1 >> returned;
	test_result(expected, returned);
}

void test2() {
	std::cout << "Test 2: " << std::flush;
	Alchemist::System::Executable exec2("/usr/bin/tr", {"-d", "\n"});
	const std::string expected = "321";
	std::optional<std::string> returned;
	
	exec2 << "3\n" << "2\n" << "1\n" << Alchemist::System::Executable::EoF;

	exec2.wait();
	exec2 >> returned;
	test_result(expected, returned);
}

void test3() {
	std::cout << "Test 3: " << std::flush;
	Alchemist::System::Executable tr("/usr/bin/tr", {"-d", "\n"});
	Alchemist::System::Executable sort("/usr/bin/sort", {"-"});
	const std::string expected = "123";
	std::optional<std::string> returned;
	sort >> tr;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::System::Executable::EoF;

	sort.wait();
	tr.wait();
	tr >> returned;
	test_result(expected, returned);
}

void test4() {
	std::cout << "Test 4: " << std::flush;
	Alchemist::System::Executable tr("/usr/bin/tr", {"-d", "\n"});
	Alchemist::System::Executable sort("/usr/bin/sort", {"-"});
	Alchemist::System::Executable sed("/bin/sed", {"-e", "s/3/9/"});
	const std::string expected = "129";
	std::optional<std::string> returned;
	sort >> tr >> sed;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::System::Executable::EoF;

	sort.wait();
	tr.wait();
	sed.wait();

	sed >> returned;
	test_result(expected, returned);
}
#endif

void pipetest1() {
	std::cout << "Test Pipe 1: " << std::flush;
	Alchemist::System::Pipe p;

	p << "test";
	p.close_write();

	std::optional<std::string> result;
	p >> result;
	p.close_read();

	test_result("test", result);
}

int main() {
	#ifdef LINUX
	test1();
	test2();
	test3();
	test4();
	#endif
	pipetest1();

	return 0;
}
