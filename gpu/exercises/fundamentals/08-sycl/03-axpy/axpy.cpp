#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

int main() {
    // Set up queue on any available device
    queue q(default_selector_v);

    constexpr size_t N = 25600;
    constexpr int a = 4;

    // Initialization on the host with STL
    std::vector<int> y(N);
    /*
    std::vector<int> x(N), y(N);
    std::fill(x.begin(), x.end(), 1);
    std::fill(y.begin(), y.end(), 2);
    */

    // USM
    /*
    int* x = sycl::malloc_shared<int>(N, q);
    int* y = sycl::malloc_shared<int>(N, q);
    // Initialization on the host with USM
    for (int i = 0; i < N; i++) {
        x[i] = 1;
        y[i] = 2;
    }
    */

    /*
    int* d_x = malloc_device<int>(N, q);
    int* d_y = malloc_device<int>(N, q);
    q.memcpy(d_x, x.data(), N * sizeof(int)).wait();
    q.memcpy(d_y, y.data(), N * sizeof(int)).wait();
    // q.wait();
    */

    // Create buffers for the host data or allocate memory usinggUSM
    // If USM + malloc_device() is used add the copy operations

    // If using buffers, AdaptiveCpp prints this warning:
    // [AdaptiveCpp Warning] This application uses SYCL buffers;
    // the SYCL buffer-accessor model is well-known to introduce unnecessary overheads.
    // Please consider migrating to the SYCL2020 USM model,
    // in particular device USM (sycl::malloc_device) combined with in-order queues for more performance.
    // See the AdaptiveCpp performance guide for more information:
    // https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/doc/performance.md
    {
    // buffer<int, 1> d_x(x.data(), range<1>(N));
    // buffer<int, 1> d_y(y.data(), range<1>(N));
    buffer<int, 1> d_x(range<1>(N));
    buffer<int, 1> d_y(range<1>(N));

    q.submit([&](handler &h) {
        accessor x_acc{d_x, h, write_only};
        h.parallel_for(range{N}, [=](id<1> i) {
            x_acc[i] = 1;
        });
    });

    q.submit([&](handler &h) {
        accessor y_acc{d_y, h, write_only};
        h.parallel_for(range{N}, [=](id<1> i) {
            y_acc[i] = 2;
        });
    })

    // Submit the kernel to the queue
    q.submit([&](handler& h) {
        // Create accessors if necessary
        accessor x_acc{d_x, h, read_only};
        accessor y_acc{d_y, h, read_write};

        // Regular range
        h.parallel_for(range<1>(N), [=](id<1> i) {
            y_acc[i] = a * x_acc[i] +  y_acc[i];
        });

        /*
        // Define work-group size and global size
        size_t local_size = 256;
        size_t global_size = ((N + local_size - 1) / local_size) * local_size;

        // nd_range launching
        h.parallel_for(sycl::nd_range<1>(sycl::range<1>(((N+local_size-1)/local_size)*local_size), sycl::range<1>(local_size)), [=](sycl::nd_item<1> item) {
            auto idx = item.get_global_id(0);
            if (idx < N) { // to avoid out of bounds access
                // y_acc[idx] = y_acc[idx] + a*x_acc[idx];
                // d_y[idx] = d_y[idx] + a * d_x[idx];
                y[idx] = y[idx] + a * x[idx];
            }
        });
        */

        /*
        // Basic submission with USM
        h.parallel_for(sycl::range{N}, [=](sycl::id<1> idx) {
            d_y[idx] = d_y[idx] + a*d_x[idx];
        });
        */
    }); //.wait();

    /*
    // Checking the result inside the scope of the buffers using host_accessors
    host_accessor h_accY(d_y, sycl::read_only); // Read back data after kernel execution
    std::cout << "First few elements of Y after operation:" << std::endl;
    for (size_t i = 0; i < 10; ++i) {
        std::cout << "Y[" << i << "] = " << h_accY[i] << std::endl;
    }
    */

    // End of buffer scope
    }

    // If USM + malloc_device() is used add the copy operations
    // q.memcpy(y.data(), d_y, N * sizeof(int)).wait();

    // If USM is used free the device memory
    // sycl::free(d_x, q);
    // sycl::free(d_y, q);

    // Check that all outputs match expected value
    // bool passed = std::all_of(y.begin(), y.end(), [a](int val) { return val == a * 1 + 2; });
    bool passed = true;
    // This can manually create an error
    y[2] = 1;
    const int correct = a * 1 + 2;
    for (int i = 0; i < N; i++) {
        if (y[i] != correct) {
            passed = false;
            break;
        }
    }

    // USM with
    // sycl::free(x, q);
    // sycl::free(y, q);

    std::cout << ((passed) ? "SUCCESS" : "FAILURE") << std::endl;
    return (passed) ? 0 : 1;
}
