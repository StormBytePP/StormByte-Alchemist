include(FetchContent)

FetchContent_Declare(ffmpeg
    URL      https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-full.7z
    DOWNLOAD_EXTRACT_TIMESTAMP false
)
FetchContent_MakeAvailable(ffmpeg)

if(NOT ffmpeg_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(ffmpeg)
endif()

install(FILES
    "${ffmpeg_SOURCE_DIR}/bin/ffmpeg.exe"
    "${ffmpeg_SOURCE_DIR}/bin/ffprobe.exe"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/external"
)
