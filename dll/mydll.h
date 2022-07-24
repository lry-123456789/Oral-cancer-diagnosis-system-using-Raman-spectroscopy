#pragma once
#ifndef _MYDLL_H_
#define _MYDLL_H_
#ifndef EXPORT_DLL
#define EXPORT_DLL _declspec(dllexport)
#endif
extern "C" EXPORT_DLL double* PCA_LDA_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* PCA_SVM_RBF_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* PCA_SVM_POLY_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* RF_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* AlexNet_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* VGGNet_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* ResNet_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* DenseNet_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* MobileNetV2_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* MobileNetV3_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* EfficientNet_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* EfficientNetV2_model(float* inputdata,float* output);
extern "C" EXPORT_DLL double* transformer_model(float* inputdata,float* output);
#endif
