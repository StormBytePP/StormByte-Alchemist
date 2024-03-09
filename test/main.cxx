#include <executor.hxx>
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
	exec2 << Alchemist::Executable::EoF;
	
	real_output << exec2;
	test_result(expected_output, real_output);

	exec2.wait();
	exec1.wait();
}

int main() {
	// Este ejemplo ha ido muy bien
	// Alchemist::Executor exec1("/usr/bin/echo", "");
	// Alchemist::Executor exec2("/usr/bin/echo", "");
	// exec1 << "1\n" << "2\n" << "3\n" << Alchemist::Executor::EoF;
	// exec2 << "4\n" << "5\n" << "6\n";
	// exec1 << "7\n" << "8\n";
	// exec1 >> exec2;
	// std::cout << exec2;
	// exec2.wait();
	// exec1.wait();
	// Alchemist::Executable exec1("/usr/bin/echo", "");
	// Alchemist::Executable exec2("/usr/bin/echo", "");
	// exec1 << "1\n" << "2\n" << "3\n" << Alchemist::Executable::EoF;
	// exec2 << "9\n" << "8\n" << "7\n"; // << Alchemist::Executable::EoF;
	// //exec1 >> exec2; // Does not work yet
	// //exec2 << Alchemist::Executable::EoF; // Should NOT be needed
	// std::cout << "Exec1: " << std::endl;
	// std::cout << exec1;
	// std::cout << "Exec2: " << std::endl;
	// std::cout << exec2;
	// exec2.wait();
	// exec1.wait();

	test1();
	test2();
	test3();
	return 0;
}

// #include <unistd.h>

// int main(void)
// {
//     int ABtoC[2];
//     pipe(ABtoC);

//     if (fork() > 0)
//     {
//         // Process A
//         close(ABtoC[0]);
//         dup2(ABtoC[1], STDOUT_FILENO);
//         close(ABtoC[1]);     // Close this too!
//         // Process A writing to C
//         for (int i = 0; i < 100; i++)
//         {
//             write(STDOUT_FILENO, "Hi\n", sizeof("Hi\n")-1);
//             usleep(5000);
//         }
//     }
//     else if (fork() > 0)
//     {
//         // Process B
//         close(ABtoC[0]);
//         dup2(ABtoC[1], STDOUT_FILENO);
//         close(ABtoC[1]);
//         // Process B writing to C
//         for (int i = 0; i < 100; i++)
//         {
//             write(STDOUT_FILENO, "Lo\n", sizeof("Lo\n")-1);
//             usleep(5000);
//         }
//     }
//     else
//     {
//         char buffer[100];
//         ssize_t nbytes;
//         close(ABtoC[1]);
//         dup2(ABtoC[0], STDIN_FILENO);
//         close(ABtoC[0]);
//         // Process C reading from both A and B
//         while ((nbytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
//             write(STDOUT_FILENO, buffer, nbytes);
//     }
//     return(0);
// }