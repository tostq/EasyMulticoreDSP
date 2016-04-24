## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/hello_pe66.oe66 \

linker.cmd: package/cfg/hello_pe66.xdl
	$(SED) 's"^\"\(package/cfg/hello_pe66cfg.cmd\)\"$""\"E:/Code/CCS/workspace_v5_2/helloworldBios/Debug/configPkg/\1\""' package/cfg/hello_pe66.xdl > $@
