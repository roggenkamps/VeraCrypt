# $FreeBSD$

PORTNAME=	veracrypt
PORTVERSION=	c0f46187dec76c4ff980a3267d716e7f05c92f33
PORTREVISION?=
CATEGORIES=	security
USE_GITHUB=     yes
GH_ACCOUNT=     veracrypt
GH_PROJECT=     VeraCrypt
GH_TAGNAME=     c0f46187dec76c4ff980a3267d716e7f05c92f33

MASTER_SITES=   GH:vc \
		SF/wxwindows/${WX_VER}/:wxwidgets

DISTFILES=	${GH_PROJECT}-${PORTVERSION}.tar.gz:vc \
		wxWidgets-${WX_VER}.tar.bz2:wxwidgets

MAINTAINER=	steveroggenkamps@gmail.com
COMMENT=	Free open-source disk encryption software based on Truecrypt

BUILD_DEPENDS=	nasm:devel/nasm
RUN_DEPENDS=	sudo:security/sudo # fusefs:sysutils/fusefs-libs

WRKSRC=		${WRKDIR}/${GH_PROJECT}-${PORTVERSION}/src

USES=		fuse iconv pkgconfig gmake

WX_VER=		3.0.2

LICENSE_FILE=	${WRKSRC}/License.txt

PLIST_FILES=	bin/veracrypt

OPTIONS_DEFINE=	X11 DOCS
X11_DESC=	With GUI (depends on X)

.include <bsd.port.options.mk>

GITHUB_MUST_SET_DISTNAME= no
DISTNAME= ${VC_PROJECT}_${PORTVERSION}

.if ${PORT_OPTIONS:MDOCS}
PLIST_FILES+=	%%DOCSDIR%%/VeraCrypt\ User\ Guide.pdf
PLIST_FILES+=	%%DOCSDIR%%/License.txt
.endif

.if ${PORT_OPTIONS:MX11}
USE_GNOME=	gtk20
NOGUI=
.else
NOGUI=		NOGUI=1
.endif

do-build:
	@${ECHO_MSG} "===>  Building for wxWidgets dependency"
	@(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${NOGUI} WX_ROOT=${WRKDIR}/wxWidgets-${WX_VER} wxbuild)
	@${ECHO_MSG} "===>  Building for ${PKGNAME}"
	(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${NOGUI} WXSTATIC=1)

do-install:
	@${INSTALL_PROGRAM} ${WRKSRC}/Main/veracrypt ${STAGEDIR}${PREFIX}/bin
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${INSTALL_DATA} ${WRKSRC}/License.txt ${STAGEDIR}${DOCSDIR}
	@${INSTALL_DATA} ${WRKSRC}/Release/Setup\ Files/VeraCrypt\ User\ Guide.pdf ${STAGEDIR}${DOCSDIR}
.endif

.include <bsd.port.mk>
