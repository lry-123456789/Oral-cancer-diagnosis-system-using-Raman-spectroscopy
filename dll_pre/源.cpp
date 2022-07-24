/*
#include<iostream>
#include<assert.h>
#include<vector>
//引入runtime库
#include<onnxruntime_cxx_api.h>
//引入cuda库<无cuda>,改为cpu
#include"cpu_provider_factory.h"
#include<ctime>
int main()
{
	Ort::Env env(ORT_LOGGING_LEVEL_VERBOSE, "test");
	Ort::SessionOptions session_options;
	//使用16线程执行，提升速度
	session_options.SetIntraOpNumThreads(16);
	//使用GPU时，请取消这两行的注释
	
	// * #include<cuda_provider_factory.h>
	// * OrtSessionOptionsAppendExecutionProvider_CUDA(session_options,0)
	
	session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
	printf("Using Onnxruntime C++ API\n");
	const wchar_t* model_path = L"AlexNet_output.onnx";
	Ort::Session session(env, model_path, session_options);
	Ort::AllocatorWithDefaultOptions allocator;
	size_t num_input_nodes = session.GetInputCount();
	size_t num_output_nodes = session.GetOutputCount();
	std::vector<const char*> input_node_names(num_input_nodes);
	std::vector<const char*> output_node_names(num_output_nodes);
	std::vector<int64_t> input_node_dims;
	std::vector<int64_t> output_node_dims;
	printf("Number of inputs = %zu\n", num_input_nodes);
	printf("Number of outputs= %zu\n", num_input_nodes);
	//迭代出所有层的信息
	for (int i = 0; i < num_output_nodes; i++)
	{
		char* output_name = session.GetOutputName(i, allocator);
		printf("Output %d : name =%s\n", i, output_name);
		//将输出层的名称添加到output_node_name这个vector中
		output_node_names[i] = output_name;

		Ort::TypeInfo type_info = session.GetOutputTypeInfo(i);
		auto tensor_info = type_info.GetTensorTypeAndShapeInfo();

		ONNXTensorElementDataType type = tensor_info.GetElementType();
		printf("output %d : type=%d\n", i, type);

		output_node_dims = tensor_info.GetShape();
		printf("Output %d : num_dims=%zu\n", i, output_node_dims.size());
		for (int j = 0; j < output_node_dims.size(); j++)
			printf("Output %d : dim %d=%jd\n", i, j, output_node_dims[j]);

	}
	printf("get information0 successfully ended\n");
	// 获取所有输入层信息
	for (int i = 0; i < num_input_nodes; i++) {
		char* input_name = session.GetInputName(i, allocator);
		printf("Input %d : name=%s\n", i, input_name);
		input_node_names[i] = input_name;

		Ort::TypeInfo type_info = session.GetInputTypeInfo(i);
		auto tensor_info = type_info.GetTensorTypeAndShapeInfo();

		ONNXTensorElementDataType type = tensor_info.GetElementType();
		printf("Input %d : type=%d\n", i, type);

		input_node_dims = tensor_info.GetShape();
		printf("Input %d : num_dims=%zu\n", i, input_node_dims.size());
		for (int j = 0; j < input_node_dims.size(); j++)
			printf("Input %d : dim %d=%jd\n", i, j, input_node_dims[j]);
	}
	printf("get information1 successfully ended\n");
	size_t input_tensor_size = 1044;
	// 生成假的输入
	std::vector<float> input_tensor_values(input_tensor_size);
	printf("successfully created fake input\n");
	for (unsigned int i = 0; i < input_tensor_size; i++)
		input_tensor_values[i] = (float)i / (input_tensor_size + 1);
	printf("successfully change the input to tensor\n");
	auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
	printf("successfully put it into memory\n");
	clock_t startTime, endTime;
	// 创建输入tensor
	Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_tensor_values.data(), input_tensor_size, input_node_dims.data(), 2);
	printf("successfully created value\n");
	assert(input_tensor.IsTensor());
	startTime = clock();
	// 第二个参数代表输入节点的名称集合
	// 第四个参数1代表输入层的数目
	// 第五个参数代表输出节点的名称集合
	// 最后一个参数代表输出节点的数目
	// 除了第一个节点外，其他参数与原网络对应不上程序就会无法执行
	auto output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_node_names.data(), &input_tensor, 1, output_node_names.data(), num_output_nodes);
	endTime = clock();
	assert(output_tensors.size() == 1 && output_tensors.front().IsTensor());
	// 获取输出输出
	float* floatarr = output_tensors.front().GetTensorMutableData<float>();
	// TODO 因为这里我的输出是个heat map，暂时还没完成这部分后处理功能
	// 计算运行时间
	std::cout << "The run time is:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
	printf("Done!\n");
	system("pause");
	return 0;
}
*/
//上方代码出错，-1073740791

#include <assert.h>
#include <onnxruntime_c_api.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "cpu_provider_factory.h"
const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);

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
int main(int argc, char* argv[]) {
    //*************************************************************************
    // initialize  enviroment...one enviroment per process
    // enviroment maintains thread pools and other state info
    // 创建一个执行环境，主要用来创建onnxruntime的session
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

    g_ort->ReleaseValue(output_tensor);
    g_ort->ReleaseValue(input_tensor);
    g_ort->ReleaseSession(session);
    g_ort->ReleaseSessionOptions(session_options);
    g_ort->ReleaseEnv(env);
    printf("Done!\n");
    return 0;
}
