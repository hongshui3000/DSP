# invoke SourceDir generated makefile for app.pe674
app.pe674: .libraries,app.pe674
.libraries,app.pe674: package/cfg/app_pe674.xdl
	$(MAKE) -f D:\sound\tronlong\dsp\demo\SYSBIOS\Application\DSP_v8/src/makefile.libs

clean::
	$(MAKE) -f D:\sound\tronlong\dsp\demo\SYSBIOS\Application\DSP_v8/src/makefile.libs clean

