#include <pthread.h>
#include <jni.h>
#include <Includes/Utils.h>
#include <Substrate/SubstrateHook.h>
#include "KittyMemory/MemoryPatch.h"
#include "MonoString.h"
#include <cstring>
#include <thread>
#include <chrono>
#include <string>
#include <android/log.h>

#define LOG_TAG "MyLib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#include "Quaternion.h"

extern "C" {

const char *libName = "libtroll.so";

bool fl = false;

typedef void (*AddChatMessageFunc)(char*);
    AddChatMessageFunc old_AddChatMessage;

    void AddChatMessage(char* text) {
        if (!text)
            return;
        old_AddChatMessage(text);
    }

// ---- KEY system strings ----

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_Menu_name(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("TROLL");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_Menu_close(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("× Закрыть");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_Menu_name1(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("t.me/apexxsoft");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name2(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Авторизация");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name3(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Введите ключ");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name4(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("ВОЙТИ");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name5(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("ПОЛУЧИТЬ КЛЮЧ");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name6(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Ключ верен!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name7(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Чит запускается, подождите!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name8(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Неверный ключ!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_name9(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Неверный ключ!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_KEY_key7(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Troll777");
}

// ---- Features ----

JNIEXPORT jobjectArray JNICALL Java_il2cpp_Main_getFeatures(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;
    // switch_featureid_text
    const char *features[] = {
        "page_Персонаж_player.png",
        "page_Транспорт_car.png",
        "page_Визуалы_visual.png",
        "page_Другое_misc.png",

        "BLOCK_0_0,1",
        "BLOCK_1_2,3",
        "BLOCK_2_4,5",
        "BLOCK_3_6,7",

        "h1_0_1_Флудер",
        "h1_0_11_jump x3",

        "h1_1_111_flood",
        "h1_1_1111_jump x5",

        "h2_0_11111_super jump",
        "slider_0_111_long jump_255_0",
    };
    int Total_Feature = (sizeof features /
                         sizeof features[0]);

    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}

JNIEXPORT void JNICALL
Java_il2cpp_Main_Changes(JNIEnv *env, jobject activityObject, jint feature, jint value) {
    switch (feature) {

        case 1:
            fl = !fl;
            if (fl) {
                AddChatMessage("{F12763}Apex |{ffffff} Введите команду:");
                AddChatMessage("{F12763}Apex |{ffffff} /flood <сообщение флуда>");
            }
            break;
    }
}

void(*old_ChatWindowInputHandler)(char *text);
void (*SendChatMessage)(char *text);

bool floodActive = false;
std::string floodMessage = "";

void floodFunction() {
    while (floodActive) {
        char* text = new char[floodMessage.length() + 1];
        strcpy(text, floodMessage.c_str());
        SendChatMessage(text);
        delete[] text;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ChatWindowInputHandler(char *text) {
    if (strncmp(text, "/flood ", 7) == 0) {
        AddChatMessage("{F12763}Apex |{ffffff} Чтобы остановить введите повторно команду");
        floodMessage = std::string(text + 7);
        LOGD("Сообщение для флуда: %s", floodMessage.c_str());

        floodActive = !floodActive;

        if (floodActive) {
            std::thread floodThread(floodFunction);
            floodThread.detach();
        }
        return;
    }

    old_ChatWindowInputHandler(text);
}

// EXTERN END
}

void *cheat(void *) {
    // libtroll.so — 64-bit ARM (aarch64), no +1 Thumb offset needed
    // Offsets found from libblackrussia-client.so (renamed to libtroll.so in game):
    //   ChatWindowInputHandler : 0x5850C4 (chat command input processor)
    //   AddChatMessage         : 0x584F08 (add message to chat display)
    //   SendChatMessage        : 0x5D8574 (JNI exported sendChatMessage wrapper)

    MSHookFunction((void*) getAbsoluteAddress(libName, 0x5850C4), (void*) ChatWindowInputHandler,
      (void **) &old_ChatWindowInputHandler);

    MSHookFunction((void*) getAbsoluteAddress(libName, 0x584F08), (void*) AddChatMessage,
      (void **) &old_AddChatMessage);

    MSHookFunction((void*) getAbsoluteAddress(libName, 0x5D8574), (void*) SendChatMessage,
      (void **) &SendChatMessage);

    return NULL;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);

    pthread_t ptid;
    pthread_create(&ptid, NULL, cheat, NULL);

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}
