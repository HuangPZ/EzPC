#pragma once

#ifndef CORRECTNESS
#define CORRECTNESS 0
#endif


#include <sytorch/layers/layers.h>
#include <sytorch/module.h>
#include <sytorch/utils.h>

template <typename T>
class ResNet20 : public SytorchModule<T> {
    Conv2D<T> *conv0;
    ReLU<T> *relu1;

    Conv2D<T> *conv2_0, *conv2_1, *conv2_2;
    Conv2D<T> *conv3_0, *conv3_1, *conv3_2;
    Conv2D<T> *conv4_0, *conv4_1, *conv4_2;

    ReLU<T> *relu5;
    GlobalAvgPool2D<T> *globalaveragepool6;
    Flatten<T> *flatten7;
    FC<T> *fc8;

public:
    ResNet20() {
        // Initial convolution and activation
        // printf("Creating ResNet20\n");
        conv0 = new Conv2D<T>(3, 16, 3, 1, 1, true);
        // printf("Created Conv2D\n");
        relu1 = new ReLU<T>();
        // printf("Created ReLU\n");

        // Initialize layers explicitly
        conv2_0 = new Conv2D<T>(16, 16, 3, 1, 1, true);
        conv2_1 = new Conv2D<T>(16, 16, 3, 1, 1, true);
        conv2_2 = new Conv2D<T>(16, 16, 3, 1, 1, true);

        conv3_0 = new Conv2D<T>(16, 32, 3, 1, 2, true); // Downsample
        conv3_1 = new Conv2D<T>(32, 32, 3, 1, 1, true);
        conv3_2 = new Conv2D<T>(32, 32, 3, 1, 1, true);

        conv4_0 = new Conv2D<T>(32, 64, 3, 1, 2, true); // Downsample
        conv4_1 = new Conv2D<T>(64, 64, 3, 1, 1, true);
        conv4_2 = new Conv2D<T>(64, 64, 3, 1, 1, true);

        // printf("Created Conv2D blocks\n");

        // Remaining layers
        relu5 = new ReLU<T>();
        globalaveragepool6 = new GlobalAvgPool2D<T>();
        // printf("Created ReLU and GlobalAvgPool2D\n");
        flatten7 = new Flatten<T>();
        fc8 = new FC<T>(64, 10, true);
    }

    Tensor<T>& _forward(Tensor<T>& input) {
        // Initial convolution and activation
        printf("Starting ResNet20 forward\n");
        auto &x0 = conv0->forward(input);
        printf("Conv0 done\n");
        auto &x1 = relu1->forward(x0);
        printf("ReLU1 done\n");
        // Stage 1
        auto &x2_0 = conv2_0->forward(x1);
        printf("Conv2_0 done\n");
        auto &x2_1 = conv2_1->forward(x2_0);
        printf("Conv2_1 done\n");
        auto &x2_2 = conv2_2->forward(x2_1);
        printf("Conv2_2 done\n");

        // Stage 2
        auto &x3_0 = conv3_0->forward(x2_2); // Downsample
        printf("Conv3_0 done\n");
        auto &x3_1 = conv3_1->forward(x3_0);
        printf("Conv3_1 done\n");
        auto &x3_2 = conv3_2->forward(x3_1);
        printf("Conv3_2 done\n");

        // Stage 3
        auto &x4_0 = conv4_0->forward(x3_2); // Downsample
        auto &x4_1 = conv4_1->forward(x4_0);
        auto &x4_2 = conv4_2->forward(x4_1);
        printf("Conv4_2 done\n");

        // Final stages
        auto &x5 = relu5->forward(x4_2);
        printf("ReLU5 done\n");
        auto &x6 = globalaveragepool6->forward(x5);
        printf("GlobalAvgPool6 done\n");
        auto &x7 = flatten7->forward(x6);
        return fc8->forward(x7); // Final fully connected layer
    }
};
