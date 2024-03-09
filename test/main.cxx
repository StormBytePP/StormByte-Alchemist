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
	const std::string expected_output = "123";
	std::string real_output;
	Alchemist::Executable exec1("/usr/bin/echo", "");

	exec1 << "1" << "2" << "3" << Alchemist::Executable::EoF;

	real_output << exec1;
	test_result(expected_output, real_output);

	exec1.wait();
}

void test2() {
	std::cout << "Test 2: " << std::flush;
	const std::string expected_output = "123";
	std::string real_output;
	Alchemist::Executable exec1("/usr/bin/echo", "");

	"1" >> exec1;
	"2" >> exec1;
	"3" >> exec1;
	Alchemist::Executable::EoF >> exec1;

	real_output << exec1;
	test_result(expected_output, real_output);

	exec1.wait();
}

void test3() {
	std::cout << "Test 3: " << std::flush;
	const std::string expected_output = "123";
	std::string real_output;
	Alchemist::Executable exec1("/usr/bin/echo", "");
	Alchemist::Executable exec2("/usr/bin/echo", "");
	exec1 >> exec2;
	exec1 << "1" << "2" << "3" << Alchemist::Executable::EoF;
	
	real_output << exec2;
	test_result(expected_output, real_output);

	exec2.wait();
	exec1.wait();
}

void test4() {
	std::cout << "Test 4: " << std::flush;
	const std::string expected_output = "123";
	std::string real_output;
	Alchemist::Executable exec1("/usr/bin/echo", "");
	Alchemist::Executable exec2("/usr/bin/echo", "");
	exec1 << "1" << "2" << "3";
	exec1 >> exec2;
	exec1 << Alchemist::Executable::EoF;
	real_output << exec2;
	test_result(expected_output, real_output);

	exec2.wait();
	exec1.wait();
}

void test5() {
	std::cout << "Test 5: " << std::flush;
	const std::string expected_output = "123";
	std::string real_output;
	Alchemist::Executable exec1("/usr/bin/echo", "");
	Alchemist::Executable exec2("/usr/bin/echo", "");
	exec1 << "1" << "2" << "3" << Alchemist::Executable::EoF;
	real_output << exec1;

	exec1 >> exec2; // No effect as it was eof already

	test_result(expected_output, real_output);

	exec2.wait();
	exec1.wait();
}

void test6() {
	std::cout << "Test 6: " << std::flush;
	const std::string expected_output = "123";
	std::string real_output;
	Alchemist::Executable exec1("/usr/bin/echo", "");
	Alchemist::Executable exec2("/usr/bin/echo", "");
	exec1 << "1" << "2" << "3" << Alchemist::Executable::EoF;
	exec1 >> exec2;
	
	real_output << exec2;
	test_result(expected_output, real_output);

	exec2.wait();
	exec1.wait();
}

int main() {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

	return 0;
}
