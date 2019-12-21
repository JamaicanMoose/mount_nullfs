CFLAGS += -Wall

LDFLAGS += -dead_strip

all: mount_nullfs sign

mount_nullfs: mount_nullfs.c getmntopts.c
	$(CC) -O2 -o mount_nullfs mount_nullfs.c getmntopts.c
	strip mount_nullfs

sign:
	/usr/bin/codesign -fs 'nullfs-cert' --entitlements entitlements.plist ./mount_nullfs

clean:
	rm -f *.o mount_nullfs
