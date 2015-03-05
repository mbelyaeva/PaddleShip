ACLOCAL_AMFLAGS= -I m4
noinst_HEADERS= DebugDraw.hpp DynamicLineDrawer.hpp BulletContactCallback.h OgreMotionState.h BaseApplication.h Game.h GameObject.h Paddle.h Ship.h Asteroid.h AsteroidSys.h Simulator.h GameScreen.h

bin_PROGRAMS= PaddleShip
PaddleShip_CPPFLAGS= -I$(top_srcdir)
PaddleShip_SOURCES= DebugDraw.cpp DynamicLineDrawer.cpp BaseApplication.cpp Game.cpp GameObject.cpp Paddle.cpp Ship.cpp Asteroid.cpp AsteroidSys.cpp Simulator.cpp GameScreen.cpp 
PaddleShip_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
PaddleShip_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
PaddleShip_LDFLAGS= -lOgreOverlay -lboost_system

OgreApp_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(CEGUI_CFLAGS)
OgreApp_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
