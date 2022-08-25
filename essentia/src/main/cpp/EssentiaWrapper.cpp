#include <jni.h>
#include "algorithm.h"
#include "algorithmfactory.h"
#include "android/log.h"
#include "sys/stat.h"
#include "sys/mman.h"

//
// Created by Berkin Güler on 27.04.2022.
//

static struct {
    jfieldID descriptor;
} gFileDescriptorClassInfo;

static inline int jniGetFDFromFileDescriptor(JNIEnv *env, jobject fd) {
    return env->GetIntField(fd, gFileDescriptorClassInfo.descriptor);
}

static std::vector<essentia::Real> getSignalFromFileDescriptor(JNIEnv *env, jobject fileDescriptor) {
    auto fd = jniGetFDFromFileDescriptor(env, fileDescriptor);
    struct stat statbuf{};
    fstat(fd, &statbuf);
    auto realPCMBuffer = (char *) mmap(nullptr, statbuf.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0); // pcm file consists of values between -128 to 127

    std::vector<essentia::Real> signal;
    signal.reserve(statbuf.st_size);
    for (size_t i = 0; i < statbuf.st_size; i++) {
        signal.push_back((float) realPCMBuffer[i] / 128.f); // pcm values are normalized here
    }
    munmap(realPCMBuffer, statbuf.st_size);
    return signal;
}

static jfloatArray jfloatArrayFromVector(JNIEnv *env, std::vector<float>& vector) {
    auto vectorSize = (jsize) vector.size();
    auto floatArray = env->NewFloatArray(vectorSize);
    env->SetFloatArrayRegion(floatArray, 0, vectorSize, vector.data());
    return floatArray;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *unused) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    auto clazz = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/io/FileDescriptor")));
    if (clazz == nullptr) {
        return JNI_ERR;
    }

    gFileDescriptorClassInfo.descriptor = env->GetFieldID(clazz, "descriptor", "I");
    if (gFileDescriptorClassInfo.descriptor == nullptr) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_com_pixerylabs_android_essentia_wrapper_Essentia_nativeFindTicksFd(JNIEnv *env, jobject thiz,
                                                                      jobject fileDescriptor) {
    auto signal = getSignalFromFileDescriptor(env, fileDescriptor);

    essentia::init();
    auto rhythmExtractor = essentia::standard::AlgorithmFactory::create("RhythmExtractor2013", "method", "multifeature");
    jfloatArray _ticks;

    try {
        essentia::Real bpm, confidence;
        std::vector<essentia::Real> ticks, estimates, bpmIntervals;

        rhythmExtractor->input("signal").set(signal);
        rhythmExtractor->output("ticks").set(ticks);
        rhythmExtractor->output("bpm").set(bpm);
        rhythmExtractor->output("confidence").set(confidence);
        rhythmExtractor->output("estimates").set(estimates);
        rhythmExtractor->output("bpmIntervals").set(bpmIntervals);
        rhythmExtractor->compute();

        _ticks = jfloatArrayFromVector(env, ticks);
    } catch (essentia::EssentiaException &ex) {
        __android_log_print(ANDROID_LOG_ERROR, "Essentia", "%s", ex.what());
        _ticks = env->NewFloatArray(0);
    }

    delete rhythmExtractor;
    essentia::shutdown();

    return _ticks;
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_com_pixerylabs_android_essentia_wrapper_Essentia_nativeFindOnsetsFd(JNIEnv *env, jobject thiz,
                                                                         jobject fileDescriptor) {
    auto signal = getSignalFromFileDescriptor(env, fileDescriptor);

    essentia::init();
    auto onsetRateExtractor = essentia::standard::AlgorithmFactory::create("OnsetRate");

    std::vector<essentia::Real> onsets;
    essentia::Real onsetRate;

    onsetRateExtractor->input("signal").set(signal);
    onsetRateExtractor->output("onsets").set(onsets);
    onsetRateExtractor->output("onsetRate").set(onsetRate);
    onsetRateExtractor->compute();

    auto result = jfloatArrayFromVector(env, onsets);

    delete onsetRateExtractor;
    essentia::shutdown();

    return result;
}
