## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/memory_pe66.oe66 \

linker.cmd: package/cfg/memory_pe66.xdl
	$(SED) 's"^\"\(package/cfg/memory_pe66cfg.cmd\)\"$""\"E:/Code/CCS/workspace_v5_2/SharedMem/.config/xconfig_memory/\1\""' package/cfg/memory_pe66.xdl > $@
