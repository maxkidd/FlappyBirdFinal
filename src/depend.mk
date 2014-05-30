BackgroundComponent.o: BackgroundComponent.cpp \
 Components\BackgroundComponent.h Components\IComponent.h \
 Components\../Types.h
BackgroundManager.o: BackgroundManager.cpp Logic/BackgroundManager.h \
 Logic/IEntitySystem.h Logic/../Components/BackgroundComponent.h \
 Logic/../Components/IComponent.h Logic/../Components/../Types.h \
 Logic/../Components/PlayerComponent.h Systems/EntityManager.h \
 Systems/../Types.h Systems/ServiceLocator.h Systems/EntityManager.h \
 gba.h
CollisionSystem.o: CollisionSystem.cpp Logic/CollisionSystem.h \
 Logic/IEntitySystem.h Logic/../Components/PlayerComponent.h \
 Logic/../Components/IComponent.h Logic/../Components/../Types.h \
 Logic/../Components/RenderComponent.h \
 Logic/../Components/BackgroundComponent.h Systems/EntityManager.h \
 Systems/../Types.h Systems/ServiceLocator.h Systems/EntityManager.h \
 gba.h
EntityManager.o: EntityManager.cpp Systems/EntityManager.h \
 Systems/../Types.h Components/IComponent.h Components/../Types.h
GraphicsManager.o: GraphicsManager.cpp Systems/GraphicsManager.h \
 Systems/../gba.h Systems/../Types.h Systems/EntityManager.h \
 Systems/../Components/IComponent.h Systems/../Components/../Types.h \
 Components/RenderComponent.h Components/IComponent.h \
 Components/BackgroundComponent.h gba.h
PlayerComponent.o: PlayerComponent.cpp Components\PlayerComponent.h \
 Components\IComponent.h Components\../Types.h
PlayerDriver.o: PlayerDriver.cpp Logic/PlayerDriver.h \
 Logic/IEntitySystem.h Logic/../Components/PlayerComponent.h \
 Logic/../Components/IComponent.h Logic/../Components/../Types.h \
 Systems/EntityManager.h Systems/../Types.h Systems/ServiceLocator.h \
 Systems/EntityManager.h gba.h
RenderComponent.o: RenderComponent.cpp Components/RenderComponent.h \
 Components/IComponent.h Components/../Types.h
ServiceLocator.o: ServiceLocator.cpp Systems/ServiceLocator.h \
 Systems/EntityManager.h Systems/../Types.h Types.h
UpdateSystems.o: UpdateSystems.cpp Logic/UpdateSystems.h \
 Logic/IEntitySystem.h Logic/../Components/PlayerComponent.h \
 Logic/../Components/IComponent.h Logic/../Components/../Types.h \
 Logic/../Components/RenderComponent.h Systems/EntityManager.h \
 Systems/../Types.h Systems/ServiceLocator.h Systems/EntityManager.h \
 gba.h
gba.o: gba.cpp gba.h
main.o: main.cpp Types.h Components/RenderComponent.h \
 Components/IComponent.h Components/../Types.h \
 Components/PhysicsComponent.h Components/BackgroundComponent.h \
 Systems/ServiceLocator.h Systems/EntityManager.h Systems/../Types.h \
 Systems/EntityManager.h Systems/GraphicsManager.h Systems/../gba.h \
 Systems/../Components/IComponent.h Logic/PlayerDriver.h \
 Logic/IEntitySystem.h Logic/../Components/PlayerComponent.h \
 Logic/../Components/IComponent.h Logic/UpdateSystems.h \
 Logic/../Components/RenderComponent.h Logic/BackgroundManager.h \
 Logic/../Components/BackgroundComponent.h Logic/CollisionSystem.h \
 Res/pipe_end_top.h Res/pipe_end_bot.h Res/pipe_main.h Res/bird.h \
 Res/palette.h Res/background.h Res/ground.h Res/sky.h Res/numbers.h
