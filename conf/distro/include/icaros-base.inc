require conf/distro/poky.conf

DISTRO = "icaros-base"
DISTRO_NAME = "IcarOS Distro Base"

ICAROS_BUILDNBR ?= "0"
ICAROS_PURPOSE ?= "Testing"

def get_icaros_prerelease(purpose, datetime):
    if purpose == "Testing":
        return '-devel-%s' % (datetime)
    elif purpose == "Nightly":
        return '-devel-%s' % (datetime[:8])
    elif purpose == "Monthly":
        return '-devel-%s' % (datetime[:6])
    elif purpose == "Release":
        return ''
    else:
        return '-devel-%s' % (datetime)

ICAROS_BUILD ?= "+build.${ICAROS_BUILDNBR}"
ICAROS_MATRIX_BUILD_TIME ?= "${DATETIME}"
ICAROS_MATRIX_BUILD_TIME[vardepsexclude] = "DATETIME"
ICAROS_PRERELEASE ?= "${@get_icaros_prerelease(d.getVar('ICAROS_PURPOSE'), d.getVar('ICAROS_MATRIX_BUILD_TIME'))}"
ICAROS_MAJOR ?= "1"
ICAROS_MINOR ?= "0"
ICAROS_PATCH ?= "0"
ICAROS_RELEASE ?= "${ICAROS_MAJOR}.${ICAROS_MINOR}.${ICAROS_PATCH}"

# IcarOS version number without date, for U-Boot/Kernel and other
# IcarOS specific software artifacts.
ICAROS_VERSION ?= "${ICAROS_RELEASE}${@'' if d.getVar('ICAROS_PURPOSE') == 'Release' else '-devel'}"

# Complete image version with date and build number
DISTRO_VERSION = "${ICAROS_RELEASE}${ICAROS_PRERELEASE}${ICAROS_BUILD}"

SDK_VENDOR = "-icarossdk"
SDK_NAME_PREFIX = "${DISTRO}"
# do not use elements in SDK_VERSION which are in vardepsexclude
SDK_VERSION = "${ICAROS_RELEASE}"

MAINTAINER = "ska@linux.it"

TARGET_VENDOR = "-icaros"

DISTROOVERRIDES .= ":icaros-distro"

# create etc/build in the rootfs
INHERIT += "image-buildinfo"

# Log information on images and packages
INHERIT += "buildhistory"
BUILDHISTORY_COMMIT = "1"

IMAGE_LINGUAS ?= "en-us"

ERROR_QA:remove = "version-going-backwards"

DISTRO_FEATURES:append = " pam usrmerge tpm2"
DISTRO_FEATURES:remove = "ptest"

# Selects systemd and drops sysvinit from DISTRO_FEATURES
# (see conf/distro/include/init-manager-systemd.inc)
INIT_MANAGER = "systemd"
