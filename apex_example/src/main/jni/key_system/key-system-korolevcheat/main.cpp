#include <pthread.h>
#include <jni.h>
#include <Includes/Utils.h>
#include <Substrate/SubstrateHook.h>
#include "KittyMemory/MemoryPatch.h"
#include "MonoString.h"
#include <thread>
#include <chrono>
#include <cstring>
#include <jni.h>
#include <string>
#include <vector>



#include "Quaternion.h"

extern "C" {
	
//Шифрованый текст,значения из Menu
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_typefaces_Menu_name(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("APEX");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_typefaces_Menu_close(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("× Закрыть");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_typefaces_Menu_name1(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("t.me/apexxsoft");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name2(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("Авторизация");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name3(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("Введите ключ");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name4(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("ВОЙТИ");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name5(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("ПОЛУЧИТЬ КЛЮЧ");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name6(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("Ключ верен!");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name7(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("Чит запускается, подождите!");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name8(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("Неверный ключ!");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_name9(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("Неверный ключ!");
    return str;
	}
	
JNIEXPORT jstring JNICALL
    Java_il2cpp_KEY_key7(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("apex");
    return str;
	}
	

	

bool beskbeg,black,flood = false;


const char *libName = "liblackrussia-client.so";

const char *lastMessage = "Hello";

struct My_Patches {MemoryPatch Beskbeg, Black;} hexPatches;

JNIEXPORT jobjectArray  JNICALL Java_il2cpp_Main_getFeatures(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;
    // switch_featureid_text
    const char *features[] = {
        "page_Персонаж_player.png",
		"page_Оружие_uron.png",
        "page_Транспорт_car.png",
        "page_Визуалы_visual.png",
		"page_Настройки_sett.png",
        
        "BLOCK_0_0,1",
        "BLOCK_1_2,3",
        "BLOCK_2_4,5",
        "BLOCK_3_6,7",
		"BLOCK_4_8,9",

        
		//Блок - Персонаж 
		//*примечание = "h1_0 = слева
	   //               "h1_1 = справа
	   
		
        "h1_0_1_Скрорость",
		"h1_1_2_Откл.Колизии",
		"h1_0_3_Бесконечный бег",
		"h1_1_4_Слап",
		"h1_0_5_Крутилка",
		"h1_0_6_Длинный прыжок",
		"h1_1_7_Анти АФК",
		"h1_0_8_Откл.Анимации",
		"h1_1_9_Флай Пед",
		"h1_0_10_Быстрый поворот",
		"h1_1_11_Fake Lags",
		"h1_1_12_Откл.Гравитацию",
		"h1_0_14_Ходьба под водой",
		"h1_1_15_Аир Брейк",
		"h1_0_16_Фаст Краш",
		
		
		//Блок - Оружие
		
		"h1_2_17_Бесконечные пвтроны",
		"h1_3_18_Быстрая Стрельба",
		"h1_2_19_Фейк прицел",
		"h1_3_20_Стрельба сквозь стены",
		
		
		//Блок - Транспорт
		
		
		"h1_4_21_Бесмертие машины",
		"h1_5_22_Вечный двигатель",
		"h1_4_23_Выдать нитро",
		"h1_5_24_Лаунч контроль",
		"h1_4_25_Гидравлика",
		"h1_5_26_Анти штраф",
		"h1_4_27_Крутилка",
		"h1_5_28_Откл.лимит скорости",
		"h1_4_29_Откл.Колизия",
		"h1_5_30_Фаст стоп",
		"h1_4_31_Управление камерой",
		
		
		//Блок - Визуал
		
		"h1_6_32_Прорисовка",
		"h1_7_33_Черное небо",
		"h1_6_34_Красивая графика",
		"h1_7_35_Большой угол обзора",
		"h1_6_36_Большой FOV",
		"h1_7_37_Большие пикапы",
		"h1_6_38_Стоп камера",
		"h1_7_39_Высота камеры",
		"h1_6_40_Скрыть ники",
		"h1_7_41_Приблизить камеру",
		
		
		
       
     
    };
    int Total_Feature = (sizeof features /
                         sizeof features[0]); //Now you dont have to manually update the number everytime;
    
    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}


JNIEXPORT void JNICALL
Java_il2cpp_Main_Changes(JNIEnv *env,jobject activityObject,jint feature,jint value) {
    /*  FEATURES  */
        switch (feature) {
        	case 99:
		black = !black;
		if(black){
		hexPatches.Black.Modify();
		}else{
		hexPatches.Black.Restore();
		}
		break;
		
	
		
		


                    
    }
}




// EXTERN END
}
// ---------- Hooking ---------- //

void *hack_thread(void *) {
	
	
	
	
    // ---------- Hook ---------- //
	
		hexPatches.Beskbeg = MemoryPatch::createWithHex("libblackrussia-client.so", 0x37D988, "0000A0C0");
	    hexPatches.Black = MemoryPatch::createWithHex("libblackrussia-client.so", 0x3C45A4, "0000C6C2");
	
		
      return NULL;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);

    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}


