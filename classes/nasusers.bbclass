inherit extrausers

# Password hash for the "ska" admin user. Do not keep the real hash in the
# layer: set it in local.conf, e.g. generated with
#   openssl passwd -6 'mypassword'
# and escape every '$' as '\$'.
# Without it the account is created locked (no password login).
ICAROS_ADMIN_HASH ??= "!"

python () {
    if d.getVar('ICAROS_ADMIN_HASH') == "!":
        bb.warn("%s: ICAROS_ADMIN_HASH is not set, the ska account is locked. Set it in local.conf" % d.getVar('PN'))
}

EXTRA_USERS_PARAMS += "useradd -u 10000 -p '${ICAROS_ADMIN_HASH}' ska;"
EXTRA_USERS_PARAMS += "groupadd -g 20001 fileshare;"
EXTRA_USERS_PARAMS += "usermod -a -G fileshare ska;"
