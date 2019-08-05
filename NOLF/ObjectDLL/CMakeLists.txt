# File generated at : 20:28:37, Sat 03 Aug 
# Converted Project : ObjectDLL/Object.vcxproj
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

##################### Variables ############################
# Change if you want modify path or other values           #
############################################################

# Project
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(DEPENDENCIES_DIR ${PROJECT_DIR}/dependencies)
set(PROJECT_NAME <PLEASE SET YOUR PROJECT NAME !!>)


# Outputs
set(OUTPUT_DEBUG ./Debug/)
set(OUTPUT_RELEASE ./Final_Release/)

################# CMake Project ############################
# The main options of project                              #
############################################################

project(${PROJECT_NAME} CXX)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

############## Artefacts Output ############################
# Defines outputs , depending BUILD TYPE                   #
############################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
endif()

# Messages
message("${PROJECT_NAME}: MAIN PROJECT: ${CMAKE_PROJECT_NAME}")
message("${PROJECT_NAME}: CURR PROJECT: ${CMAKE_CURRENT_SOURCE_DIR}")
message("${PROJECT_NAME}: CURR BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")

############### Files & Targets ############################
# Files of project and target to build                     #
############################################################

# Source Files
set(SRC_FILES
    ./AI.cpp
    ./AIAnimal.cpp
    ./AIAnimalState.cpp
    ./AIAnimalStrategy.cpp
    ./AIBrain.cpp
    ./AIButeMgr.cpp
    ./AIDog.cpp
    ./AIDogReactions.cpp
    ./AIGroup.cpp
    ./AIHelicopter.cpp
    ./AIHuman.cpp
    ./AIHumanReactions.cpp
    ./AIHumans.cpp
    ./AIHumanState.cpp
    ./AIHumanStrategy.cpp
    ./AIMovement.cpp
    ./AINode.cpp
    ./AINodeMgr.cpp
    ./AINudge.cpp
    ./AIPath.cpp
    ./AIPathMgr.cpp
    ./AIPoodle.cpp
    ./AIReactions.cpp
    ./AIRegion.cpp
    ./AIRegionMgr.cpp
    ./AISense.cpp
    ./AIShark.cpp
    ./AISounds.cpp
    ./AIState.cpp
    ./AISteering.cpp
    ./AITarget.cpp
    ./AIUtils.cpp
    ./AIVehicle.cpp
    ./AIVehicleState.cpp
    ./AIVehicleStrategy.cpp
    ./AIVolume.cpp
    ./AIVolumeMgr.cpp
    ./Alarm.cpp
    ./AmmoBox.cpp
    ./AnimationLex.cpp
    ./AnimationMgr.cpp
    ./AnimationMgrHuman.cpp
    ./AnimationParse.cpp
    ./AnimationParser.cpp
    ./AnimatorAIAnimal.cpp
    ./AnimatorAIVehicle.cpp
    ./AnimatorPlayer.cpp
    ./Attachments.cpp
    ./Body.cpp
    ./BodyState.cpp
    ./Breakable.cpp
    ./CachedFiles.cpp
    ./Camera.cpp
    ./Character.cpp
    ./CharacterHitBox.cpp
    ./CharacterMgr.cpp
    ./CinematicTrigger.cpp
    ./ClientLightFX.cpp
    ./ClientSFX.cpp
    ./ClientWeaponSFX.cpp
    ./CommandMgr.cpp
    ./Controller.cpp
    ./DebrisFuncs.cpp
    ./Destructible.cpp
    ./DestructibleModel.cpp
    ./DialogueWindow.cpp
    ./DisplayMeter.cpp
    ./DisplayTimer.cpp
    ./Door.cpp
    ./DoorKnob.cpp
    ./Editable.cpp
    ./EventCounter.cpp
    ./ExitTrigger.cpp
    ./Explosion.cpp
    ./Fire.cpp
    ./GameBase.cpp
    ./GameServerShell.cpp
    ./GameStartPoint.cpp
    ./GearItems.cpp
    ./GlobalServerMgr.cpp
    ./Group.cpp
    ./HHWeaponModel.cpp
    ./HingedDoor.cpp
    ./Intelligence.cpp
    ./IntelMgr.cpp
    ./Key.cpp
    ./KeyData.cpp
    ./KeyFramer.cpp
    ./keyframer_light.cpp
    ./KeyPad.cpp
    ./LaserTrigger.cpp
    ./Lightning.cpp
    ./Lock.cpp
    ./Mine.cpp
    ./ModItem.cpp
    ./MusicMgr.cpp
    ./MyGameSpyMgr.cpp
    ./NodeLine.cpp
    ./ObjectiveSprite.cpp
    ./ObjectRemover.cpp
    ./object_list.cpp
    ./ParticleSystem.cpp
    ./PickupItem.cpp
    ./PlayerObj.cpp
    ./PlayerVehicle.cpp
    ./PolyGrid.cpp
    ./Projectile.cpp
    ./ProjectileTypes.cpp
    ./Prop.cpp
    ./PropType.cpp
    ./PropTypeMgr.cpp
    ./RandomSpawner.cpp
    ./RotatingDoor.cpp
    ./RotatingWorldModel.cpp
    ./ScaleSprite.cpp
    ./Scanner.cpp
    ./ScreenShake.cpp
    ./SearchLight.cpp
    ./SecurityCamera.cpp
    ./ServerButeMgr.cpp
    ./ServerMark.cpp
    ./ServerSoundMgr.cpp
    ./ServerUtilities.cpp
    ./SFXFuncs.cpp
    ./SoundFX.cpp
    ./Sparam.cpp
    ./Spawner.cpp
    ./Speaker.cpp
    ./Sprinkles.cpp
    ./Steam.cpp
    ./Switch.cpp
    ./TeleportPoint.cpp
    ./TranslucentWorldModel.cpp
    ./Trigger.cpp
    ./Video.cpp
    ./VolumeBrush.cpp
    ./VolumeBrushTypes.cpp
    ./Weapon.cpp
    ./WeaponItems.cpp
    ./Weapons.cpp
    ./WorldModelDebris.cpp
    ./WorldProperties.cpp
    ./ZipHook.cpp
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
    AI.h
    AIAnimal.h
    AIAnimalState.h
    AIAnimalStrategy.h
    AIBrain.h
    AIButeMgr.h
    AIDog.h
    AIDogReactions.h
    AIGroup.h
    AIHelicopter.h
    AIHuman.h
    AIHumanReactions.h
    AIHumans.h
    AIHumanState.h
    AIHumanStrategy.h
    AIMovement.h
    AINode.h
    AINodeMgr.h
    AINudge.h
    AIPath.h
    AIPathMgr.h
    AIPoodle.h
    AIReactions.h
    AIRegion.h
    AIRegionMgr.h
    AISense.h
    AIShark.h
    AISounds.h
    AIState.h
    AISteering.h
    AITarget.h
    AIUtils.h
    AIVehicle.h
    AIVehicleState.h
    AIVehicleStrategy.h
    AIVolume.h
    AIVolumeMgr.h
    Alarm.h
    AmmoBox.h
    AnimationLex.h
    AnimationLexSymbols.h
    AnimationMgr.h
    AnimationMgrHuman.h
    AnimationParse.h
    AnimationParser.h
    AnimationStd.h
    AnimatorAIAnimal.h
    AnimatorAIVehicle.h
    AnimatorPlayer.h
    Attachments.h
    Body.h
    BodyState.h
    Bouncer.h
    Breakable.h
    CachedFiles.h
    Camera.h
    CDynArray.h
    Character.h
    CharacterHitBox.h
    CharacterMgr.h
    CinematicTrigger.h
    ClientDeathSFX.h
    ClientFX.h
    ClientLightFX.h
    ClientSFX.h
    ClientWeaponSFX.h
    CommandMgr.h
    Controller.h
    CVarTrack.h
    DeathScene.h
    DebrisFuncs.h
    Destructible.h
    DestructibleModel.h
    DialogueWindow.h
    DisplayMeter.h
    DisplayTimer.h
    Door.h
    DoorKnob.h
    Editable.h
    EventCounter.h
    ExitTrigger.h
    Explosion.h
    Fire.h
    Fixture.h
    GameBase.h
    GameServerShell.h
    GameStartPoint.h
    GearItems.h
    Group.h
    HHWeaponModel.h
    HingedDoor.h
    Intelligence.h
    Joint.h
    Key.h
    KeyData.h
    KeyFramer.h
    keyframer_light.h
    KeyPad.h
    LaserTrigger.h
    Lightning.h
    Lock.h
    Mine.h
    ModItem.h
    MusicMgr.h
    NodeLine.h
    ObjectiveSprite.h
    ObjectMsgs.h
    ObjectRemover.h
    ParticleSystem.h
    PickupItem.h
    PlayerButes.h
    PlayerObj.h
    PlayerVehicle.h
    PolyGrid.h
    Projectile.h
    ProjectileTypes.h
    Prop.h
    PropType.h
    PropTypeMgr.h
    RandomSpawner.h
    RotatingDoor.h
    RotatingWorldModel.h
    ScaleSprite.h
    Scanner.h
    ScreenShake.h
    SearchLight.h
    SecurityCamera.h
    ServerButeMgr.h
    ServerMark.h
    ServerSoundMgr.h
    ServerUtilities.h
    SFXFuncs.h
    SoundFX.h
    Sparam.h
    Spawner.h
    Speaker.h
    Sprinkles.h
    Steam.h
    Switch.h
    TeleportPoint.h
    TranslucentWorldModel.h
    Trigger.h
    TriggerSound.h
    Video.h
    VolumeBrush.h
    VolumeBrushTypes.h
    Weapon.h
    WeaponItems.h
    Weapons.h
    WorldModelDebris.h
    WorldProperties.h
    ZipHook.h
)
source_group("Headers" FILES ${HEADERS_FILES})

# Add executable to build.
add_executable(${PROJECT_NAME} 
   ${SRC_FILES} ${HEADERS_FILES}
)

######################### Flags ############################
# Defines Flags for Windows and Linux                      #
############################################################

if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

# Preprocessor definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -D_DEBUG 
   -D_WINDOWS 
   -DNO_PRAGMA_LIBS 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /Od /Zi /EHsc)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -DNDEBUG 
   -D_WINDOWS 
   -D_NOLFBUILD 
   -DNO_PRAGMA_LIBS 
   -DUSE_INTEL_COMPILER 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /Gy /EHsc)
    endif()
endif()

########### Link & Dependencies ############################
# Add project dependencies and Link to project             #
############################################################

if(MSVC)
   target_link_libraries(${PROJECT_NAME} odbc32.lib odbccp32.lib )
endif(MSVC)
