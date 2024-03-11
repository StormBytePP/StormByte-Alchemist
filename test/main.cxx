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

int main() {
	test1();
	test2();
	test3();
	test4();

	return 0;
}
