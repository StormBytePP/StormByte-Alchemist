file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/installer/config.xml" CONTENT
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<Installer>
    <Name>${PROJECT_NAME}</Name>
    <Version>${${PROJECT_NAME}_VERSION_STRING}</Version>
    <Title>${PROJECT_NAME}</Title>
    <Publisher>StormByte &lt;stormbyte@gmail.com&gt;</Publisher>
    <StartMenuDir>${PROJECT_NAME}</StartMenuDir>
    <TargetDir>@ApplicationsDir@/Alchemist</TargetDir>
	<AllowSpaceInPath>true</AllowSpaceInPath>
	<WizardStyle>Aero</WizardStyle>
</Installer>"
)
install(FILES "${CMAKE_BINARY_DIR}/installer/config.xml" DESTINATION "${CMAKE_INSTALL_PREFIX}/../../../config" )

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/installer/package.xml" CONTENT
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<Package>
	<DisplayName>${PROJECT_NAME}</DisplayName>
	<Description>Install Alchemist</Description>
	<Version>0.1.0-1</Version>
	<ReleaseDate>2010-09-21</ReleaseDate>
	<Licenses>
		<License name=\"GNU General Public License v3.0\" file=\"license.txt\" />
	</Licenses>
	<Default>script</Default>
	<Script>installscript.qs</Script>
	<UserInterfaces>
		<UserInterface>page.ui</UserInterface>
	</UserInterfaces>
	<Translations>
        <Translation>es.qm</Translation>
    </Translations>
</Package>"
)
install(FILES "${CMAKE_BINARY_DIR}/installer/package.xml" DESTINATION "${CMAKE_INSTALL_PREFIX}/../../../packages/com.StormByte.Alchemist/meta" )