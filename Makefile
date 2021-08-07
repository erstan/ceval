#default message
default: msg_before
msg_before:
	@echo "Run 'sudo make install' to put the library on PATH"

#installation
install: cp_to_path msg_end
cp_to_path:
	@mkdir -p /usr/local/include/ceval
	@touch /usr/local/include/ceval/ceval.h
	@cp -f ceval.h /usr/local/include/ceval/ceval.h
	@cp -fr core /usr/local/include/ceval
msg_end:
	@echo "Use #include<ceval/ceval.h> directive to include the header file in your project"

#uninstallation
uninstall:
	@rm /usr/local/include/ceval -fr
