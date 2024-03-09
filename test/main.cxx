#include <executable.hxx>

#include <iostream>

void test_result(const std::string& expected, const std::string& real) {
	if (expected == real)
		std::cout << "OK";
	else
		std::cout << "ERROR (expected: " << expected << ", got: " << real << ")";
	std::cout << std::endl;
}

void test1() {
	std::cout << "Test 1: " << std::flush;
	Alchemist::Executable exec1("/usr/bin/sort", {"-"});
	const std::string expected = "1\n2\n3\n";
	std::string returned;
	exec1 << "3\n" << "2\n" << "1\n" << Alchemist::Executable::EoF;
	exec1.wait();
	exec1 >> returned;
	test_result(expected, returned);
}

void test2() {
	std::cout << "Test 2: " << std::flush;
	Alchemist::Executable exec2("/usr/bin/tr", {"-d", "\n"});
	const std::string expected = "321";
	std::string returned;
	
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
	std::string returned;
	sort >> tr;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::Executable::EoF;

	sort.wait();
	tr.wait();
	tr >> returned;
	test_result(expected, returned);
}

int main() {
	test1();
	test2();
	test3();

	return 0;
}
