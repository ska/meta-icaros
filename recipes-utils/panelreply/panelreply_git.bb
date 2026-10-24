SUMMARY = "PanelReply"
SECTION = "utils"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM ?= "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
PV = "1.0"
PR = "ic1"
SRC_URI = "git://github.com/ska/PanelReply.git;protocol=https;branch=master; \
           file://init"

SRCREV = "8671748334ed4c796163fa7e50bc5e020fd70bf3"

inherit update-rc.d
INITSCRIPT_NAME = "${BPN}.sh"
INITSCRIPT_PARAMS = "start 09 5 . stop 23 0 6 1 ."

do_compile () {
	oe_runmake all
}

do_install () {
    install -d ${D}/${bindir}/
    install -m 0755 ${S}/PanelReply ${D}/${bindir}/

    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${UNPACKDIR}/init ${D}/${sysconfdir}/init.d/${BPN}.sh
}

FILES:${PN} += "/etc/*"
INSANE_SKIP:${PN} += "ldflags"
