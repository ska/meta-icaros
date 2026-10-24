SUMMARY = "A basic NAS image to share data"
DESCRIPTION = ""
LICENSE = "MIT"

inherit core-image
inherit nasusers

GLIBC_GENERATE_LOCALES = "en_US.UTF-8"
IMAGE_LINGUAS = "en-us"

set_hostname (){
     #!/bin/sh -e
     echo "NAS-${MACHINE}" > ${IMAGE_ROOTFS}/etc/hostname;
}

ROOTFS_POSTPROCESS_COMMAND += "set_hostname;"

IMAGE_FEATURES += " ssh-server-openssh nfs-server "

IMAGE_INSTALL += " kernel-modules "
IMAGE_INSTALL += " e2fsprogs \
                   e2fsprogs-e2fsck \
                   e2fsprogs-mke2fs \
                   e2fsprogs-resize2fs \
                   e2fsprogs-tune2fs"
IMAGE_INSTALL += " mdadm"
#IMAGE_INSTALL += " webmin"
IMAGE_INSTALL += " htop btop"
IMAGE_INSTALL += " util-linux"
IMAGE_INSTALL += " panelreply"
IMAGE_INSTALL += " sysstat"
IMAGE_INSTALL += " samba"
IMAGE_INSTALL += " nfs-utils" 
IMAGE_INSTALL += " openssh-sftp-server"
IMAGE_INSTALL += " procps"
IMAGE_INSTALL += " nvme-cli"
