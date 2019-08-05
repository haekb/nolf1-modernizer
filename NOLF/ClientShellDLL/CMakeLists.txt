# File generated at : 20:28:37, Sat 03 Aug 
# Converted Project : ClientShellDLL/ClientShellDLL.vcxproj
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
    ./BaseFolder.cpp
    ./BaseLineSystemFX.cpp
    ./BaseMenu.cpp
    ./BaseParticleSystemFX.cpp
    ./BasePolyDrawFX.cpp
    ./BaseScaleFX.cpp
    ./BaseSelectionFolder.cpp
    ./BeamFX.cpp
    ./BitmapCtrl.cpp
    ./BodyFX.cpp
    ./BulletTrailFX.cpp
    ./CameraOffsetMgr.cpp
    ./CharacterFX.cpp
    ./ClientButeMgr.cpp
    ./ClientInfoMgr.cpp
    ./ClientSoundMgr.cpp
    ./ClientUtilities.cpp
    ./ClientWeaponUtils.cpp
    ./client_physics.cpp
    ./CMoveMgr.cpp
    ./Credits.cpp
    ./CycleCtrl.cpp
    ./DamageFXMgr.cpp
    ./DeathFX.cpp
    ./DebrisFX.cpp
    ./DynamicLightFX.cpp
    ./ExplosionFX.cpp
    ./FireFX.cpp
    ./FlashLight.cpp
    ./FolderAdvDisplay.cpp
    ./FolderAudio.cpp
    ./FolderAwards.cpp
    ./FolderBriefing.cpp
    ./FolderControls.cpp
    ./FolderCrosshair.cpp
    ./FolderCustomControls.cpp
    ./FolderCustomLevel.cpp
    ./FolderDifficulty.cpp
    ./FolderDisplay.cpp
    ./FolderEffects.cpp
    ./FolderEscape.cpp
    ./FolderFavoriteLevels.cpp
    ./FolderGadgets.cpp
    ./FolderGallery.cpp
    ./FolderGame.cpp
    ./FolderGear.cpp
    ./FolderHost.cpp
    ./FolderHostLevels.cpp
    ./FolderHostOptions.cpp
    ./FolderIntel.cpp
    ./FolderInventory.cpp
    ./FolderJoin.cpp
    ./FolderJoinLAN.cpp
    ./FolderJoystick.cpp
    ./FolderKeyboard.cpp
    ./FolderLoad.cpp
    ./FolderMain.cpp
    ./FolderMgr.cpp
    ./FolderMission.cpp
    ./FolderMods.cpp
    ./FolderMouse.cpp
    ./FolderMulti.cpp
    ./FolderMultiBriefing.cpp
    ./FolderMultiSummary.cpp
    ./FolderNew.cpp
    ./FolderObjectives.cpp
    ./FolderOptions.cpp
    ./FolderPerformance.cpp
    ./FolderPlayer.cpp
    ./FolderSave.cpp
    ./FolderSingle.cpp
    ./FolderStats.cpp
    ./FolderSummary.cpp
    ./FolderTexture.cpp
    ./FolderViewInventory.cpp
    ./FolderWeaponControls.cpp
    ./FolderWeapons.cpp
    ./GameClientShell.cpp
    ./GameSettings.cpp
    ./GibFX.cpp
    ./GlobalClientMgr.cpp
    ./GroupCtrl.cpp
    ./HeadBobMgr.cpp
    ./IntelItemMgr.cpp
    ./InterfaceMeter.cpp
    ./InterfaceMgr.cpp
    ./InterfaceResMgr.cpp
    ./InterfaceSurfMgr.cpp
    ./InterfaceTimer.cpp
    ./IpMgr.cpp
    ./JoystickAxis.cpp
    ./KeyFixes.cpp
    ./LaserBeam.cpp
    ./LaserTriggerFX.cpp
    ./LayoutMgr.cpp
    ./LeashFX.cpp
    ./LensFlareFX.cpp
    ./LightFX.cpp
    ./LightningFX.cpp
    ./LightScaleMgr.cpp
    ./LineSystemFX.cpp
    ./ListCtrl.cpp
    ./LoadingScreen.cpp
    ./LTDecisionWnd.cpp
    ./LTDialogueWnd.cpp
    ./LTMaskedWnd.cpp
    ./LTMenuWnd.cpp
    ./LTMultiWnd.cpp
    ./LTTextWnd.cpp
    ./LtWnd.cpp
    ./MarkSFX.cpp
    ./MessageBox.cpp
    ./MessageBoxCtrl.cpp
    ./MessageMgr.cpp
    ./MineFX.cpp
    ./MissionText.cpp
    ./MouseMgr.cpp
    ./MultiplayerMenu.cpp
    ./Music.cpp
    ./MuzzleFlashFX.cpp
    ./MuzzleFlashParticleFX.cpp
    ./NodeController.cpp
    ./NodeLinesFX.cpp
    ./ObjEditMgr.cpp
    ./ObjSpriteFX.cpp
    ./ParticleExplosionFX.cpp
    ./ParticleShowerFX.cpp
    ./ParticleSystemFX.cpp
    ./ParticleTrailFX.cpp
    ./ParticleTrailSegmentFX.cpp
    ./PickupItemFX.cpp
    ./PlayerCamera.cpp
    ./PlayerSoundFX.cpp
    ./PlayerStats.cpp
    ./PlayerVehicleFX.cpp
    ./PolyDebrisFX.cpp
    ./PolyGridFX.cpp
    ./PolyLineFX.cpp
    ./PopupText.cpp
    ./ProjectileFX.cpp
    ./PVFXMgr.cpp
    ./RandomSparksFX.cpp
    ./ScreenTintMgr.cpp
    ./SearchLightFX.cpp
    ./SFXMgr.cpp
    ./ShellCasingFX.cpp
    ./SliderCtrl.cpp
    ./SmokeFX.cpp
    ./SoundFX.cpp
    ./Sparam.cpp
    ./SpecialFXList.cpp
    ./sprinklesfx.cpp
    ./StaticTextCtrl.cpp
    ./SteamFX.cpp
    ./Subtitle.cpp
    ./TracerFX.cpp
    ./VehicleMgr.cpp
    ./VideoFX.cpp
    ./VKDefs.cpp
    ./WeaponChooser.cpp
    ./WeaponFX.cpp
    ./WeaponModel.cpp
    ./WeatherFX.cpp
    ./WinUtil.cpp
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
    BaseFolder.h
    BaseLineSystemFX.h
    BaseMenu.h
    BaseParticleSystemFX.h
    BasePolyDrawFX.h
    BaseScaleFX.h
    BaseSelectionFolder.h
    BeamFX.h
    BitmapCtrl.h
    BodyFX.h
    BulletTrailFX.h
    CameraFX.h
    CameraOffsetMgr.h
    CharacterFX.h
    ClientButeMgr.h
    ClientInfoMgr.h
    ClientSoundMgr.h
    ClientUtilities.h
    ClientWeaponUtils.h
    client_physics.h
    CMoveMgr.h
    Credits.h
    CycleCtrl.h
    DamageFXMgr.h
    DeathFX.h
    DebrisFX.h
    DynamicLightFX.h
    ExplosionFX.h
    FastList.h
    FireFX.h
    FlashLight.h
    FolderAdvDisplay.h
    FolderAudio.h
    FolderAwards.h
    FolderBriefing.h
    FolderCommands.h
    FolderControls.h
    FolderCrosshair.h
    FolderCustomControls.h
    FolderCustomLevel.h
    FolderDifficulty.h
    FolderDisplay.h
    FolderEffects.h
    FolderEscape.h
    FolderFavoriteLevels.h
    FolderGadgets.h
    FolderGallery.h
    FolderGame.h
    FolderGear.h
    FolderHost.h
    FolderHostLevels.h
    FolderHostOptions.h
    FolderIntel.h
    FolderInventory.h
    FolderJoin.h
    FolderJoinLAN.h
    FolderJoystick.h
    FolderKeyboard.h
    FolderLoad.h
    FolderMain.h
    FolderMgr.h
    FolderMission.h
    FolderMods.h
    FolderMouse.h
    FolderMulti.h
    FolderMultiBriefing.h
    FolderMultiSummary.h
    FolderNew.h
    FolderObjectives.h
    FolderOptions.h
    FolderPerformance.h
    FolderPlayer.h
    FolderSave.h
    FolderSingle.h
    FolderStats.h
    FolderSummary.h
    FolderSupplies.h
    FolderTexture.h
    FolderViewInventory.h
    FolderWeaponControls.h
    FolderWeapons.h
    GameButes.h
    GameClientShell.h
    GameSettings.h
    GibFX.h
    GroupCtrl.h
    HeadBobMgr.h
    IntelItemMgr.h
    InterfaceMeter.h
    InterfaceMgr.h
    InterfaceResMgr.h
    InterfaceSurfMgr.h
    InterfaceTimer.h
    IpMgr.h
    JoystickAxis.h
    KeyFixes.h
    LaserBeam.h
    LayoutMgr.h
    LeashFX.h
    LensFlareFX.h
    LightFX.h
    LightningFX.h
    LightScaleMgr.h
    LineSystemFX.h
    ListCtrl.h
    LoadingScreen.h
    LTDecisionWnd.h
    LTDialogueWnd.h
    LTMaskedWnd.h
    LTMenuWnd.h
    LTMultiWnd.h
    LTTextWnd.h
    LtWnd.h
    LTWndMessages.h
    MarkSFX.h
    MenuJoystickAxis.h
    MessageBox.h
    MessageBoxCtrl.h
    MessageMgr.h
    MineFX.h
    MissionText.h
    MouseMgr.h
    MultiplayerMenu.h
    Music.h
    MuzzleFlashFX.h
    MuzzleFlashParticleFX.h
    NetInfo.h
    NetStart.h
    NodeController.h
    NodeLinesFX.h
    ObjEditMgr.h
    Overlays.h
    ParticleExplosionFX.h
    ParticleShowerFX.h
    ParticleSystemFX.h
    ParticleTrailFX.h
    ParticleTrailSegmentFX.h
    PickupItemFX.h
    PlayerCamera.h
    PlayerData.h
    PlayerSoundFX.h
    PlayerStats.h
    PlayerVehicleFX.h
    PolyDebrisFX.h
    PolyGridFX.h
    PolyLineFX.h
    PopupText.h
    ProjectileFX.h
    PVFXMgr.h
    RandomSparksFX.h
    ScreenTintMgr.h
    SearchLightFX.h
    SFXMgr.h
    SharedDefs.h
    ShellCasingFX.h
    SliderCtrl.h
    SmokeFX.h
    SoundFX.h
    Sparam.h
    SpecialFX.h
    SpecialFXList.h
    sprinklesfx.h
    StaticTextCtrl.h
    SteamFX.h
    Subtitle.h
    TracerFX.h
    VarTrack.h
    VehicleMgr.h
    VideoFX.h
    VKDefs.h
    VolumeBrushFX.h
    WeaponChooser.h
    WeaponFX.h
    WeaponModel.h
    WeaponStringDefs.h
    WeatherFX.h
    WinUtil.h
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
   -D_CLIENTBUILD 
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
   -D_CLIENTBUILD 
   -D_WINDOWS 
   -D_NOLFBUILD 
   -DNO_PRAGMA_LIBS 
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
