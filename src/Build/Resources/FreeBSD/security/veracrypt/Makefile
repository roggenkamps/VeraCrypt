# $FreeBSD$

PORTNAME=	veracrypt
PORTVERSION=	b15cb5794d5cac56d50e2caa8fcf619651cded1f
PORTREVISION?=
CATEGORIES=	security

MAINTAINER=	steveroggenkamps@gmail.com
COMMENT=	Free open-source disk encryption software based on Truecrypt

LICENSE_FILE=	${WRKSRC}/License.txt

USE_GITHUB=	yes
GH_ACCOUNT=	veracrypt
GH_PROJECT=	VeraCrypt
GH_TAGNAME=	b15cb5794d5cac56d50e2caa8fcf619651cded1f

MASTER_SITES=	GH:vc \
		SF/wxwindows/${WX_VER}/:wxwidgets
DISTFILES=	${GH_PROJECT}-${PORTVERSION}.tar.gz:vc \
		wxWidgets-${WX_VER}.tar.bz2:wxwidgets

USES=		desktop-file-utils fuse gmake iconv pkgconfig

WRKSRC=		${WRKDIR}/${GH_PROJECT}-${PORTVERSION}/src

WX_VER=		3.0.2

PLIST_FILES=	bin/veracrypt

OPTIONS_DEFINE=	X11 DOCS
X11_DESC=	With GUI (depends on X)

.include <bsd.port.options.mk>

GITHUB_MUST_SET_DISTNAME=	no
DISTNAME=	${VC_PROJECT}_${PORTVERSION}

.if ${PORT_OPTIONS:MDOCS}
PLIST_FILES+=	%%DOCSDIR%%/VeraCrypt\ User\ Guide.pdf
PLIST_FILES+=	%%DOCSDIR%%/License.txt
.endif

.if ${PORT_OPTIONS:MX11}
USE_GNOME=	gtk30
NOGUI=
PLIST_FILES+=	%%PREFIX%%/share/applications/veracrypt.desktop
.else
NOGUI=		NOGUI=1
.endif

post-patch:
	@${SED} -e 's|%%PREFIX%%|${PREFIX}|' \
		< ${FILESDIR}/veracrypt.desktop \
		> ${WRKSRC}/veracrypt.desktop

do-build:
	@${ECHO_MSG} "===>  Building for wxWidgets dependency"
	@(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${NOGUI} WX_ROOT=${WRKDIR}/wxWidgets-${WX_VER} wxbuild)
	@${ECHO_MSG} "===>  Building for ${PKGNAME}"
	(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${NOGUI} WXSTATIC=1)

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/Main/veracrypt ${STAGEDIR}${PREFIX}/bin
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${INSTALL_DATA} ${WRKSRC}/License.txt ${STAGEDIR}${DOCSDIR}
	@${INSTALL_DATA} ${WRKSRC}/Release/Setup\ Files/VeraCrypt\ User\ Guide.pdf ${STAGEDIR}${DOCSDIR}
.endif

post-install:
.if ${PORT_OPTIONS:MX11}
	@${INSTALL_DATA} ${WRKSRC}/vercrypt.desktop \
		${STAGEDIR}${PREFIX}/share/applications
.endif

.include <bsd.port.mk>
