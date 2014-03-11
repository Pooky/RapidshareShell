##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Rapidshare
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/worker/Rapidshare"
ProjectPath            := "/home/worker/Rapidshare"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Worker
Date                   :=30.9.2012
CodeLitePath           :="/home/worker/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/worker/Rapidshare/Rapidshare.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -O0 -Wall $(Preprocessors)
C_CmpOptions           := -g -O0 -Wall $(Preprocessors)
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -lcurl -lboost_regex -lncurses
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := $(IncludeSwitch)include 
Libs                   := 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/src_curlClient$(ObjectSuffix) $(IntermediateDirectory)/src_File$(ObjectSuffix) $(IntermediateDirectory)/src_Manager$(ObjectSuffix) $(IntermediateDirectory)/src_Rapidshare$(ObjectSuffix) $(IntermediateDirectory)/src_Folder$(ObjectSuffix) $(IntermediateDirectory)/include_Browser$(ObjectSuffix) $(IntermediateDirectory)/src_Buffer$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/worker/Rapidshare/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/worker/Rapidshare/main.cpp"

$(IntermediateDirectory)/src_curlClient$(ObjectSuffix): src/curlClient.cpp $(IntermediateDirectory)/src_curlClient$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/src/curlClient.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_curlClient$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_curlClient$(DependSuffix): src/curlClient.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_curlClient$(ObjectSuffix) -MF$(IntermediateDirectory)/src_curlClient$(DependSuffix) -MM "/home/worker/Rapidshare/src/curlClient.cpp"

$(IntermediateDirectory)/src_curlClient$(PreprocessSuffix): src/curlClient.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_curlClient$(PreprocessSuffix) "/home/worker/Rapidshare/src/curlClient.cpp"

$(IntermediateDirectory)/src_File$(ObjectSuffix): src/File.cpp $(IntermediateDirectory)/src_File$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/src/File.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_File$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_File$(DependSuffix): src/File.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_File$(ObjectSuffix) -MF$(IntermediateDirectory)/src_File$(DependSuffix) -MM "/home/worker/Rapidshare/src/File.cpp"

$(IntermediateDirectory)/src_File$(PreprocessSuffix): src/File.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_File$(PreprocessSuffix) "/home/worker/Rapidshare/src/File.cpp"

$(IntermediateDirectory)/src_Manager$(ObjectSuffix): src/Manager.cpp $(IntermediateDirectory)/src_Manager$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/src/Manager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Manager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Manager$(DependSuffix): src/Manager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Manager$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Manager$(DependSuffix) -MM "/home/worker/Rapidshare/src/Manager.cpp"

$(IntermediateDirectory)/src_Manager$(PreprocessSuffix): src/Manager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Manager$(PreprocessSuffix) "/home/worker/Rapidshare/src/Manager.cpp"

$(IntermediateDirectory)/src_Rapidshare$(ObjectSuffix): src/Rapidshare.cpp $(IntermediateDirectory)/src_Rapidshare$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/src/Rapidshare.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Rapidshare$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Rapidshare$(DependSuffix): src/Rapidshare.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Rapidshare$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Rapidshare$(DependSuffix) -MM "/home/worker/Rapidshare/src/Rapidshare.cpp"

$(IntermediateDirectory)/src_Rapidshare$(PreprocessSuffix): src/Rapidshare.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Rapidshare$(PreprocessSuffix) "/home/worker/Rapidshare/src/Rapidshare.cpp"

$(IntermediateDirectory)/src_Folder$(ObjectSuffix): src/Folder.cpp $(IntermediateDirectory)/src_Folder$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/src/Folder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Folder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Folder$(DependSuffix): src/Folder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Folder$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Folder$(DependSuffix) -MM "/home/worker/Rapidshare/src/Folder.cpp"

$(IntermediateDirectory)/src_Folder$(PreprocessSuffix): src/Folder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Folder$(PreprocessSuffix) "/home/worker/Rapidshare/src/Folder.cpp"

$(IntermediateDirectory)/include_Browser$(ObjectSuffix): include/Browser.cpp $(IntermediateDirectory)/include_Browser$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/include/Browser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/include_Browser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/include_Browser$(DependSuffix): include/Browser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/include_Browser$(ObjectSuffix) -MF$(IntermediateDirectory)/include_Browser$(DependSuffix) -MM "/home/worker/Rapidshare/include/Browser.cpp"

$(IntermediateDirectory)/include_Browser$(PreprocessSuffix): include/Browser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/include_Browser$(PreprocessSuffix) "/home/worker/Rapidshare/include/Browser.cpp"

$(IntermediateDirectory)/src_Buffer$(ObjectSuffix): src/Buffer.cpp $(IntermediateDirectory)/src_Buffer$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/worker/Rapidshare/src/Buffer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Buffer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Buffer$(DependSuffix): src/Buffer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Buffer$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Buffer$(DependSuffix) -MM "/home/worker/Rapidshare/src/Buffer.cpp"

$(IntermediateDirectory)/src_Buffer$(PreprocessSuffix): src/Buffer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Buffer$(PreprocessSuffix) "/home/worker/Rapidshare/src/Buffer.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_curlClient$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_curlClient$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_curlClient$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_File$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_File$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_File$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Manager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Manager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Manager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Rapidshare$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Rapidshare$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Rapidshare$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Folder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Folder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Folder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/include_Browser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/include_Browser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/include_Browser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Buffer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Buffer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Buffer$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/worker/Rapidshare/.build-debug/Rapidshare"


