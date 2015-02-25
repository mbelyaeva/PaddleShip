ACLOCAL_AMFLAGS= -I m4
noinst_HEADERS= Asteroid.h BaseApplication.h Game.h GameScreen.h BulletContactCallback.h GameObject.h Ship.h

bin_PROGRAMS= PaddleShip
PaddleShip_CPPFLAGS= -I$(top_srcdir)
PaddleShip_SOURCES= Asteroid.cpp BaseApplication.cpp Game.cpp GameScreen.cpp GameObject.cpp Ship.cpp
PaddleShip_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
PaddleShip_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
PaddleShip_LDFLAGS= -lOgreOverlay -lboost_system

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
