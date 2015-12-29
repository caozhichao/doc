Test06: check
	@echo "-------- export scw c++  --------"
include ../Makefile.common

clean:
	rm -f *.swf *.swc *.bc *.exe *.as *.abc

swig:
	# -c++ 表示生成的包装类是c++形式的 格式 swig_wrap.cxx
	"$(FLASCC)/usr/bin/swig" -as3 -c++ -module FLCCLib -outdir . -includeall -ignoremissing swig.i
abc:
	#生成as3 代码
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) FLCCLib.as
swc:
	# g++方式编译
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) -O4 FLCCLib.abc swig_wrap.cxx main.cpp Heap.cpp -emit-swc=yz.flashcc -o flashcc7.swc

create:
	make clean
	make swig
	make abc
	make swc
