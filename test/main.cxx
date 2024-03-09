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
	returned << exec1;
	test_result(expected, returned);
	
}

int main() {
	test1();

	return 0;
}
