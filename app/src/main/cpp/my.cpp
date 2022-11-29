#include<jni.h>
#include"Calculator_interface.h"

extern "C" JNIEXPORT void JNICALL
Java_com_example_my_MainActivity_calculate(JNIEnv *env, jobject thisObject, jstring s) {
    jclass Activity = env->GetObjectClass(thisObject);
    jfieldID answer = env->GetFieldID(Activity, "answer", "Lcom/example/my/InformationFromC;");
    jmethodID set = env->GetMethodID(env->FindClass("com/example/my/InformationFromC"), "setBoth", "(Ljava/lang/String;Ljava/lang/String;)V");
    Calculator_interface::initialize();
    try {
        env->CallVoidMethod
        (env->GetObjectField(thisObject, answer),
                            set,
                            env->NewStringUTF(Calculator_interface::calculate(std::string(env->GetStringUTFChars(s, nullptr))).c_str()),
                            env->NewStringUTF(""));
    }
    catch(Calculator::Calculator_error& e)
    {
        env->CallVoidMethod(env->GetObjectField(thisObject, answer),
                            set,
                            env->NewStringUTF(""),
                            env->NewStringUTF(e.what()));
    }
    catch(...)
    {
        env->CallVoidMethod(env->GetObjectField(thisObject, answer),
                            set,
                            env->NewStringUTF(""),
                            env->NewStringUTF("Something went wrong"));
    }

}