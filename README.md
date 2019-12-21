# mount_nullfs

Apple's XNU kernel includes sources for the nullfs filesystem. On other OSs this might be referred to as a bind or loopback filesystem. The source for said filesystem is available [here](https://github.com/apple/darwin-xnu/tree/master/bsd/miscfs/nullfs) in Apple's public kernel sources.

Unfortunately this filesystem is hidden from users both through the lack of an available `mount_nullfs` binary as well as behind the `com.apple.private.nullfs_allow` entitlement on modern versions of macOS. This means that in normal development scenarios nullfs cannot be used by any program that isn't signed with an Apple codesigning certificate.

This program allows users to create nullfs mounts.

## WARNING

**The use of this program requires disabling both `SIP` and `AMFI`. This cripples many of the modern security measures built into macOS.**

`SIP` and `AMFI` can be disabled by rebooting into recovery mode by holding `CMD-R` on reboot and running the following commands:
```bash
sudo csrutil disable
sudo nvram boot-args=“amfi_get_out_of_my_way=0x1”
```

If disabling `SIP` and `AMFI` sounds bad to you (and it should) then you should probably be using either [bindfs](https://github.com/mpartel/bindfs) or [unionfs-fuse](https://github.com/rpodgorny/unionfs-fuse). Both are FUSE based filesystems that emulate loopback and unionfs (which is a loopback when only one branch is specified) filesystems respectively that run perfectly fine on modern macOS.

A formula for bindfs is available in standard homebrew repositories. A formula for unionfs-fuse is available to tap [here](https://github.com/JamaicanMoose/homebrew-moosetap).

## Usage
```bash
mount_nullfs [-o options] target_fs mount_point
```

##### NOTE : For some reason mounting nullfs creates the mountpoint at `mount_point` but puts the target in `mount_point/d/target`. No idea why this happens 🤷‍♂.
