package com.pixerylabs.android.essentia.wrapper

import java.io.File
import java.io.FileDescriptor

object Essentia {

    init {
        System.loadLibrary("essentia")
    }

    private external fun nativeFindTicksFd(fileDescriptor: FileDescriptor): FloatArray
    private external fun nativeFindOnsetsFd(fileDescriptor: FileDescriptor): FloatArray

    fun findTicks(fileDescriptor: FileDescriptor) = nativeFindTicksFd(fileDescriptor)

    fun findTicks(file: File) = file.inputStream().use { findTicks(it.fd) }

    fun findTicks(filePath: String) = findTicks(File(filePath))

    fun findOnsets(fileDescriptor: FileDescriptor): FloatArray = nativeFindOnsetsFd(fileDescriptor)

    fun findOnsets(file: File): FloatArray = file.inputStream().use { findOnsets(it.fd) }

    fun findOnsets(filePath: String): FloatArray = findOnsets(File(filePath))
}
