TARGET = qfb
#TEMPLATE = lib

SOURCES = facebook-api.c \
    facebook-http.c \
    facebook-json.c \
    facebook-mqtt.c \
    facebook-thrift.c \
    facebook-util.c \
    main.cpp \
    bitlbee/lib/base64.c \
    bitlbee/lib/events_glib.c \
    bitlbee/lib/http_client.c \
    bitlbee/lib/json.c \
    bitlbee/lib/json_util.c \
    bitlbee/lib/md5.c \
    bitlbee/lib/misc.c \
    bitlbee/lib/proxy.c \
    bitlbee/lib/sha1.c \
    bitlbee/lib/ssl_openssl.c \
    bitlbee/lib/url.c

HEADERS = facebook-api.h \
    facebook-http.h \
    facebook-id.h \
    facebook-json.h \
    facebook-mqtt.h \
    facebook-thrift.h \
    facebook-util.h \
    bitlbee/sock.h \
    bitlbee/lib/base64.h \
    bitlbee/lib/events.h \
    bitlbee/lib/http_client.h \
    bitlbee/lib/json.h \
    bitlbee/lib/json_util.h \
    bitlbee/lib/md5.h \
    bitlbee/lib/misc.h \
    bitlbee/lib/proxy.h \
    bitlbee/lib/sha1.h \
    bitlbee/lib/ssl_client.h \
    bitlbee/lib/url.h

INCLUDEPATH += bitlbee \
    bitlbee/lib

DEFINES += ARCH=\\\"x86_64\\\" \
    CPU=\\\"Whatever\\\" \
    CONFIG=\\\"/etc/bitlbee/\\\" \
    PLUGINDIR=\\\"Whatever\\\" \
    PIDFILE=\\\"Whatever\\\" \
    ETCDIR=\\\"/etc/bitlbee/\\\" \
    IPCSOCKET=\\\"Whatever\\\" \
    VARDIR=\\\"/etc/bitlbee/\\\" \
    BITLBEE_VERSION=\\\"Nope\\\" \
    PACKAGE=\\\"Nope\\\" \
    PACKAGE_VERSION=\\\"Nope\\\"

CONFIG += c++11 link_pkgconfig

PKGCONFIG += glib-2.0 zlib openssl
