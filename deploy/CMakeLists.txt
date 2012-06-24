MACRO(DeployModule VAR MOD_NAME FILE_NAME PATH)
	IF (${VAR})
		MESSAGE(STATUS "Writing deployment scripts for ${MOD_NAME}")
		
		INCLUDE(../${PATH}/${FILE_NAME}.cmake)
	ENDIF(${VAR})
ENDMACRO(DeployModule)

# DeployModule(MODULE_BASE NBase NBaseInstall src/base)
# DeployModule(MODULE_NETWORK NNetwork NNetworkInstall src/network)
# DeployModule(MODULE_EVENTS NEvents NEventsInstall src/events)
# DeployModule(MODULE_XML NXml NXmlInstall src/xml)
# DeployModule(MODULE_SECURITY NSecurity NSecurityInstall src/security)