#include <pthread.h>
#include <jni.h>
#include <Includes/Utils.h>
#include "Dobby/dobby.h"
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

const char *libName = "libblackrussia-client.so";

// ---- AddChatMessage ----
typedef void (*AddChatMessageFunc)(int color, char* text);
AddChatMessageFunc real_AddChatMessage = nullptr;

void AddChatMessage(const char* text) {
    if (!text || !real_AddChatMessage) return;
    real_AddChatMessage(0xBEBEBEFF, (char*)text);
}

// ---- Feature flags ----
bool b_Speed         = false;
bool b_NoCollision   = false;
bool b_InfSprint     = false;
bool b_Slap          = false;
bool b_SpinnerPed    = false;
bool b_LongJump      = false;
bool b_AntiAFK       = false;
bool b_NoAnim        = false;
bool b_FlyPed        = false;
bool b_FastTurn      = false;
bool b_FakeLags      = false;
bool b_NoGravity     = false;
bool b_WalkWater     = false;
bool b_AirBrake      = false;
bool b_FastCrash     = false;
bool b_InfAmmo       = false;
bool b_FastShoot     = false;
bool b_FakeAim       = false;
bool b_WallShoot     = false;
bool b_CarGod        = false;
bool b_InfEngine     = false;
bool b_GiveNitro     = false;
bool b_LaunchCtrl    = false;
bool b_Hydraulics    = false;
bool b_AntiFine      = false;
bool b_SpinnerCar    = false;
bool b_NoSpeedLimit  = false;
bool b_NoCarCollide  = false;
bool b_FastStop      = false;
bool b_CamControl    = false;
bool b_DrawDist      = false;
bool b_BlackSky      = false;
bool b_NiceGraphics  = false;
bool b_BigFOV        = false;
bool b_BigPickups    = false;
bool b_StopCam       = false;
bool b_CamHeight     = false;
bool b_HideNick      = false;
bool b_ZoomCam       = false;
bool fl              = false;

// ---- Memory helpers ----
static inline void writeFloat(uintptr_t offset, float val) {
    uintptr_t addr = getAbsoluteAddress(libName, offset);
    if (addr) *(float*)addr = val;
}
static inline float readFloat(uintptr_t offset) {
    uintptr_t addr = getAbsoluteAddress(libName, offset);
    return addr ? *(float*)addr : 0.f;
}

// ---- Known globals (from binary analysis) ----
#define OFFSET_GRAVITY   0x94e3c0   // float 0.008 — world gravity
#define OFFSET_FOV       0x976b60   // float 45.0  — camera FOV

JNIEXPORT jobjectArray JNICALL Java_il2cpp_Main_getFeatures(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;
    const char *features[] = {
        // Pages
        "page_Персонаж_player.png",
        "page_Оружие_weapon.png",
        "page_Транспорт_car.png",
        "page_Визуал_visual.png",

        // Blocks per page
        "BLOCK_0_0,1",    // page 0: blocks 0,1
        "BLOCK_1_2,3",    // page 1: blocks 2,3
        "BLOCK_2_4,5",    // page 2: blocks 4,5
        "BLOCK_3_6,7",    // page 3: blocks 6,7

        // ===== Персонаж (page 0) =====
        "h1_0_1_Скорость",
        "h1_0_2_Откл.Коллизии",
        "h1_0_3_Бесконечный бег",
        "h1_0_4_Слап",
        "h1_0_5_Крутилка",
        "h1_0_6_Длинный прыжок",
        "h1_1_7_Анти АФК",
        "h1_1_8_Откл.Анимации",
        "h1_1_9_Флай Пед",
        "h1_1_10_Быстрый поворот",
        "h1_1_11_Флудер",
        "h1_1_12_Откл.Гравитацию",
        "h1_1_14_Ходьба под водой",
        "h1_1_15_Аир Брейк",
        "h1_1_16_Фаст Краш",

        // ===== Оружие (page 1) =====
        "h1_2_17_Бесконечные патроны",
        "h1_2_18_Быстрая Стрельба",
        "h1_2_19_Фейк прицел",
        "h1_3_20_Стрельба сквозь стены",

        // ===== Транспорт (page 2) =====
        "h1_4_21_Бесмертие машины",
        "h1_4_22_Вечный двигатель",
        "h1_4_23_Выдать нитро",
        "h1_4_24_Лаунч контроль",
        "h1_5_25_Гидравлика",
        "h1_5_26_Анти штраф",
        "h1_5_27_Крутилка авто",
        "h1_5_28_Откл.лимит скорости",
        "h1_5_29_Откл.Коллизия авто",
        "h1_4_30_Фаст стоп",
        "h1_5_31_Управление камерой",

        // ===== Визуал (page 3) =====
        "h1_6_32_Прорисовка",
        "h1_6_33_Черное небо",
        "h1_6_34_Красивая графика",
        "h1_7_35_Большой угол обзора",
        "h1_7_36_Большой FOV",
        "h1_7_37_Большие пикапы",
        "h1_6_38_Стоп камера",
        "h1_7_39_Высота камеры",
        "h1_6_40_Скрыть ники",
        "h1_7_41_Приблизить камеру",
    };
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return ret;
}

JNIEXPORT void JNICALL
Java_il2cpp_Main_Changes(JNIEnv *env, jobject activityObject, jint feature, jint value) {
    bool on = (value == 1);
    switch (feature) {

        // ===== ПЕРСОНАЖ =====
        case 1:  b_Speed       = on; /* TODO: patch max speed */       break;
        case 2:  b_NoCollision = on; /* TODO: patch collision check */  break;
        case 3:  b_InfSprint   = on; /* TODO: patch sprint decrement */ break;
        case 4:  b_Slap        = on; /* TODO */                         break;
        case 5:  b_SpinnerPed  = on; /* TODO */                         break;
        case 6:  b_LongJump    = on; /* TODO */                         break;
        case 7:  b_AntiAFK     = on; /* TODO */                         break;
        case 8:  b_NoAnim      = on; /* TODO */                         break;
        case 9:  b_FlyPed      = on; /* TODO */                         break;
        case 10: b_FastTurn    = on; /* TODO */                         break;

        case 11: // Флудер
            fl = !fl;
            if (fl) {
                AddChatMessage("{F12763}Apex |{ffffff} Введите команду:");
                AddChatMessage("{F12763}Apex |{ffffff} /flood <сообщение>");
            }
            break;

        case 12: // Откл. Гравитацию
            b_NoGravity = on;
            writeFloat(OFFSET_GRAVITY, on ? 0.0f : 0.008f);
            break;

        case 14: b_WalkWater   = on; /* TODO */                         break;
        case 15: b_AirBrake    = on; /* TODO */                         break;
        case 16: b_FastCrash   = on; /* TODO */                         break;

        // ===== ОРУЖИЕ =====
        case 17: b_InfAmmo     = on; /* TODO: patch ammo decrement */   break;
        case 18: b_FastShoot   = on; /* TODO: patch fire delay */       break;
        case 19: b_FakeAim     = on; /* TODO */                         break;
        case 20: b_WallShoot   = on; /* TODO: patch bullet collision */ break;

        // ===== ТРАНСПОРТ =====
        case 21: b_CarGod      = on; /* TODO: patch vehicle damage */   break;
        case 22: b_InfEngine   = on; /* TODO */                         break;
        case 23: b_GiveNitro   = on; /* TODO */                         break;
        case 24: b_LaunchCtrl  = on; /* TODO */                         break;
        case 25: b_Hydraulics  = on; /* TODO */                         break;
        case 26: b_AntiFine    = on; /* TODO */                         break;
        case 27: b_SpinnerCar  = on; /* TODO */                         break;
        case 28: b_NoSpeedLimit= on; /* TODO */                         break;
        case 29: b_NoCarCollide= on; /* TODO */                         break;
        case 30: b_FastStop    = on; /* TODO */                         break;
        case 31: b_CamControl  = on; /* TODO */                         break;

        // ===== ВИЗУАЛ =====
        case 32: b_DrawDist    = on; /* TODO */                         break;
        case 33: b_BlackSky    = on; /* TODO */                         break;
        case 34: b_NiceGraphics= on; /* TODO */                         break;
        case 35: b_BigFOV      = on; /* TODO */                         break;

        case 36: // Большой FOV
            b_BigFOV = on;
            writeFloat(OFFSET_FOV, on ? 100.0f : 45.0f);
            writeFloat(OFFSET_FOV + 4, on ? 100.0f : 45.0f);
            break;

        case 37: b_BigPickups  = on; /* TODO */                         break;
        case 38: b_StopCam     = on; /* TODO */                         break;
        case 39: b_CamHeight   = on; /* TODO */                         break;
        case 40: b_HideNick    = on; /* TODO */                         break;
        case 41: b_ZoomCam     = on; /* TODO */                         break;
    }
}

// ---- Chat hook ----
void(*old_ChatWindowInputHandler)(char *text);

bool floodActive = false;
std::string floodMessage = "";

void floodFunction() {
    while (floodActive) {
        if (old_ChatWindowInputHandler) {
            char* text = new char[floodMessage.length() + 1];
            strcpy(text, floodMessage.c_str());
            old_ChatWindowInputHandler(text);
            delete[] text;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ChatWindowInputHandler(char *text) {
    if (strncmp(text, "/flood ", 7) == 0) {
        AddChatMessage("{F12763}Apex |{ffffff} Чтобы остановить — введи снова");
        floodMessage = std::string(text + 7);
        floodActive = !floodActive;
        if (floodActive) {
            std::thread(floodFunction).detach();
        }
        return;
    }
    old_ChatWindowInputHandler(text);
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
    return env->NewStringUTF("t.me/Troll_mod");
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

// EXTERN END
}

void *cheat(void *) {
    DobbyHook((void*) getAbsoluteAddress(libName, 0x5850C4),
              (void*) ChatWindowInputHandler,
              (void**) &old_ChatWindowInputHandler);

    real_AddChatMessage = (AddChatMessageFunc) getAbsoluteAddress(libName, 0x569C9C);

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
