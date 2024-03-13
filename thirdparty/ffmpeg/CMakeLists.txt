#include(FetchContent)

ExternalProject_Add( [<option>...])

#FetchContent_Declare(
#  myCompanyIcons
#  URL      https://intranet.mycompany.com/assets/iconset_1.12.tar.gz
#  URL_HASH MD5=5588a7b18261c20068beabfb4f530b87
#)
#
#FetchContent_MakeAvailable(googletest myCompanyIcons)