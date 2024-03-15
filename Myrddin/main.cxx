#include <system/executable.hxx>
#include <system/pipe.hxx>
#include <media/file.hxx>

#include <iostream>

void test_result(const std::string& expected, const std::string& real) {
	if (expected == real)
		std::cout << "OK";
	else
		std::cout << "ERROR (expected: " << expected << ", got: " << real << ")";
	std::cout << std::endl;
}

void test_exit_code(int expected, int real) {
	if (expected == real)
		std::cout << "OK";
	else
		std::cout << "ERROR (expected exit code: " << expected << ", got: " << real << ")";
	std::cout << std::endl;
}

/*
#ifdef LINUX
void test1() {
	std::cout << "Test 1: " << std::flush;
	Alchemist::System::Executable exec1("/usr/bin/sort", {"-"});
	const std::string expected = "1\n2\n3\n";
	std::string returned;
	exec1 << "3\n" << "2\n" << "1\n" << Alchemist::System::EoF;
	exec1.wait();
	exec1 >> returned;
	test_result(expected, returned);
}

void test2() {
	std::cout << "Test 2: " << std::flush;
	Alchemist::System::Executable exec2("/usr/bin/tr", {"-d", "\n"});
	const std::string expected = "321";
	std::string returned;
	
	exec2 << "3\n" << "2\n" << "1\n" << Alchemist::System::EoF;

	exec2.wait();
	exec2 >> returned;
	test_result(expected, returned);
}

void test3() {
	std::cout << "Test 3: " << std::flush;
	Alchemist::System::Executable tr("/usr/bin/tr", {"-d", "\n"});
	Alchemist::System::Executable sort("/usr/bin/sort", {"-"});
	const std::string expected = "123";
	std::string returned;
	sort >> tr;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::System::EoF;

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
	std::string returned;
	sort >> tr >> sed;
	sort << "3\n" << "2\n" << "1\n" << Alchemist::System::EoF;

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

	std::string result;
	p >> result;
	p.close_read();

	test_result("test", result);
}

void testfilm() {
	std::cout << "Test film with HDR+: " << std::flush;
	#ifdef LINUX
	Alchemist::System::Executable ffmpeg("ffmpeg", { "-hide_banner", "-loglevel", "panic", "-i", "/StormWarehouse/PRUEBAPELI/prueba_con.mkv", "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-" });
	Alchemist::System::Executable hdr10plus_tool("hdr10plus_tool", { "--verify", "extract", "-" });
	#else
	Alchemist::System::Executable ffmpeg("C:\\Users\\Storm\\Desktop\\Alchemist\\install\\bin\\external\\ffmpeg.exe", { "-hide_banner", "-loglevel", "panic", "-i", "D:\\PRUEBAPELI\\prueba_con.mkv", "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-" });
	Alchemist::System::Executable hdr10plus_tool("C:\\Users\\Storm\\Desktop\\Alchemist\\install\\bin\\external\\hdr10plus_tool.exe", { "--verify", "extract", "-" });
	#endif
	ffmpeg >> hdr10plus_tool;
	const std::string expected = "Dynamic HDR10+ metadata detected.\n";
	ffmpeg.wait();
	hdr10plus_tool.wait();

	std::string result;
	hdr10plus_tool >> result;
	
	test_result(expected, result);
}

void testfilm2() {
	std::cout << "Test film with HDR+ (2): " << std::flush;
#ifdef LINUX
	Alchemist::System::Executable ffmpeg("ffmpeg", { "-hide_banner", "-loglevel", "panic", "-i", "/StormWarehouse/PRUEBAPELI/prueba_con.mkv", "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-" });
	Alchemist::System::Executable hdr10plus_tool("hdr10plus_tool", { "--verify", "extract", "-" });
#else
	Alchemist::System::Executable ffmpeg("C:\\Users\\Storm\\Desktop\\Alchemist\\install\\bin\\external\\ffmpeg.exe", { "-hide_banner", "-loglevel", "panic", "-i", "D:\\PRUEBAPELI\\prueba_con.mkv", "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-" });
	Alchemist::System::Executable hdr10plus_tool("C:\\Users\\Storm\\Desktop\\Alchemist\\install\\bin\\external\\hdr10plus_tool.exe", { "--verify", "extract", "-" });
#endif
	ffmpeg >> hdr10plus_tool;
	const std::string expected = "Dynamic HDR10+ metadata detected.\n";
	ffmpeg.wait();
	auto exit_code = hdr10plus_tool.wait();

	test_exit_code(0, exit_code);
}

void testfilm3() {
	std::cout << "Test film without HDR+: " << std::flush;
#ifdef LINUX
	Alchemist::System::Executable ffmpeg("ffmpeg", { "-hide_banner", "-loglevel", "panic", "-i", "/StormWarehouse/PRUEBAPELI/prueba_sin.mkv", "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-" });
	Alchemist::System::Executable hdr10plus_tool("hdr10plus_tool", { "--verify", "extract", "-" });
#else
	Alchemist::System::Executable ffmpeg("C:\\Users\\Storm\\Desktop\\Alchemist\\install\\bin\\external\\ffmpeg.exe", { "-hide_banner", "-loglevel", "panic", "-i", "D:\\PRUEBAPELI\\prueba_sin.mkv", "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-" });
	Alchemist::System::Executable hdr10plus_tool("C:\\Users\\Storm\\Desktop\\Alchemist\\install\\bin\\external\\hdr10plus_tool.exe", { "--verify", "extract", "-" });
#endif
	ffmpeg >> hdr10plus_tool;
	const std::string expected = "Dynamic HDR10+ metadata detected.\n";
	ffmpeg.wait();
	auto exit_code = hdr10plus_tool.wait();

	test_exit_code(1, exit_code);
}
*/

int main() {
	/*
	#ifdef LINUX
	test1();
	test2();
	test3();
	test4();
	#endif
	pipetest1();
	testfilm();
	testfilm2();
	testfilm3();
	*/

	std::unique_ptr<Alchemist::Media::File> f;

	f = std::make_unique<Alchemist::Media::File>("/StormWarehouse/PRUEBAPELI/prueba_con.mkv");
	std::cout << "File 1" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR))
		std::cout << "* Has HDR" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
		std::cout << "* Has HDR+" << std::endl;

	f = std::make_unique<Alchemist::Media::File>("/StormWarehouse/PRUEBAPELI/prueba_sin.mkv");
	std::cout << "File 2" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR))
		std::cout << "* Has HDR" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
		std::cout << "* Has HDR+" << std::endl;

	return 0;
}

