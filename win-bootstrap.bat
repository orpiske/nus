@echo This will delete every single Visual Studio project within this directory! 
@echo Removing any Visual Studio project file
@del *vcproj*
@echo Removing older cache
@del CMakeCache.txt
if exist CMakeFiles	@rd /s /q CMakeFiles
@echo Pre-configuring
@cmake -DMODULE_SECURITY:BOOLEAN=OFF -DMODULE_XML:BOOLEAN=OFF -DMODULE_NETWORK:BOOLEAN=OFF -DMODULE_EVENTS:BOOLEAN=OFF -DMODULE_DBAL:BOOLEAN=OFF -DMODULE_DBAL_MYSQL:BOOLEAN=OFF -DCMAKE_VERBOSE_MAKEFILE:BOOLEAN=ON -G "NMake Makefiles" .
@echo Configuring ...
@cmake -DMODULE_SECURITY:BOOLEAN=ON -DMODULE_XML:BOOLEAN=ON -DMODULE_NETWORK:BOOLEAN=ON -DMODULE_EVENTS:BOOLEAN=ON -DMODULE_DBAL:BOOLEAN=ON -DMODULE_DBAL_MYSQL:BOOLEAN=OFF -DCMAKE_VERBOSE_MAKEFILE:BOOLEAN=ON -G "NMake Makefiles" .
rem @echo Done :)