LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := ./hellocpp/AppDelegate.cpp \
                   ./hellocpp/AppDelegate.h \
./hellocpp/GameAboutScene.cpp \
./hellocpp/GameAboutScene.h \
./hellocpp/GameEnemyBullet.cpp \
./hellocpp/GameEnemyBullet.h \
./hellocpp/GameHeroBullet.cpp \
./hellocpp/GameHeroBullet.h \
./hellocpp/GameMark.cpp \
./hellocpp/GameMark.h \
./hellocpp/GameMenuScene.cpp \
./hellocpp/GameMenuScene.h \
./hellocpp/GameObjEnemy.cpp \
./hellocpp/GameObjEnemy.h \
./hellocpp/GameObjHero.cpp \
./hellocpp/GameObjHero.h \
./hellocpp/GameScene.cpp \
./hellocpp/GameScene.h \
./hellocpp/HelloWorldScene.cpp \
./hellocpp/HelloWorldScene.h \
./hellocpp/main.cpp \
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
