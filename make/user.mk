.POSIX:

user/core.o: user/core.c include/string.h include/mpx/serial.h \
  include/mpx/device.h include/processes.h include/sys_req.h

USER_OBJECTS=\
	user/core.o\
	user/comhand.o\
	user/dateAndTime.o\
	user/ISRuser.o\
	user/pcbuser.o\
	user/alarm.o
	