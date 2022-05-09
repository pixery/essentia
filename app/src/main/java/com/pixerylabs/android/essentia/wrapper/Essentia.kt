package com.pixerylabs.android.essentia.wrapper

import java.io.File
import java.io.FileDescriptor

object Essentia {

    init {
        System.loadLibrary("essentia")
    }

    private external fun nativeFindTicksFd(fileDescriptor: FileDescriptor): FloatArray

    fun findTicks(fileDescriptor: FileDescriptor) = nativeFindTicksFd(fileDescriptor)

    fun findTicks(file: File) = file.inputStream().use { findTicks(it.fd) }

    fun findTicks(filePath: String) = findTicks(File(filePath))

}
