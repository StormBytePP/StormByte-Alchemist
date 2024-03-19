add_custom_target(package
	${QT_DIR}/../../../../../Tools/QtInstallerFramework/4.7/bin/binarycreator.exe -c config/config.xml -p packages -e org.StormByte.Alchemist install.exe
	COMMAND echo "Installable exe created in ${CMAKE_SOURCE_DIR}/dist/install.exe"
	WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/../../.."
	DEPENDS install
)

add_custom_target(repository
	${QT_DIR}/../../../../../Tools/QtInstallerFramework/4.7/bin/repogen.exe -p packages -i org.StormByte.Alchemist repository
	COMMAND echo "Repository contents created in ${CMAKE_SOURCE_DIR}/dist/repository"
	WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/../../.."
	DEPENDS install
)