ACLOCAL_AMFLAGS= -I m4
noinst_HEADERS= BulletContactCallback.h BaseApplication.h Game.h GameObject.h Ship.h Asteroid.h GameScreen.h

bin_PROGRAMS= PaddleShip
PaddleShip_CPPFLAGS= -I$(top_srcdir)
PaddleShip_SOURCES= BaseApplication.cpp Game.cpp GameObject.cpp Ship.cpp Asteroid.cpp GameScreen.cpp
PaddleShip_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
PaddleShip_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
PaddleShip_LDFLAGS= -lOgreOverlay -lboost_system

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
