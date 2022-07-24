#include"pch.h"
#include"mydll.h"
//上述为dll必要的头文件
//下方为ONNX需要的文件
#include <assert.h>
#include <onnxruntime_c_api.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "cpu_provider_factory.h"
const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
//下方为准备操作

//*****************************************************************************
// helper function to check for status
void CheckStatus(OrtStatus* status)
{
    if (status != NULL) {
        printf("error occured!\n");
        const char* msg = g_ort->GetErrorMessage(status);
        fprintf(stderr, "%s\n", msg);
        g_ort->ReleaseStatus(status);
        exit(1);
    }
}

double* softmax(float* modeloutput)
{
    int class_number;
    double out[6];
    class_number = 6;
    int i = 0;
    double max, min;
    double sum;
    sum = 0;
    for (i = 0; i < class_number; i++)
    {
        sum = sum + exp(modeloutput[i]);
    }
    for (i = 0; i < class_number; i++)
    {
        out[i] = exp(modeloutput[i]) / sum;
    }
    return out;
}

double* PCA_LDA_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"PCA_LDA_output.onnx";
#else
    const char* model_path = "PCA_LDA_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* PCA_SVM_RBF_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"PCA_SVM_RBF_output.onnx";
#else
    const char* model_path = "PCA_SVM_RBF_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* PCA_SVM_POLY_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"PCA_SVM_POLY_output.onnx";
#else
    const char* model_path = "PCA_SVM_POLY_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* RF_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"RF_output.onnx";
#else
    const char* model_path = "RF_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* AlexNet_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"AlexNet_output.onnx";
#else
    const char* model_path = "AlexNet_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* VGGNet_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"VGGNet_output.onnx";
#else
    const char* model_path = "VGGNet_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* ResNet_model(float* inputdata,float * output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"ResNet_output.onnx";
#else
    const char* model_path = "ResNet_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* DenseNet_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"DenseNet_output.onnx";
#else
    const char* model_path = "DenseNet_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* MobileNetV2_model(float* inputdata,float * output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"MobileNetV2_output.onnx";
#else
    const char* model_path = "MobileNetV2_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* MobileNetV3_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"MobileNetV3_output.onnx";
#else
    const char* model_path = "MobileNetV3_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* EfficientNet_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"EfficientNet_output.onnx";
#else
    const char* model_path = "EfficientNet_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* EfficientNetV2_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"EfficientNetV2_output.onnx";
#else
    const char* model_path = "EfficientNetV2_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}

double* transformer_model(float* inputdata,float* output)
{
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
    const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    OrtEnv* env;
    CheckStatus(g_ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "test", &env));

    // initialize session options if needed
    // 给创建session时，需要的一些参数
    OrtSessionOptions* session_options;
    CheckStatus(g_ort->CreateSessionOptions(&session_options));
    // 设置线程数
    g_ort->SetIntraOpNumThreads(session_options, 1);

    // Sets graph optimization level
    // 设置优化级别
    g_ort->SetSessionGraphOptimizationLevel(session_options, ORT_ENABLE_BASIC);

    // Optionally add more execution providers via session_options
    // E.g. for CUDA uncomment the following line:
    // 设置推断函数的持有者，比如是在cuda端还是gpu端
    // 把它称为执行提供者（Execution Provider，其实翻译成赞助商可能更合适，赞助算力嘛，哈哈）
    //CheckStatus(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
    CheckStatus(OrtSessionOptionsAppendExecutionProvider_CPU(session_options, 0));
    //*************************************************************************
    // create session and load model into memory
    // using squeezenet version 1.3
    // URL = https://github.com/onnx/models/tree/master/squeezenet
    OrtSession* session;
#ifdef _WIN32
    const wchar_t* model_path = L"transformerNet_output.onnx";
#else
    const char* model_path = "transformerNet_output.onnx";
#endif

    printf("Using Onnxruntime C API\n");
    // 创建一个session
    CheckStatus(g_ort->CreateSession(env, model_path, session_options, &session));

    //*************************************************************************
    // print model input layer (node names, types, shape etc.)
    size_t num_input_nodes;
    OrtStatus* status;
    OrtAllocator* allocator;
    CheckStatus(g_ort->GetAllocatorWithDefaultOptions(&allocator));

    // print number of model input nodes
    status = g_ort->SessionGetInputCount(session, &num_input_nodes);
    std::vector<const char*> input_node_names(num_input_nodes);
    std::vector<int64_t> input_node_dims;  // simplify... this model has only 1 input node {1, 3, 224, 224}.
                                           // Otherwise need vector<vector<>>

    printf("Number of inputs = %zu\n", num_input_nodes);

    // iterate over all input nodes
    for (size_t i = 0; i < num_input_nodes; i++) {
        // print input node names
        char* input_name;
        status = g_ort->SessionGetInputName(session, i, allocator, &input_name);
        printf("Input %zu : name=%s\n", i, input_name);
        input_node_names[i] = input_name;

        // print input node types
        OrtTypeInfo* typeinfo;
        status = g_ort->SessionGetInputTypeInfo(session, i, &typeinfo);
        const OrtTensorTypeAndShapeInfo* tensor_info;
        CheckStatus(g_ort->CastTypeInfoToTensorInfo(typeinfo, &tensor_info));
        ONNXTensorElementDataType type;
        CheckStatus(g_ort->GetTensorElementType(tensor_info, &type));
        printf("Input %zu : type=%d\n", i, type);

        // print input shapes/dims
        size_t num_dims;
        CheckStatus(g_ort->GetDimensionsCount(tensor_info, &num_dims));
        printf("Input %zu : num_dims=%zu\n", i, num_dims);
        input_node_dims.resize(num_dims);
        g_ort->GetDimensions(tensor_info, (int64_t*)input_node_dims.data(), num_dims);
        input_node_dims[0] = 1;
        for (size_t j = 0; j < num_dims; j++)
        {
            printf("Input %zu : dim %zu=%jd\n", i, j, input_node_dims[j]);

        }

        g_ort->ReleaseTypeInfo(typeinfo);
    }

    // Results should be...
    // Number of inputs = 1
    // Input 0 : name = data_0
    // Input 0 : type = 1
    // Input 0 : num_dims = 4
    // Input 0 : dim 0 = 1
    // Input 0 : dim 1 = 3
    // Input 0 : dim 2 = 224
    // Input 0 : dim 3 = 224

    //*************************************************************************
    // Similar operations to get output node information.
    // Use OrtSessionGetOutputCount(), OrtSessionGetOutputName()
    // OrtSessionGetOutputTypeInfo() as shown above.

    //*************************************************************************
    // Score the model using sample data, and inspect values

    //size_t input_tensor_size = 224 * 224 * 3;  // simplify ... using known dim values to calculate size
                                               // use OrtGetTensorShapeElementCount() to get official size!
    size_t input_tensor_size = 1044;
    std::vector<float> input_tensor_values(input_tensor_size);
    std::vector<const char*> output_node_names = { "modelOutput" }; // 输出节点

    // initialize input data with values in [0.0, 1.0]
    // 这里用的是直接赋值
    // input_tensor_values.data() 相当于 mat.data()
    for (size_t i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = (float)i / (input_tensor_size + 1);

    // create input tensor object from data values
    OrtMemoryInfo* memory_info;
    CheckStatus(g_ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &memory_info));
    OrtValue* input_tensor = NULL;
    g_ort->CreateTensorAsOrtValue(allocator, input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor);
    CheckStatus(g_ort->CreateTensorWithDataAsOrtValue(memory_info, input_tensor_values.data(), input_tensor_size * sizeof(float), input_node_dims.data(), 3, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &input_tensor));
    int is_tensor;
    CheckStatus(g_ort->IsTensor(input_tensor, &is_tensor));
    assert(is_tensor);
    g_ort->ReleaseMemoryInfo(memory_info);

    // score model & input tensor, get back output tensor
    OrtValue* output_tensor = NULL;
    //while (true)
    //{
    CheckStatus(g_ort->Run(session, NULL, input_node_names.data(), (const OrtValue* const*)&input_tensor, 1, output_node_names.data(), 1, &output_tensor));
    CheckStatus(g_ort->IsTensor(output_tensor, &is_tensor));
    assert(is_tensor);

    // Get pointer to output tensor float values
    float* floatarr;
    CheckStatus(g_ort->GetTensorMutableData(output_tensor, (void**)&floatarr));
    assert(std::abs(floatarr[0] - 0.000045) < 1e-6);

    // score the model, and print scores for first 5 classes
    for (int i = 0; i < 6; i++)
        printf("Score for class [%d] =  %f\n", i, floatarr[i]);
    //}
    std::cout << "model=" << model_path << std::endl;
    std::cout << "using softmax function to transfer,please wait...\n";
    auto out = softmax(floatarr);
    for (int i = 0; i < 6; i++)
    {
        printf("accuracy for class [%d] = %lf\n", i, out[i]);
        output[i] = out[i];
    }
    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return out;
}
