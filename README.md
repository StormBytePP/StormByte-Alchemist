# StormByte Video Convert

This is a program to handle automatic ffmpeg conversions between downloaded videos in order to convert them to desired format.

## Basic information

### Requirements

* Compiler with C++20 support
* [libConfig++](http://hyperrealm.github.io/libconfig) A library to parse config files
* [SQlite3](https://www.sqlite.org/index.html) A lite database manager
* [FFmpeg](https://ffmpeg.org) Multimedia converter software
* [CMake](https://cmake.org/) Build system

### Personal annotation:

_I usually like to store videos in H265 format in order to save space (specially in 4K films). In order to achieve that, I started by having a text file with the proper FFmpeg command that I usually copy/paste in a terminal modifying it to meet target file specs yet soon I realized that it is a repetitive task and left my little server mostly idle when it finished a conversion._

_So finally when I found time, I programmed this little daemon as a **hello world** application because I never used some of the components I used here, like:_

* _libConfig++: To read and parse configuration files in an application_
* _SQlite3: To make use of a little database_
* _C++17: Features like std::filesystem, std::shared_ptr, std::unique_ptr and std::optional which I never used (and they are great!)_

_So once I started, this quickly became addictive and now that it is finished I'm very glad this works!_

## How to install

### Compile and install instructions

In order to compile it download and unpack the source code to a folder and run `cmake <source_code_folder>` to _configure_, `make` to _compile_ and finally `make install` (remember to use `sudo` or similar to get root privileges for install).

### Optional features

There are some codecs to use which need to be enabled when running configure stage, this are the optional codecs to be supported (please make sure your FFmpeg support those codecs before enabling it, otherwise your files will not be converted to those) along with the CMake options to enable them:

* **-DENABLE_HEVC=ON**: Enable libx265 codec for H.265 content
* **-DENABLE_AAC=ON**: Enable the Advanced Audio Codec
* **-DENABLE_FDKAAC=ON**: Enable the Advanced Audio Codec via Fraunhoffer encoder (not GPL!)
* **-DENABLE_AC3=ON**: Enable Dolby's AC-3 codec
* **-DENABLE_EAC3=ON**: Enable Dolby's Enhanced AC-3 codec
* **-DENABLE_OPUS=ON**: Enable Opus codec via libopus encoder

It is possible that support for more codecs come in the future!

## How to use

### Configuration

First of all, check file `/etc/conf.d/StormByte-videoconvert.conf` file and edit it according to your needs and folders

### Adding films to convert queue

Just call `StormByte-videoconvert --add <film_relative_path>` remembering that path should be relative to `input` path you set in config and follow on screen instructions.

### Starting the daemon

If daemon have not been started yet, you can start it via `/etc/init.d/StormByte-videoconvert start` command or manually by `StormByte-videoconvert --daemon`, if it does not start successfully will print error message and if it does will output to `logfile` set in config.

The daemon will query database every `sleep` configured seconds and if it finds a film for convert it will attempt to do that, working temporarily in `work` directory and finally storing its result (if successful) in `output` directory.

### Getting help

The program comes with a mini-help that can be invoked any time by running `StormByte-videoconvert --help` command.
