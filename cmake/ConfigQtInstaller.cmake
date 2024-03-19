add_custom_target(package
	${QT_DIR}/../../../../../Tools/QtInstallerFramework/4.7/bin/binarycreator.exe --offline-only -c config/config.xml -p packages install.exe
	COMMAND echo "Installable exe created in ${CMAKE_SOURCE_DIR}/dist/install.exe"
	WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/../../.."
	DEPENDS install
)