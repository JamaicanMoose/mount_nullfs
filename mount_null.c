#include <sys/param.h>
#include <sys/mount.h>

#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "mntopts.h"

struct mntopt mopts[] = {
    MOPT_STDOPTS,
    { NULL }
};

#define NULLFS_MOUNT_TYPE   "nullfs"

void    usage __P((void));

int main(int argc, char **argv) {
    struct nullfs_args { char *target } args;
    int ch, mntflags;
    char target[MAXPATHLEN], canon_dir[MAXPATHLEN];

    mntflags = 0;
    while ((ch = getopt(argc, argv, "o:")) != EOF)
        switch(ch) {
        case 'o':
            getmntopts(optarg, mopts, &mntflags, 0);
            break;
        case '?':
        default:
            usage();
        }
    argc -= optind;
    argv += optind;

    if (argc != 2)
        usage();

    if (realpath(argv[0], target) == NULL)
        err(1, "realpath %s", argv[0]);
    if (strncmp(argv[0], target, MAXPATHLEN)) {
        warnx("\"%s\" is a relative path.", argv[0]);
        warnx("using \"%s\" instead.", target);
    }

    if (realpath(argv[1], canon_dir) == NULL)
        err(1, "realpath %s", argv[1]);
    if (strncmp(argv[1], canon_dir, MAXPATHLEN)) {
        warnx("\"%s\" is a relative path.", argv[1]);
        warnx("using \"%s\" instead.", canon_dir);
    }

    if (strcmp(target, canon_dir) == 0)
        errx(1, "%s (%s) and %s (%s) are identical paths",
            argv[0], target, argv[1], canon_dir);

    if (mount("nullfs", canon_dir, mntflags, (void*)target) == -1)
        err(1, "%s on %s", target, canon_dir);
    exit(0);
}

void usage() {
    (void)fprintf(stderr,
        "usage: mount_null [-o options] target mount_point\n");
    exit(1);
}
