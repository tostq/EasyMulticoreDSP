## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/SharedMemory_pe66.oe66 \

linker.cmd: package/cfg/SharedMemory_pe66.xdl
	$(SED) 's"^\"\(package/cfg/SharedMemory_pe66cfg.cmd\)\"$""\"E:/Code/CCS/workspace_v5_2/SharedMem/Debug/configPkg/\1\""' package/cfg/SharedMemory_pe66.xdl > $@
