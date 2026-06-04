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
#include <cmath>

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
static inline void writeInt(uintptr_t offset, int val) {
    uintptr_t addr = getAbsoluteAddress(libName, offset);
    if (addr) *(int*)addr = val;
}

// ---- Known globals (from binary analysis) ----
#define OFFSET_GRAVITY      0x94e3c0   // float 0.008 — world gravity
#define OFFSET_FOV          0x976b60   // float 45.0  — camera FOV
#define OFFSET_PED_CONT     0x4c4d600  // ptr → ptr → CPed

// ---- CPed struct offsets (confirmed by disassembly) ----
#define PED_POS_X    0x38
#define PED_POS_Y    0x3c
#define PED_POS_Z    0x40
#define PED_VEL_X    0x44
#define PED_VEL_Y    0x48
#define PED_VEL_Z    0x4c
#define PED_ANGLE    0x50
#define PED_HEALTH   0xb4
#define PED_ARMOR    0xb8
#define PED_VEHICLE  0x3e0
#define PED_SPRINT   0x5E0   // float sprint energy; ≥999999 = infinite

// weapon slot at 0x5bc (ammo in clip), 0x5c0 (total ammo)
#define PED_AMMO_CLIP   0x5bc
#define PED_AMMO_TOTAL  0x5c0

// ---- CVehicle struct offsets ----
#define VEH_POS_X    0x38
#define VEH_POS_Y    0x3c
#define VEH_POS_Z    0x40
#define VEH_VEL_X    0x44
#define VEH_VEL_Y    0x48
#define VEH_VEL_Z    0x4c
#define VEH_ANGLE    0x50
#define VEH_HEALTH   0x368   // float max 1000.0

// ---- Player / vehicle getters ----
static inline uintptr_t getPlayerPed() {
    uintptr_t base = getAbsoluteAddress(libName, OFFSET_PED_CONT);
    if (!base) return 0;
    uintptr_t cont = *(uintptr_t*)base;
    if (!cont) return 0;
    return *(uintptr_t*)cont;
}

static inline uintptr_t getVehicle(uintptr_t ped) {
    if (!ped) return 0;
    return *(uintptr_t*)(ped + PED_VEHICLE);
}

// ---- Sky color table (binary analysis: 0x93c860, byte RGB triples) ----
#define OFFSET_SKY_TABLE  0x93c860
#define SKY_TABLE_ENTRIES 64   // time-of-day entries

JNIEXPORT jobjectArray JNICALL Java_il2cpp_typefaces_Main_getFeatures(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;
    const char *features[] = {
        // Pages
        "page_Персонаж_player.png",
        "page_Оружие_info.png",
        "page_Транспорт_car.png",
        "page_Визуал_visual.png",

        // Blocks per page
        "BLOCK_0_0,1",
        "BLOCK_1_2,3",
        "BLOCK_2_4,5",
        "BLOCK_3_6,7",

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

// ---- Game loop: per-frame features ----
static void gameLoop() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        uintptr_t ped = getPlayerPed();
        if (!ped) continue;

        uintptr_t vehicle = getVehicle(ped);

        // --- Speed ---
        if (b_Speed) {
            if (vehicle) {
                float vx = *(float*)(vehicle + VEH_VEL_X);
                float vy = *(float*)(vehicle + VEH_VEL_Y);
                float vz = *(float*)(vehicle + VEH_VEL_Z);
                float spd = sqrtf(vx*vx + vy*vy + vz*vz);
                if (spd > 0.08f && spd < 0.9f) {
                    float sc = 1.6f;
                    *(float*)(vehicle + VEH_VEL_X) = vx * sc;
                    *(float*)(vehicle + VEH_VEL_Y) = vy * sc;
                    *(float*)(vehicle + VEH_VEL_Z) = vz * sc;
                }
            } else {
                float vx = *(float*)(ped + PED_VEL_X);
                float vy = *(float*)(ped + PED_VEL_Y);
                float spd = sqrtf(vx*vx + vy*vy);
                if (spd > 0.03f && spd < 0.5f) {
                    float sc = 2.5f;
                    *(float*)(ped + PED_VEL_X) = vx * sc;
                    *(float*)(ped + PED_VEL_Y) = vy * sc;
                }
            }
        }

        // --- InfSprint: game checks sprint >= 999999 for infinite ---
        if (b_InfSprint) {
            *(float*)(ped + PED_SPRINT) = 999999.0f;
        }

        // --- Slap: push player upward momentarily ---
        if (b_Slap && !vehicle) {
            *(float*)(ped + PED_VEL_Z) = 0.25f;
        }

        // --- SpinnerPed: rotate heading each tick ---
        if (b_SpinnerPed) {
            float a = *(float*)(ped + PED_ANGLE);
            a += 0.18f;
            if (a > 3.14159f) a -= 6.28318f;
            *(float*)(ped + PED_ANGLE) = a;
        }

        // --- LongJump: boost upward velocity while ascending ---
        if (b_LongJump && !vehicle) {
            float vz = *(float*)(ped + PED_VEL_Z);
            if (vz > 0.15f && vz < 0.6f) {
                *(float*)(ped + PED_VEL_Z) = vz * 2.8f;
            }
        }

        // --- AntiAFK: nudge velocity to fake activity ---
        if (b_AntiAFK) {
            static int afkTick = 0;
            afkTick++;
            if (afkTick % 40 == 0) {
                float vx = *(float*)(ped + PED_VEL_X);
                *(float*)(ped + PED_VEL_X) = vx + 0.0001f;
            }
        }

        // --- FlyPed: sustain upward velocity on foot ---
        if (b_FlyPed && !vehicle) {
            *(float*)(ped + PED_VEL_Z) = 0.12f;
        }

        // --- FastTurn: rotate player quickly toward motion ---
        if (b_FastTurn && !vehicle) {
            float vx = *(float*)(ped + PED_VEL_X);
            float vy = *(float*)(ped + PED_VEL_Y);
            float spd = sqrtf(vx*vx + vy*vy);
            if (spd > 0.02f) {
                float targetAngle = atan2f(-vx, vy);
                *(float*)(ped + PED_ANGLE) = targetAngle;
            }
        }

        // --- AirBrake: zero all velocity ---
        if (b_AirBrake) {
            if (vehicle) {
                *(float*)(vehicle + VEH_VEL_X) = 0.0f;
                *(float*)(vehicle + VEH_VEL_Y) = 0.0f;
                *(float*)(vehicle + VEH_VEL_Z) = 0.0f;
            } else {
                *(float*)(ped + PED_VEL_X) = 0.0f;
                *(float*)(ped + PED_VEL_Y) = 0.0f;
                *(float*)(ped + PED_VEL_Z) = 0.0f;
            }
        }

        // --- WalkWater: prevent sinking below surface ---
        if (b_WalkWater && !vehicle) {
            float z = *(float*)(ped + PED_POS_Z);
            if (z < 0.3f) {
                *(float*)(ped + PED_VEL_Z) = 0.08f;
            }
        }

        // --- InfAmmo: keep clip and total ammo maxed ---
        if (b_InfAmmo) {
            *(int*)(ped + PED_AMMO_CLIP)  = 9999;
            *(int*)(ped + PED_AMMO_TOTAL) = 9999;
        }

        // --- CarGod: max vehicle health every frame ---
        if (b_CarGod && vehicle) {
            *(float*)(vehicle + VEH_HEALTH) = 1000.0f;
        }

        // --- InfEngine: keep engine health full ---
        if (b_InfEngine && vehicle) {
            *(float*)(vehicle + 0x4A4) = 1000.0f;
        }

        // --- GiveNitro: continuously refill nitro slot ---
        if (b_GiveNitro && vehicle) {
            *(float*)(vehicle + 0x93C) = 1.0f;
        }

        // --- LaunchCtrl: thrust vehicle forward ---
        if (b_LaunchCtrl && vehicle) {
            float vx = *(float*)(vehicle + VEH_VEL_X);
            float vy = *(float*)(vehicle + VEH_VEL_Y);
            float spd = sqrtf(vx*vx + vy*vy);
            if (spd < 0.7f) {
                float ang = *(float*)(vehicle + VEH_ANGLE);
                float boost = 0.4f;
                *(float*)(vehicle + VEH_VEL_X) = -sinf(ang) * boost;
                *(float*)(vehicle + VEH_VEL_Y) =  cosf(ang) * boost;
            }
        }

        // --- Hydraulics: bounce vehicle vertically ---
        if (b_Hydraulics && vehicle) {
            static int hydTick = 0;
            hydTick++;
            float dir = ((hydTick / 5) % 2 == 0) ? 0.08f : -0.04f;
            *(float*)(vehicle + VEH_VEL_Z) += dir;
        }

        // --- SpinnerCar: rotate vehicle heading ---
        if (b_SpinnerCar && vehicle) {
            float a = *(float*)(vehicle + VEH_ANGLE);
            a += 0.2f;
            if (a > 3.14159f) a -= 6.28318f;
            *(float*)(vehicle + VEH_ANGLE) = a;
        }

        // --- FastStop: heavy braking ---
        if (b_FastStop && vehicle) {
            *(float*)(vehicle + VEH_VEL_X) *= 0.60f;
            *(float*)(vehicle + VEH_VEL_Y) *= 0.60f;
            *(float*)(vehicle + VEH_VEL_Z) *= 0.80f;
        }

        // --- DrawDist: write large draw distance ---
        if (b_DrawDist) {
            uintptr_t base = getAbsoluteAddress(libName, 0x92081c);
            if (base) {
                for (int i = 0; i < 40; i++) {
                    *(float*)(base + i * 0x28) = 2000.0f;
                }
            }
        }

        // --- BlackSky: zero sky color table ---
        if (b_BlackSky) {
            uintptr_t tbl = getAbsoluteAddress(libName, OFFSET_SKY_TABLE);
            if (tbl) {
                for (int i = 0; i < SKY_TABLE_ENTRIES * 3; i++) {
                    *(uint32_t*)(tbl + i * 4) = 0;
                }
            }
        }

        // --- NiceGraphics: high quality settings via FOV + far clip ---
        if (b_NiceGraphics) {
            writeFloat(OFFSET_FOV,     90.0f);
            writeFloat(OFFSET_FOV + 4, 90.0f);
        }

        // --- BigPickups: scale pickup objects ---
        if (b_BigPickups) {
            // Object scale global; write after pickup container
            uintptr_t base = getAbsoluteAddress(libName, 0x94d540 + 0x120);
            if (base) *(float*)base = 3.0f;
        }
    }
}

JNIEXPORT void JNICALL
Java_il2cpp_typefaces_Main_Changes(JNIEnv *env, jobject activityObject, jint feature, jint value) {
    bool on = (value == 1);
    switch (feature) {

        // ===== ПЕРСОНАЖ =====
        case 1:  b_Speed       = on; break;
        case 2:  b_NoCollision = on; break;
        case 3:  b_InfSprint   = on; break;
        case 4:  b_Slap        = on; break;
        case 5:  b_SpinnerPed  = on; break;
        case 6:  b_LongJump    = on; break;
        case 7:  b_AntiAFK     = on; break;
        case 8:  b_NoAnim      = on; break;
        case 9:  b_FlyPed      = on; break;
        case 10: b_FastTurn    = on; break;

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

        case 14: b_WalkWater   = on; break;
        case 15: b_AirBrake    = on; break;
        case 16: b_FastCrash   = on; break;

        // ===== ОРУЖИЕ =====
        case 17: b_InfAmmo     = on; break;
        case 18: b_FastShoot   = on; break;
        case 19: b_FakeAim     = on; break;
        case 20: b_WallShoot   = on; break;

        // ===== ТРАНСПОРТ =====
        case 21: b_CarGod      = on; break;
        case 22: b_InfEngine   = on; break;
        case 23: b_GiveNitro   = on; break;
        case 24: b_LaunchCtrl  = on; break;
        case 25: b_Hydraulics  = on; break;
        case 26: b_AntiFine    = on; break;
        case 27: b_SpinnerCar  = on; break;
        case 28: b_NoSpeedLimit= on; break;
        case 29: b_NoCarCollide= on; break;
        case 30: b_FastStop    = on; break;
        case 31: b_CamControl  = on; break;

        // ===== ВИЗУАЛ =====
        case 32: // Прорисовка
            b_DrawDist = on;
            break;

        case 33: // Черное небо
            b_BlackSky = on;
            break;

        case 34: b_NiceGraphics= on; break;
        case 35: b_BigFOV      = on; break;

        case 36: // Большой FOV
            b_BigFOV = on;
            writeFloat(OFFSET_FOV,     on ? 100.0f : 45.0f);
            writeFloat(OFFSET_FOV + 4, on ? 100.0f : 45.0f);
            break;

        case 37: b_BigPickups  = on; break;
        case 38: b_StopCam     = on; break;
        case 39: b_CamHeight   = on; break;
        case 40: b_HideNick    = on; break;
        case 41: b_ZoomCam     = on; break;
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
Java_il2cpp_typefaces_KEY_name2(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Авторизация");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name3(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Введите ключ");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name4(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("ВОЙТИ");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name5(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("ПОЛУЧИТЬ КЛЮЧ");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name6(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Ключ верен!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name7(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Чит запускается, подождите!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name8(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Неверный ключ!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_name9(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Неверный ключ!");
}

JNIEXPORT jstring JNICALL
Java_il2cpp_typefaces_KEY_key7(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Troll777");
}

// EXTERN END
}

void *cheat(void *) {
    DobbyHook((void*) getAbsoluteAddress(libName, 0x5850C4),
              (void*) ChatWindowInputHandler,
              (void**) &old_ChatWindowInputHandler);

    real_AddChatMessage = (AddChatMessageFunc) getAbsoluteAddress(libName, 0x569C9C);

    // Start per-frame feature loop
    std::thread(gameLoop).detach();

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
