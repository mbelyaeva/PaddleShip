ACLOCAL_AMFLAGS= -I m4
noinst_HEADERS= SoundPlayer.h DebugDraw.hpp DynamicLineDrawer.hpp BulletContactCallback.h OgreMotionState.h BaseApplication.h Game.h GameObject.h Paddle.h Ship.h Alien.h Asteroid.h AsteroidSys.h Simulator.h GameScreen.h NetManager.h

bin_PROGRAMS= PaddleShip
PaddleShip_CPPFLAGS= -I$(top_srcdir)
<<<<<<< HEAD
PaddleShip_SOURCES= SoundPlayer.cpp DebugDraw.cpp DynamicLineDrawer.cpp BaseApplication.cpp Game.cpp GameObject.cpp Paddle.cpp Ship.cpp Alien.cpp Asteroid.cpp AsteroidSys.cpp Simulator.cpp GameScreen.cpp 
PaddleShip_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(CEGUI_CFLAGS)
PaddleShip_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)
PaddleShip_LDFLAGS= -lOgreOverlay -lboost_system -lSDL -lSDL_mixer
=======
PaddleShip_SOURCES= SoundPlayer.cpp DebugDraw.cpp DynamicLineDrawer.cpp BaseApplication.cpp Game.cpp GameObject.cpp Paddle.cpp Ship.cpp Alien.cpp Asteroid.cpp AsteroidSys.cpp Simulator.cpp GameScreen.cpp NetManager.cpp
PaddleShip_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS)
PaddleShip_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) -lSDL -lSDL_mixer -lSDL_net
PaddleShip_LDFLAGS= -lOgreOverlay -lboost_system
>>>>>>> 89eb356339a2b35641c99cb545b95d32c5658821

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
