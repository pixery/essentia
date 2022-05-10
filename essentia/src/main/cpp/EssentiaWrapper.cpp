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
    auto fd = jniGetFDFromFileDescriptor(env, fileDescriptor);
    struct stat statbuf;
    fstat(fd, &statbuf);
    auto realPCMBuffer = (char *) mmap(nullptr, statbuf.st_size, PROT_READ, MAP_PRIVATE|MAP_POPULATE, fd, 0); // pcm file consists of values between -128 to 127

    auto signal = std::vector<essentia::Real>();
    signal.reserve(statbuf.st_size);
    for (size_t i = 0; i < statbuf.st_size; i++) {
        signal.push_back(realPCMBuffer[i] / 128.f); // pcm values are normalized here
    }
    munmap(realPCMBuffer, statbuf.st_size);

    auto ticks = std::vector<essentia::Real>();

    essentia::init();
    auto &factory = essentia::standard::AlgorithmFactory::instance();
    auto rhythmExtractor = factory.create("RhythmExtractor2013", "method", "multifeature");

    essentia::Real bpm, confidence;
    std::vector<essentia::Real> estimates, bpmIntervals;

    rhythmExtractor->input("signal").set(signal);
    rhythmExtractor->output("ticks").set(ticks);
    rhythmExtractor->output("bpm").set(bpm);
    rhythmExtractor->output("confidence").set(confidence);
    rhythmExtractor->output("estimates").set(estimates);
    rhythmExtractor->output("bpmIntervals").set(bpmIntervals);
    rhythmExtractor->compute();

    auto tickCount = (jsize) ticks.size();
    auto _ticks = env->NewFloatArray(tickCount);
    env->SetFloatArrayRegion(_ticks, 0, tickCount, ticks.data());

    delete rhythmExtractor;
    essentia::shutdown();

    return _ticks;
}
